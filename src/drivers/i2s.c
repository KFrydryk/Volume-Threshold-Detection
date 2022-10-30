#include <stdint.h>
#include "include/i2s.h"
#include "include/dma.h"
#include "platform_defs.h"

/* register/bit set for SPIx clk enable */
uint32_t spi_periph_en[][2] = {
	{RCC_APB2ENR, SPI1EN},
	{RCC_APB1ENR, SPI2EN},
	{RCC_APB1ENR, SPI3EN}
};

static int i2s_set_freq(struct i2s *i2s)
{
	/* TODO: calculate R and N based on required frequency and sysclk */
	if (i2s->data.frequency == 48000) {
		set_bits(RCC_PLLI2S, PLLI2SR(5));
		set_bits(RCC_PLLI2S, PLLI2SN(61)); //61
		/* 24.4 MHz i2s clk*/
		clear_bits(I2S2_I2SPR, I2S_MCKOE);
		clear_bits(I2S2_I2SPR, I2S_ODD);
		set_bits(I2S2_I2SPR, I2S_I2SDIV(16));
		/* 24.4/16 = 1,525. Wanted 1,536. <1% err is acceptable*/
		set_bits(RCC_CR, RCC_PLLI2SON);
		while (!(read_reg(RCC_CR) & RCC_PLLI2SRDY))
			;

		return 0;
	}

	return -ENOTSUP;
}

static int i2s_config_apply(struct i2s *i2s)
{	/* Currently only supports i2s2 */
	if (i2s->data.instance == 2) {
		clear_bits(I2S2_I2SCFGR, 0x0FBF);
		clear_bits(I2S2_I2SPR, 0x03F);
		set_bits(I2S2_I2SCFGR, SPI_SETUP_I2S);
		set_bits(I2S2_I2SCFGR, I2S_I2SCFG(i2s->data.mode));
		set_bits(I2S2_I2SCFGR, I2S_I2SSTD(i2s->data.standard));
		/* clock steady state is low level*/
		// set_bits(I2S2_I2SCFGR, I2S_CKPOL);
		switch (i2s->data.fmt) {
		case I2S_DATA_16_IN_16:
			set_bits(I2S2_I2SCFGR, I2S_DATLEN(0x00));
			set_bits(I2S2_I2SCFGR, I2S_CHLEN);
			break;
		case I2S_DATA_16_IN_32:
			set_bits(I2S2_I2SCFGR, I2S_DATLEN(0x00));
			set_bits(I2S2_I2SCFGR, I2S_CHLEN);
			break;
		case I2S_DATA_24_IN_32:
			set_bits(I2S2_I2SCFGR, I2S_DATLEN(0x01));
			set_bits(I2S2_I2SCFGR, I2S_CHLEN);
			break;
		case I2S_DATA_32_IN_32:
			set_bits(I2S2_I2SCFGR, I2S_DATLEN(0x02));
			set_bits(I2S2_I2SCFGR, I2S_CHLEN);
			break;
		default:
			return -ENOTSUP;
		}

		return i2s_set_freq(i2s);
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static int i2s_set_config(struct i2s *i2s, uint32_t instance, enum i2s_mode mode,
			  enum i2s_standard standard, enum i2s_format fmt, uint32_t freq,
			  bool rxdma, bool txdma)
{
	if (i2s == NULL)
		return -ENODEV;

	i2s->data.fmt = fmt;
	i2s->data.frequency = freq;
	i2s->data.instance = instance;
	i2s->data.mode = mode;
	i2s->data.standard = standard;
	i2s->data.rxdma = rxdma;
	i2s->data.txdma = txdma;

	return i2s_config_apply(i2s);
}

static int i2s_en(struct i2s *i2s)
{
	if (i2s == NULL)
		return -ENODEV;

	if (i2s->data.instance == 2) {
		set_bits(I2S2_I2SCFGR, I2S_I2SE);

		if (i2s->data.rxdma)
			set_bits(I2S2_CR2, I2S2_RXDMAEN);
		if (i2s->data.txdma)
			set_bits(I2S2_CR2, I2S2_TXDMAEN);
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static struct i2s_ops ops = {
	.configure = i2s_set_config,
	.enable = i2s_en
};


int i2s_init(struct i2s *i2s, struct dma *dma, uint32_t in_port, uint32_t in_pin,
	     uint32_t clk_port, uint32_t clk_pin, uint32_t spi_num)
{
	int ret;

	if ((i2s == NULL) || dma == NULL)
		return -ENODEV;
	/* enable spi perif */
	set_bits(spi_periph_en[spi_num-1][0], spi_periph_en[spi_num-1][1]);

	i2s->ops = &ops;

	i2s->io_in = gpio_create(in_port, in_pin);
	i2s->io_clk = gpio_create(clk_port, clk_pin);
	ret = gpio_configure_af(&i2s->io_in, NOT_OUT, PULLUP, 5); //hardcode for i2s2
		if (ret < 0)
			return -EINVAL;
	ret = gpio_configure_af(&i2s->io_clk, PUSH_PULL, NO_PULL, 5); //hardcode for i22

	return ret;

}
