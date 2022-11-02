#include "include/gpio.h"
#include "platform_defs.h"
#include "errno.h"
#include <stdint.h>

#define GPIO_IRQ_PRIO 3

static const uint32_t port_list[] = {
	GPIOA_BASE,
	GPIOB_BASE,
	GPIOC_BASE,
	GPIOD_BASE,
	GPIOE_BASE,
	GPIOF_BASE,
	GPIOG_BASE,
	GPIOH_BASE,
	GPIOI_BASE,
	GPIOJ_BASE,
	GPIOK_BASE
};

static const uint32_t exticr_list[] = {
	SYSCFG_EXTICR1,
	SYSCFG_EXTICR2,
	SYSCFG_EXTICR3,
	SYSCFG_EXTICR4
};

static int gpio_apply_config(struct gpio *gpio)
{
	uint32_t port_addr = port_list[gpio->data.port];
	/* set mode */
	clear_bits(port_addr + GPIO_MODER, 0x3 << (gpio->data.pin*2));
	set_bits(port_addr + GPIO_MODER, gpio->data.mode << (gpio->data.pin*2));
	if (gpio->data.mode == OUTPUT) {
		clear_bits(port_addr + GPIO_OTYPER, (1 << gpio->data.pin));
		set_bits(port_addr + GPIO_OTYPER, gpio->data.otype << gpio->data.pin);
	} else if (gpio->data.mode == INPUT) {
		clear_bits(port_addr + GPIO_PUPDR, 0x3 << (gpio->data.pin*2));
		set_bits(port_addr + GPIO_PUPDR, gpio->data.ptype << (gpio->data.pin*2));
	} else if (gpio->data.mode == ALTERNATE) {
		/* can alternate function require otype and ptype to be set? */
		if (gpio->data.ptype != NOT_IN) {
			clear_bits(port_addr + GPIO_PUPDR, 0x3 << (gpio->data.pin*2));
			set_bits(port_addr + GPIO_PUPDR, gpio->data.ptype << (gpio->data.pin*2));
		}
		if (gpio->data.otype != NOT_OUT) {
			clear_bits(port_addr + GPIO_OTYPER, (1 << gpio->data.pin));
			set_bits(port_addr + GPIO_OTYPER, gpio->data.otype << gpio->data.pin);
		}
		/* set AF in Low or High parto fo GPIO_AF depending on pin */
		if (gpio->data.pin < 8) {
			clear_bits(port_addr + GPIO_AFRL, 0xF << gpio->data.pin * 4);
			set_bits(port_addr + GPIO_AFRL, gpio->data.af << gpio->data.pin * 4);
		} else {
			clear_bits(port_addr + GPIO_AFRH, 0xF << (gpio->data.pin - 8) * 4);
			set_bits(port_addr + GPIO_AFRH, gpio->data.af << (gpio->data.pin - 8) * 4);
		}
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static int gpio_configure(struct gpio *gpio, enum gpio_mode mode,
			  enum gpio_otype otype, enum gpio_ptype ptype, enum gpio_af af)
{
	if (mode == INPUT && otype != NOT_OUT)
		return -EINVAL;
	if (mode == OUTPUT && ptype != NOT_IN)
		return -EINVAL;
	gpio->data.mode = mode;
	gpio->data.otype = otype;
	gpio->data.ptype = ptype;
	gpio->data.af = af;
	gpio_apply_config(gpio);
	return 0;
}

static uint32_t gpio_get_pin_excint(uint32_t pin)
{
	uint32_t irq;

	switch (pin) {
	case 0:
		irq = EXTI0_IRQn;
		break;
	case 1:
		irq = EXTI1_IRQn;
		break;
	case 2:
		irq = EXTI2_IRQn;
		break;
	case 3:
		irq = EXTI3_IRQn;
		break;
	case 4:
		irq = EXTI4_IRQn;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		irq = EXTI9_5_IRQn;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		irq = EXTI15_10_IRQn;
		break;

	default:
		break;
	}

	return irq;
}

static int gpio_config_int(struct gpio *gpio, enum gpio_int_event event)
{
	uint32_t irq;
	/* check if pin and port nr in hw bounds */
	if ((gpio->data.port > 0x08) || (gpio->data.pin > 0x0F))
		return -EINVAL;

	/* System configuration controller clock enable */
	set_bits(RCC_APB2ENR, SYSCFGEN);

	/* Set SYSCFG to connect the button EXTI line to GPIO port */
	clear_bits(exticr_list[gpio->data.pin/4], 0xF << ((gpio->data.pin % 4) * 4));
	set_bits(exticr_list[gpio->data.pin/4], gpio->data.port << ((gpio->data.pin % 4) * 4));


	/* Setup the button's EXTI line as an interrupt */
	set_bits(EXTI_IMR, 1 << gpio->data.pin);
	if (event == FALLING_EDGE) {
		/* Disable the 'rising edge' trigger */
		clear_bits(EXTI_RTSR, (1 << gpio->data.pin));
		/* Enable the 'falling edge' trigger */
		set_bits(EXTI_FTSR, (1 << gpio->data.pin));
	} else {
		/* Enable the 'rising edge' trigger */
		set_bits(EXTI_RTSR, (1 << gpio->data.pin));
		/* Disable the 'falling edge' trigger */
		clear_bits(EXTI_FTSR, (1 << gpio->data.pin));
	}

	irq = gpio_get_pin_excint(gpio->data.pin);

	irq_set_priority(irq, GPIO_IRQ_PRIO);
	irq_enable(irq);

	return 0;
}

static int gpio_write_val(struct gpio *gpio, enum gpio_state val)
{
	uint32_t port_addr = port_list[gpio->data.port];

	if (gpio->data.mode != OUTPUT)
		return -ENOTSUP;

	if (val)
		set_bits(port_addr + GPIO_ODR, 1 << gpio->data.pin);
	else
		clear_bits(port_addr + GPIO_ODR, 1 << gpio->data.pin);

	return 0;
}

static int gpio_read_val(struct gpio *gpio)
{
	uint32_t port_addr = port_list[gpio->data.port];

	if (gpio->data.mode != INPUT)
		return -ENOTSUP;

	return read_reg(port_addr + GPIO_IDR) & (1 << gpio->data.pin);
}

static const struct gpio_ops gpio_operations = {
	.configure = gpio_configure,
	.read_val = gpio_read_val,
	.write_val = gpio_write_val,
	.configure_interrupt = gpio_config_int
};

int gpio_periph_init(void)
{
	/* enable all gpio */
	write_reg(RCC_AHB1ENR, (0xff));

	return 0;
}

/* use to init gpio and prefill gpio struct */
int gpio_init(struct gpio *gpio, uint32_t port, uint32_t pin)
{
	if (gpio == NULL)
		return -ENODEV;

	gpio->data.port = port;
	gpio->data.pin = pin;
	gpio->ops = &gpio_operations;

	return 0;
};
