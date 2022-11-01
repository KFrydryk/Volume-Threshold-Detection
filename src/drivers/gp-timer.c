#include <errno.h>
#include "include/gp-timer.h"
#include "platform_defs.h"

static int gp_timer_reset(struct gp_timer *tmr)
{
	if (tmr == NULL)
		return -ENODEV;

	if (tmr->instance == 2) {
		set_bits(RCC_APB1RSTR, RCC_RST_TIM2);
		clear_bits(RCC_APB1RSTR, RCC_RST_TIM2);
	} else if (tmr->instance == 5) {
		set_bits(RCC_APB1RSTR, RCC_RST_TIM5);
		clear_bits(RCC_APB1RSTR, RCC_RST_TIM5);
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static int gp_timer_enable(struct gp_timer *tmr)
{
	if (tmr == NULL)
		return -ENODEV;

	if (tmr->instance == 2)
		set_bits(TIM2_CR1, TIM_CEN);
	else if (tmr->instance == 5)
		set_bits(TIM5_CR1, TIM_CEN);
	else
		return -ENOTSUP;

	return 0;
}

int gp_timer_start(struct gp_timer *tmr)
{
	uint32_t tim_egr_addr;
	uint32_t tim_dier_addr;

	if (tmr == NULL)
		return -ENODEV;

	if (tmr->instance == 2) {
		tim_egr_addr = TIM2_EGR;
		tim_dier_addr = TIM2_DIER;
	} else if (tmr->instance == 5) {
		tim_egr_addr = TIM5_EGR;
		tim_dier_addr = TIM5_DIER;
	} else {
		return -ENOTSUP;
	}

	/* Update generation - reset timer and apply settings*/
	set_bits(tim_egr_addr, TIM_UG);
	/* Enable HW interrupt */
	set_bits(tim_dier_addr, TIM_UIE);
	/* enable timer */
	gp_timer_enable(tmr);

	return 0;
}

int gp_timer_stop(struct gp_timer *tmr)
{
	if (tmr == NULL)
		return -ENODEV;

	if (tmr->instance == 2)
		clear_bits(TIM2_CR1, TIM_CEN);
	else if (tmr->instance == 5)
		clear_bits(TIM5_CR1, TIM_CEN);
	else
		return -ENOTSUP;

	return 0;
}

int gp_timer_set_threshold(struct gp_timer *tmr)
{
	if (tmr == NULL)
		return -ENODEV;

	if (tmr->instance == 2)
		write_reg(TIM2_ARR, tmr->threshold);
	else if (tmr->instance == 5)
		write_reg(TIM5_ARR, tmr->threshold);
	else
		return -ENOTSUP;

	return 0;
}

int gp_timer_set_prescaler(struct gp_timer *tmr)
{
	if (tmr == NULL)
		return -ENODEV;

	if (tmr->instance == 2)
		write_reg(TIM2_PSC, tmr->prescaler);
	else if (tmr->instance == 5)
		write_reg(TIM5_PSC, tmr->prescaler);
	else
		return -ENOTSUP;

	return 0;
}


int gp_timer_configure(struct gp_timer *tmr, uint16_t presc, uint32_t thr)
{
	if (tmr == NULL)
		return -ENODEV;

	tmr->prescaler = presc;
	tmr->threshold = thr;

	gp_timer_set_prescaler(tmr);
	gp_timer_set_threshold(tmr);

	return 0;
}

int gp_timer_init(struct gp_timer *tmr, int inst)
{
	int ret;

	tmr->instance = inst;

	if (tmr == NULL)
		return -ENODEV;

	/* Enable the TIM clock */
	if (inst == 2)
		set_bits(RCC_APB1ENR, RCC_APB1ENR_TIM2EN);
	else if (inst == 5)
		set_bits(RCC_APB1ENR, RCC_APB1ENR_TIM5EN);
	else
		return -ENOTSUP;

	/* set irq */
	if (inst == 2)  {
		irq_set_priority(TIM2_IRQn, 0x03);
		irq_enable(TIM2_IRQn);
	} else if (inst == 5)  {
		irq_set_priority(TIM5_IRQn, 0x03);
		irq_enable(TIM5_IRQn);
	} else {
		/* log */
	}

	ret = gp_timer_stop(tmr);
	if (ret < 0)
		return ret;

	ret = gp_timer_reset(tmr);
	if (ret < 0)
		return ret;

	return 0;
}
