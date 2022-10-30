#include "include/platform_defs.h"
#include "include/platform_init.h"
#include <stdint.h>

/* RCC_CR */
#define HSEON (1 << 16)
#define HSRDY (1 << 17)
#define PLLON (1 << 24)
#define PLLRDY (1 << 25)

/* RCC_PLLCFGR */
#define PLL_Q_7 (7 << 24)
#define PLLSRC (1 << 22) /* set for HSE, unset HSI */
#define PLLP2 (0<<16) /* Main PLL (PLL) division factor for main system clock */
#define PLLN_168 (168 << 6)
#define PLLM_4 (4 << 0)

/* RCC_CFGR */
#define PPRE1_4 (5 << 10)
#define PPRE2_2 (4 << 13)
#define SW_PLL (2 << 0)
#define SWS_PLL (2 << 2)

#define FLASH_ACR_ICEN (1 << 9)
#define FLASH_ACR_DCEN (1 << 10)
#define FLASH_ACR_PRFTEN (1 << 8)
#define FLASH_ACR_LATENCY_4WS (1 << 2)

void platform_init(void)
{
	/* HSE clock enable */
	write_reg(RCC_CR, read_reg(RCC_CR) | HSEON);

	/* wait until enabled */
	while (!(read_reg(RCC_CR) & HSRDY)) {
	}

	/* setup flash */
	write_reg(FLASH_ACR, FLASH_ACR_ICEN |
		  FLASH_ACR_DCEN |
		  FLASH_ACR_PRFTEN |
		  FLASH_ACR_LATENCY_4WS);

	/* Set HSE as PLL source, set M, N, P, Q miltipliers and dividers
	 *Fvco = Fpll_in * (PLLN/PLLM)
	 *Fpll_out = Fvco / PLLP
	 *Fusb,sdio,rng = Fvco / PLLQ
	 */
	write_reg(RCC_PLLCFGR, PLL_Q_7 | PLLSRC | PLLP2 | PLLN_168 | PLLM_4);
	write_reg(RCC_CR, read_reg(RCC_CR) | PLLON);
	/* wait until enabled */
	while (!(read_reg(RCC_CR) & PLLRDY)) {
	}

	/* set prescalers */
	write_reg(RCC_CFGR, read_reg(RCC_CFGR) | PPRE1_4 | PPRE2_2 | SW_PLL);
	/* wait until enabled */
	while (!(read_reg(RCC_CFGR) | SWS_PLL)) {
	}

	/* TODO: Do we need other stuff enabled? FPU? */
}
