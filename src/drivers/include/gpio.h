#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <errno.h>

struct gpio;
int gpio_periph_init(void);

enum gpio_mode {
	INPUT,
	OUTPUT,
	ALTERNATE,
	ANALOG
};

/* Output type */
enum gpio_otype {
	PUSH_PULL,
	OPEN_DRAIN,
	NOT_OUT
};

/* Pull type */
enum gpio_ptype {
	NO_PULL,
	PULLUP,
	PULLDOWN,
	NOT_IN
};

enum gpio_state {
	LOW,
	HIGH
};

enum gpio_int_event {
	FALLING_EDGE,
	RISING_EDGE
};

enum gpio_port {
	PA,
	PB,
	PC,
	PD,
	PE,
	PF,
	PG,
	PH,
	PI
};

enum gpio_af {
	SYSTEM = 0,
	SPI1 = 5,
	SPI2 = 5,
	SPI3 = 6
};

/* gpio operations */
struct gpio_ops {
	int (*configure)(struct gpio *gpio, enum gpio_mode mode,
			 enum gpio_otype otype, enum gpio_ptype ptype, enum gpio_af af);
	int (*write_val)(struct gpio *gpio, enum gpio_state val);
	int (*read_val)(struct gpio *gpio);
	int (*configure_interrupt)(struct gpio *gpio, enum gpio_int_event event);
};

struct gpio_data {
	uint32_t port;
	uint32_t pin;
	enum gpio_mode mode;
	enum gpio_otype otype;
	enum gpio_ptype ptype;
	enum gpio_af af;
};

struct gpio {
	struct gpio_data data;
	struct gpio_ops *ops;
};

static inline int gpio_configure_output(struct gpio *gpio, enum gpio_otype otype)
{
	if (gpio == NULL)
		return -ENODEV;

	return gpio->ops->configure(gpio, OUTPUT, otype, NOT_IN, SYSTEM);
}

static inline int gpio_configure_input(struct gpio *gpio, enum gpio_ptype ptype)
{
	if (gpio == NULL)
		return -ENODEV;

	return gpio->ops->configure(gpio, INPUT, NOT_OUT, ptype, SYSTEM);
}

static inline int gpio_configure_interrupt(struct gpio *gpio, enum gpio_int_event event)
{
	if (gpio == NULL)
		return -ENODEV;

	return gpio->ops->configure_interrupt(gpio, event);
}

/* NOTE: IRQ handler has to be defined separately! */
static inline int gpio_configure_af(struct gpio *gpio, enum gpio_otype otype, enum gpio_ptype ptype,
		      enum gpio_af af)
{
	if (gpio == NULL)
		return -ENODEV;

	return gpio->ops->configure(gpio, ALTERNATE, otype, ptype, af);
}

/* should return enum gpio_state or error code */
static inline int gpio_read(struct gpio *gpio)
{
	if (gpio == NULL)
		return -ENODEV;

	return gpio->ops->read_val(gpio);
}

static inline int gpio_write(struct gpio *gpio, enum gpio_state val)
{
	if (gpio == NULL)
		return -ENODEV;

	return gpio->ops->write_val(gpio, val);
}

/* use to init gpio and prefill gpio struct */
int gpio_init(struct gpio *gpio, uint32_t port, uint32_t pin);

#endif
