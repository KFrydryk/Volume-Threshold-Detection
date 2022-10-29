#include <stddef.h>
#include "platform/stm32f407G/include/platform_init.h"
#include "platform/stm32f407G/include/platform_defs.h"
#include "gpio.h"
#include "linked-list.h"
#include "thresholds.h"
#include <stdint.h>
#include <stdbool.h>

#define BUTT_PORT 0
#define BUTT_PIN 0

struct threshold thr;

static uint32_t thresholds[] = {
	1,
	2,
	3,
	4,
	5,
	6
};

void  __attribute__ ((interrupt)) EXTI0_IRQHandler(void)
{
	if (*(uint32_t *)EXTI_PR & (1 << BUTT_PIN)) {
		*(uint32_t *)EXTI_PR |= (1 << BUTT_PIN);
		threshold_next(&thr);
	}
}


int main()
{

	struct linked_list llis[sizeof(thresholds)/sizeof(uint32_t)];
	struct gpio BUT;

	platform_init();
	gpio_periph_init(NULL);

	BUT = gpio_create(BUTT_PORT, BUTT_PIN);
	gpio_configure_input(&BUT, PULLDOWN);
	gpio_configure_interrupt(&BUT, RISING_EDGE);

	for (int i = 0; i < sizeof(thresholds)/sizeof(uint32_t); i++) {
		linked_list_init(&llis[i]);
		llis[i].data = &thresholds[i];
		linked_list_append(&llis[0], &llis[i]);
	}

	threshold_init(&thr, &llis[0]);

	while (1) {
	}
	
	return 0;
}