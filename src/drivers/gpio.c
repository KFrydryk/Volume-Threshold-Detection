#include "include/gpio.h"
#include "platform_defs.h"
#include "errno.h"
#include <stdint.h>

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
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static int gpio_configure(struct gpio *gpio, enum gpio_mode mode,
			  enum gpio_otype otype, enum gpio_ptype ptype)
{
	if (mode == INPUT && otype != NOT_OUT)
		return -EINVAL;
	if (mode == OUTPUT && ptype != NOT_IN)
		return -EINVAL;
	gpio->data.mode = mode;
	gpio->data.otype = otype;
	gpio->data.ptype = ptype;
	gpio_apply_config(gpio);
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
	.write_val = gpio_write_val
};

/* use to init gpio and prefill gpio struct */
struct gpio gpio_create(uint32_t port, uint32_t pin)
{
	struct gpio gpio_dev;

	gpio_dev.data.port = port;
	gpio_dev.data.pin = pin;
	gpio_dev.ops = &gpio_operations;

	return gpio_dev;
};

int gpio_periph_init(void *data)
{
	/* enable all gpio */
	write_reg(RCC_AHB1ENR, (0xff));

	return 0;
}
