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

/* use to init gpio and prefill gpio struct */
struct gpio gpio_create(uint32_t port, uint32_t pin);

/* gpio operations */
struct gpio_ops {
	int (*configure)(struct gpio *gpio, enum gpio_mode mode,
			 enum gpio_otype otype, enum gpio_ptype ptype);
	int (*write_val)(struct gpio *gpio, enum gpio_state val);
	int (*read_val)(struct gpio *gpio);
};

struct gpio_data {
	uint32_t port;
	uint32_t pin;
	enum gpio_mode mode;
	enum gpio_otype otype;
	enum gpio_ptype ptype;
};

struct gpio {
	struct gpio_data data;
	struct gpio_ops *ops;
};

#endif
