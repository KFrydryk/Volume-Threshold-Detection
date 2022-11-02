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
#include "gp-timer.h"
#include "parameters.h"

#define BUTT_PORT 0
#define BUTT_PIN 0

#define PDM_ARR_SIZE 48
#define PCM_ARR_SIZE (AVERAGING_TIME/2)

struct threshold thr;
low_pass_Filter fltr;

/* hold 1ms of samples*/
uint32_t tab[PDM_ARR_SIZE];
uint32_t tab2[PDM_ARR_SIZE];
int32_t pcm_partial_tab[PDM_ARR_SIZE];
static int last_index_partial;
/* hold intrest range of samples */
int32_t pcm_tab[PCM_ARR_SIZE];
static int last_index;

struct gpio status_led;
struct gp_timer status_led_tmr;
bool status_led_on;
struct gp_timer tmr;
bool is_in_delay_loop;

static int32_t avg_abs_int32(int32_t *arr, size_t len)
{
	int64_t temp = 0;

	for (int i = 0; i < len; i++)
		temp += abs(arr[i]);

	temp = temp/len;
	return (int32_t)(temp);
}

void  __attribute__ ((interrupt)) TIM5_IRQHandler(void)
{
	status_led_on = !status_led_on;
	status_led.ops->write_val(&status_led, status_led_on);
	clear_bits(TIM5_SR, TIM_UIF);
}

void  __attribute__ ((interrupt)) TIM2_IRQHandler(void)
{
	is_in_delay_loop = false;
	gp_timer_stop(&tmr);
	clear_bits(TIM2_SR, TIM_UIF);
}

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
			tmp_val = ((tab[i] << j) & 0x80000000) ? INT32_MAX : INT32_MIN;
			low_pass_Filter_put(&fltr, tmp_val);
		}

		/* filter put is not complex, but filter get should be moved outside of interrupt */
		pcm_partial_tab[last_index_partial++] = low_pass_Filter_get(&fltr);

		if (last_index_partial == PDM_ARR_SIZE) {
			last_index_partial = 0;
			pcm_tab[last_index++] = avg_abs_int32(pcm_partial_tab, PDM_ARR_SIZE);
			if (last_index == PCM_ARR_SIZE)
				last_index = 0;
		}
	}

	set_bits(DMA1_LIFCR, (1 << 27) | (1 << 26));
}



int main()
{
	struct linked_list llis[sizeof(thresholds)/sizeof(uint32_t)];
	struct gpio BUT;
	struct gpio LED_HI;
	struct gpio LED_LOW;
	struct i2s mic;
	struct dma copier;
	int32_t avg;

	platform_init();
	gpio_periph_init(NULL);

	/* create GPIOs*/
	BUT = gpio_create(BUTT_PORT, BUTT_PIN);
	/* choose from PD12, 13, 14, 15 for onboard leds */
	LED_HI = gpio_create(3, 15);
	LED_LOW = gpio_create(3, 13);
	status_led = gpio_create(3, 12);

	gpio_configure_input(&BUT, PULLDOWN);
	gpio_configure_output(&LED_HI, PUSH_PULL);
	gpio_configure_output(&LED_LOW, PUSH_PULL);
	gpio_configure_output(&status_led, PUSH_PULL);
	gpio_configure_interrupt(&BUT, RISING_EDGE);

	/* setup timers: status led timer and delay */
	gp_timer_init(&tmr, 2);
	gp_timer_init(&status_led_tmr, 5);
	/* configure for 3s delay. APB clk prescaler is 2, so 8400*/
	gp_timer_configure(&tmr, 8400, 30000);
	gp_timer_configure(&status_led_tmr, 8400, 5000);
	gp_timer_start(&tmr);
	gp_timer_start(&status_led_tmr);

	/* delay 3s */
	is_in_delay_loop = true;
	while (is_in_delay_loop)
		;

	/* populate thresholds list */
	for (int i = 0; i < thresholds_num; i++) {
		linked_list_init(&llis[i]);
		llis[i].data = &thresholds[i];

		/* skip linking for initial list */
		if (i == 0)
			continue;

		linked_list_append(&llis[i - 1], &llis[i]);
	}

	threshold_init(&thr, &llis[0]);

	/* DMA1, stream3, channel0 for SPI2 request*/
	dma_init(&copier, 1, 3, 0);
	dma_configure(&copier, DMA_PER_TO_MEM, false, true, DMA_ALIGN_H_WORD, DMA_ALIGN_H_WORD,
		      true, DMA_PRIO_LOW, false);
	dma_set_data_cfg(&copier, 0x4000380c, tab, sizeof(tab)/2); /* TODO: pesky raw address */

	/* i2s2 init*/
	i2s_init(&mic, &copier, 2, 3, 1, 10, 2);
	/* TODO: instance can be taken from init */
	i2s_configure(&mic, 2, MASTER_RECEIVE, MSB, I2S_DATA_32_IN_32, 48000, true, false);
	/* enable i2s and dma */
	i2s_enable(&mic, true);
	dma_enable(&copier);
	dma_int_enable(&copier);

	while (1) {
		avg = avg_abs_int32(pcm_tab, PCM_ARR_SIZE);

		if (avg > thr.val) {
			/* TODO: dont use ops call. use api */
			LED_HI.ops->write_val(&LED_HI, HIGH);
			LED_LOW.ops->write_val(&LED_LOW, LOW);
		} else {
			LED_HI.ops->write_val(&LED_HI, LOW);
			LED_LOW.ops->write_val(&LED_LOW, HIGH);
		}
	}
	
	return 0;
}