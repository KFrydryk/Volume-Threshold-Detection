#include <stddef.h>
#include "platform/stm32f407G/include/platform_init.h"
#include "platform/stm32f407G/include/platform_defs.h"
#include "gpio.h"
#include "i2s.h"
#include "dma.h"
#include "linked-list.h"
#include "thresholds.h"
#include <stdint.h>
#include <stdbool.h>
#include "low-pass-Filter.h"

#define BUTT_PORT 0
#define BUTT_PIN 0

#define PDM_ARR_SIZE 48
#define PCM_ARR_SIZE 512

struct threshold thr;
low_pass_Filter fltr;

static uint32_t thresholds[] = {
	1,
	2,
	3,
	4,
	5,
	6
};

uint32_t tab[PDM_ARR_SIZE];
int32_t pcm_tab[PCM_ARR_SIZE];
uint32_t err_tab[PCM_ARR_SIZE];
static int last_index;


void  __attribute__ ((interrupt)) EXTI0_IRQHandler(void)
{
	if (*(uint32_t *)EXTI_PR & (1 << BUTT_PIN)) {
		*(uint32_t *)EXTI_PR |= (1 << BUTT_PIN);
		threshold_next(&thr);
	}
}

void  __attribute__ ((interrupt)) DMA1_Stream3_IRQHandler(void)
{
	int32_t tmp_val;

	static bool data_rdy;

	for (int i = 0; i < PDM_ARR_SIZE; i++) {
		for (size_t j = 0; j < 32; j++) {
			/* MSB first */
			tmp_val = ((tab[i] << j) & 0x80000000) ? 32000 : -32000;
			low_pass_Filter_put(&fltr, tmp_val);
		}

		/* filter put is not complex, but filter get should be moved outside of interrupt */
		pcm_tab[last_index++] = low_pass_Filter_get(&fltr);

		if (last_index == PCM_ARR_SIZE)
			last_index = 0;
	}

	set_bits(DMA1_LIFCR, (1 << 27) | (1 << 26));
}



int main()
{
	struct linked_list llis[sizeof(thresholds)/sizeof(uint32_t)];
	struct gpio BUT;
	struct gpio LED;
	struct i2s mic;
	struct dma copier;

	platform_init();
	gpio_periph_init(NULL);

	BUT = gpio_create(BUTT_PORT, BUTT_PIN);
	LED = gpio_create(3, 15);

	gpio_configure_input(&BUT, PULLDOWN);
	gpio_configure_output(&LED, PUSH_PULL);
	gpio_configure_interrupt(&BUT, RISING_EDGE);

	for (int i = 0; i < sizeof(thresholds)/sizeof(uint32_t); i++) {
		linked_list_init(&llis[i]);
		llis[i].data = &thresholds[i];
		linked_list_append(&llis[0], &llis[i]);
	}

	threshold_init(&thr, &llis[0]);

	/* DMA1, stream3, channel0 for SPI2 request*/
	dma_init(&copier, 1, 3, 0);
	dma_configure(&copier, DMA_PER_TO_MEM, false, true, DMA_ALIGN_H_WORD, DMA_ALIGN_H_WORD,
		      true, DMA_PRIO_LOW, false);
	dma_set_data_cfg(&copier, 0x4000380c, tab, sizeof(tab)/2);

	/* i2s2 init*/
	i2s_init(&mic, &copier, 2, 3, 1, 10, 2);
	/* TODO: instance can be taken from init */
	i2s_configure(&mic, 2, MASTER_RECEIVE, MSB, I2S_DATA_32_IN_32, 48000, true, false);
	/* enable i2s and dma */
	i2s_enable(&mic, true);
	dma_enable(&copier);
	dma_int_enable(&copier);

	/* must fit sum of pcm_tab elements */
	int64_t avg;
	while (1) {
		avg = 0;

		for (int i = 0; i < PCM_ARR_SIZE; i++)
			avg += abs(pcm_tab[i]);

		avg = avg/PCM_ARR_SIZE;

		if (avg > 650)
			LED.ops->write_val(&LED, HIGH);
		else
			LED.ops->write_val(&LED, LOW);
	}
	
	return 0;
}