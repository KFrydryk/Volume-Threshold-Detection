#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* implement if device needs additional preparation */
int gpio_periph_init(void *data);

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

/* use to init gpio and prefill gpio struct */
struct gpio gpio_create(uint32_t port, uint32_t pin);
int gpio_configure_output(struct gpio *gpio, enum gpio_otype otype);
int gpio_configure_input(struct gpio *gpio, enum gpio_ptype ptype);
/* NOTE: IRQ handler has to be defined separately! */
int gpio_configure_interrupt(struct gpio *gpio, enum gpio_int_event event);
int gpio_configure_af(struct gpio *gpio, enum gpio_otype otype, enum gpio_ptype ptype,
		      enum gpio_af af);

/* gpio operations */
struct gpio_ops {
	int (*configure)(struct gpio *gpio, enum gpio_mode mode,
			 enum gpio_otype otype, enum gpio_ptype ptype, enum gpio_af af);
	int (*write_val)(struct gpio *gpio, enum gpio_state val);
	int (*read_val)(struct gpio *gpio);
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

#endif
