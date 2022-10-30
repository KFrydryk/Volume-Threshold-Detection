#ifndef I2S_H
#define I2S_H

#include "gpio.h"
#include <stdint.h>
#include "dma.h"
#include <stdbool.h>
#include <errno.h>

struct i2s;

enum i2s_mode {
	SLAVE_TRANSMIT,
	SLAVE_RECEIVE,
	MASTER_TRANSMIT,
	MASTER_RECEIVE
};

enum i2s_standard {
	PHILIPS,
	MSB,
	LSB,
	PCM
};

enum i2s_format {
	I2S_DATA_16_IN_16,
	I2S_DATA_16_IN_32,
	I2S_DATA_24_IN_32,
	I2S_DATA_32_IN_32
};

enum i2s_cpol {
	I2S_CPOL_LOW,
	I2S_SPOL_HIGH
};

int i2s_init(struct i2s *i2s, struct dma *dma, uint32_t in_port, uint32_t in_pin,
	     uint32_t clk_port, uint32_t clk_pin, uint32_t spi_num);

struct i2s_data {
	uint32_t instance;
	enum i2s_mode mode;
	enum i2s_standard standard;
	enum i2s_format fmt;
	uint32_t frequency;
	bool rxdma;
	bool txdma;
	bool en;
};

/* TODO: ops should be at least partially same for all drivers*/
struct i2s_ops {
	int (*configure)(struct i2s *i2s, uint32_t instance, enum i2s_mode mode,
			 enum i2s_standard standard, enum i2s_format fmt, uint32_t freq,
			 bool rxdma, bool txdma);
	int (*enable)(struct i2s *i2s, bool en);
};

struct i2s {
	struct gpio io_in;
	struct gpio io_clk;
	struct dma dma;

	struct i2s_data data;
	struct i2s_ops *ops;
};

static int i2s_configure(struct i2s *i2s, uint32_t instance, enum i2s_mode mode,
			 enum i2s_standard standard, enum i2s_format fmt, uint32_t freq,
			 bool rxdma, bool txdma)
{
	if (i2s == NULL)
		return -ENODEV;

	return i2s->ops->configure(i2s, instance, mode, standard, fmt, freq, rxdma, txdma);
}

static int i2s_enable(struct i2s *i2s, bool en)
{
	if (i2s == NULL)
		return -ENODEV;

	return i2s->ops->enable(i2s, en);
}

#endif
