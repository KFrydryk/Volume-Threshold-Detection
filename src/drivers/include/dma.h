#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include <stdbool.h>
#include "platform_defs.h"
#include <errno.h>

/* Experimental API, might change!*/

#define DMA_IRQ_PRIO 3

struct dma;

enum dma_dir {
	DMA_PER_TO_MEM,
	DMA_MEM_TO_PER,
	DMA_MEM_TO_MEM
};

enum dma_d_align {
	DMA_ALIGN_BYTE,
	DMA_ALIGN_H_WORD,
	DMA_ALIGN_WORD
};

enum dma_prio {
	DMA_PRIO_LOW,
	DMA_PRIO_MEDIUM,
	DMA_PRIO_HIGH,
	DMA_PRIO_V_HIGH
};

struct dma_config {
	uint32_t dmac;
	uint32_t stream;
	uint32_t channel;
	enum dma_dir dir;
	bool p_inc; /* increment peripheral mem ptr */
	bool m_inc; /* increment memory pointer */
	enum dma_d_align p_align; /* peripheral data alignment */
	enum dma_d_align m_align; /* memory data alignment */
	bool circ; /* enable circular buffer mode */
	enum dma_prio priority;
	bool fifo_mode;
	bool en;
};

struct dma_ops {
	int (*configure)(struct dma *dma, enum dma_dir dir, bool p_inc, bool m_inc,
			 enum dma_d_align p_align, enum dma_d_align m_align, bool circ,
			 enum dma_prio prio, bool fifo_mode);
	int (*set_data_cfg)(struct dma *dma, void *src_ptr, void *dst_cfg, size_t size);
	int (*enable)(struct dma *dma);
	int (*pause)(struct dma *dma);
	int (*resume)(struct dma *dma);
	int (*remove)(struct dma *dma);
	/* NOTE: IRQ handler has to be defined separately!
	 * TODO: add api to bind handler function as irq callback
	 */
	int (*interrupt_enable)(struct dma *dma);
};

/* for clarity declare only currently important parameters */
struct dma {
	struct dma_config config;
	struct dma_ops *ops;
};

int dma_init(struct dma *dma, uint32_t dmac, uint32_t stream, uint32_t channel);

static inline int dma_configure(struct dma *dma, enum dma_dir dir, bool p_inc, bool m_inc,
				enum dma_d_align p_align, enum dma_d_align m_align, bool circ,
				enum dma_prio prio, bool fifo_mode)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->configure(dma, dir, p_inc, m_inc, p_align, m_align, circ, prio, fifo_mode);
}

static inline int dma_set_data_cfg(struct dma *dma, void *src, void *dst, size_t size)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->set_data_cfg(dma, src, dst, size);
}

static inline int dma_enable(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->enable(dma);
}

static inline int dma_pause(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->pause(dma);
}

static inline int dma_resume(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->resume(dma);
}

static inline int dma_remove(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->remove(dma);
}

static inline int dma_int_enable(struct dma *dma)
{
	if (dma == NULL)
		return -ENODEV;

	return dma->ops->interrupt_enable(dma);
}

#endif
