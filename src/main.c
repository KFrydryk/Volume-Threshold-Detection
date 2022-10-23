#include <stddef.h>
#include "platform/stm32f407G/include/platform_init.h"
#include "gpio.h"

#define BUTT_PORT 0
#define BUTT_PIN 0

int main()
{
	int pressed = 0;

	platform_init();
	gpio_periph_init(NULL);

	struct gpio BUT = gpio_create(BUTT_PORT, BUTT_PIN);
	struct gpio LED = gpio_create(3, 13);

	BUT.ops->configure(&BUT, INPUT, NOT_OUT, PULLDOWN);
	LED.ops->configure(&LED, OUTPUT, PUSH_PULL, NOT_IN);

	while (1) {
		pressed = BUT.ops->read_val(&BUT);
		if (pressed)
			LED.ops->write_val(&LED, HIGH);
		else
			LED.ops->write_val(&LED, LOW);
	}
	
	return 0;
}