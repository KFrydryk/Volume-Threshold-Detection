#include "include/dma.h"
#include "platform_defs.h"
#include "errno.h"
#include <stdint.h>


/* DISCLAIMER
 * This is experimental and not fully implemented. Not all DMA functionalities may be supported
 * Known limitations:
 * Only support DMA1
 * DMA cannot be uninitialized
 */
static int dma_config_apply(struct dma *dma)
{
	struct dma_config *cfg;

	if (dma == NULL)
		return -ENODEV;

	cfg = &dma->config;

		if (cfg->dmac == 1) {
			clear_bits(DMA1_SxCR(cfg->stream), 0x0FEFFFF);
			set_bits(DMA1_SxCR(cfg->stream), DMA_CHSEL(cfg->channel));
			set_bits(DMA1_SxCR(cfg->stream), DMA_DIR(cfg->dir));

			if (cfg->p_inc)
				set_bits(DMA1_SxCR(cfg->stream), DMA_PINC);

			if (cfg->m_inc)
				set_bits(DMA1_SxCR(cfg->stream), DMA_MINC);

			set_bits(DMA1_SxCR(cfg->stream), DMA_PSIZE(cfg->p_align));
			set_bits(DMA1_SxCR(cfg->stream), DMA_MSIZE(cfg->m_align));

			if (cfg->circ)
				set_bits(DMA1_SxCR(cfg->stream), DMA_CIRC);

			set_bits(DMA1_SxCR(cfg->stream), DMA_PRIO(cfg->priority));

			if (cfg->fifo_mode)
				set_bits(DMA1_SxFCR(cfg->stream), DMA_FIFO_EN);
		} else {
			clear_bits(DMA1_SxCR(cfg->stream), 0x0FEFFFF);
			set_bits(DMA2_SxCR(cfg->stream), DMA_CHSEL(cfg->channel));
			set_bits(DMA2_SxCR(cfg->stream), DMA_DIR(cfg->dir));

			if (cfg->p_inc)
				set_bits(DMA2_SxCR(cfg->stream), DMA_PINC);

			if (cfg->m_inc)
				set_bits(DMA2_SxCR(cfg->stream), DMA_MINC);

			set_bits(DMA2_SxCR(cfg->stream), DMA_PSIZE(cfg->p_align));
			set_bits(DMA2_SxCR(cfg->stream), DMA_MSIZE(cfg->m_align));

			if (cfg->circ)
				set_bits(DMA2_SxCR(cfg->stream), DMA_CIRC);

			set_bits(DMA2_SxCR(cfg->stream), DMA_PRIO(cfg->priority));

			if (cfg->fifo_mode)
				set_bits(DMA2_SxFCR(cfg->stream), DMA_FIFO_EN);

	}

	return 0;
}

static int dma_set_config(struct dma *dma, enum dma_dir dir, bool p_inc, bool m_inc,
			  enum dma_d_align p_align, enum dma_d_align m_align, bool circ,
			  enum dma_prio prio, bool fifo_mode)
{
	if (dma == NULL)
		return -ENODEV;

	dma->config.dir = dir;
	dma->config.p_inc = p_inc;
	dma->config.m_inc = m_inc;
	dma->config.p_align = p_align;
	dma->config.m_align = m_align;
	dma->config.circ = circ;
	dma->config.priority = prio;
	dma->config.fifo_mode = fifo_mode;
	dma->config.en = 0;

	return dma_config_apply(dma);
}

static int dma_set_data_config(struct dma *dma, void *src, void *dst, size_t size)
{
	struct dma_config *cfg;

	if (dma == NULL)
		return -ENODEV;
	if (dst == NULL)
		return -ENOMEM;

	cfg = &dma->config;

	/* can only be set when transfer is disabled */
	if (cfg->en == 1)
		return -EBUSY;

	if (cfg->dmac == 1) {
		/* set buffer size */
		clear_bits(DMA1_SxNDTR(cfg->stream), 0xFFFF);
		set_bits(DMA1_SxNDTR(cfg->stream), (uint32_t)size);
		clear_bits(DMA1_SxPAR(cfg->stream), 0xFFFFFFFF);
		clear_bits(DMA1_SxM0AR(cfg->stream), 0xFFFFFFFF);
		clear_bits(DMA1_SxM1AR(cfg->stream), 0xFFFFFFFF);

		if (cfg->dir == DMA_MEM_TO_PER) {
			set_bits(DMA1_SxM0AR(cfg->stream), (uint32_t)src);
			set_bits(DMA1_SxPAR(cfg->stream), (uint32_t)dst);
		} else {
			/* same for per2mem and mem2mem */
			set_bits(DMA1_SxPAR(cfg->stream), (uint32_t)src);
			set_bits(DMA1_SxM0AR(cfg->stream), (uint32_t)dst);
		}
	} else {
		/* set buffer size */
		clear_bits(DMA2_SxNDTR(cfg->stream), 0xFFFF);
		set_bits(DMA2_SxNDTR(cfg->stream), (uint32_t)size);
		clear_bits(DMA2_SxPAR(cfg->stream), 0xFFFFFFFF);
		clear_bits(DMA2_SxM0AR(cfg->stream), 0xFFFFFFFF);
		clear_bits(DMA2_SxM1AR(cfg->stream), 0xFFFFFFFF);

		if (cfg->dir == DMA_MEM_TO_PER) {
			set_bits(DMA2_SxM0AR(cfg->stream), (uint32_t)src);
			set_bits(DMA2_SxPAR(cfg->stream), (uint32_t)dst);
		} else {
			/* same for per2mem and mem2mem */
			set_bits(DMA2_SxPAR(cfg->stream), (uint32_t)src);
			set_bits(DMA2_SxM0AR(cfg->stream), (uint32_t)dst);
		}
	}

	return 0;
}

static int dma_en(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	if (dma->config.dmac == 1)
		set_bits(DMA1_SxCR(dma->config.stream), DMA_EN);
	else if (dma->config.dmac == 2)
		set_bits(DMA2_SxCR(dma->config.stream), DMA_EN);
	else
		return -ENODEV;

	return 0;
}

static int dma_disable(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	if (dma->config.dmac == 1)
		clear_bits(DMA1_SxCR(dma->config.stream), DMA_EN);
	else if (dma->config.dmac == 2)
		clear_bits(DMA2_SxCR(dma->config.stream), DMA_EN);
	else
		return -ENODEV;

	return 0;
}

static int dma_enable_interrupt(struct dma *dma)
{
	uint32_t irq;

	if (dma == NULL)
		return -ENODEV;

	if (dma->config.dmac == 1) {
		switch (dma->config.stream) {
		case 0:
			clear_bits(DMA1_LISR, DMA_TEIF0);
			irq = DMA1_Stream0_IRQn;
			break;
		case 1:
			clear_bits(DMA1_LISR, DMA_TEIF1);
			irq = DMA1_Stream1_IRQn;
			break;
		case 2:
			clear_bits(DMA1_LISR, DMA_TEIF2);
			irq = DMA1_Stream2_IRQn;
			break;
		case 3:
			clear_bits(DMA1_LISR, DMA_TEIF3);
			irq = DMA1_Stream3_IRQn;
			break;

		default:
			return -ENOTSUP;
		}

	irq_set_priority(irq, DMA_IRQ_PRIO);
	irq_enable(irq);

	set_bits(DMA1_SxCR(dma->config.stream), DMA_TCIE);
	} else {
		/* currently only dma1 is supported*/
		return -ENOTSUP;
	}

	return 0;
}

/* implement if needed
 * static int dma_resume(struct dma *dma);
 * static int dma_remove(struct dma *dma);
 */

static struct dma_ops ops = {
	.configure = dma_set_config,
	.set_data_cfg = dma_set_data_config,
	.enable = dma_en,
	.pause = dma_disable,
	.resume = dma_en,
	.interrupt_enable = dma_enable_interrupt
};

int dma_init(struct dma *dma, uint32_t dmac, uint32_t stream, uint32_t channel)
{
	if (dma == NULL)
		return -ENODEV;

	dma->config.dmac = dmac;
	dma->config.stream = stream;
	dma->config.channel = channel;

	dma->ops = &ops;

	if (dma->config.dmac == 1)
		set_bits(RCC_AHB1ENR, RCC_DMA1EN);
	else
		return -ENOTSUP;

	return 0;
}
