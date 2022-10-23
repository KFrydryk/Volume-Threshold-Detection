#ifndef PLATFORM_DEFS_H
#define PLATFORM_DEFS_H

#include <stdint.h>

static inline uint32_t read_reg(uint32_t addr)
{
	return *(uint32_t *)addr;
}

static inline void write_reg(uint32_t addr, uint32_t val)
{
	*(uint32_t *) addr = val;
}

static inline void set_bits(uint32_t addr, uint32_t val)
{
	write_reg(addr, read_reg(addr) | val);
}

static inline void clear_bits(uint32_t addr, uint32_t val)
{
	write_reg(addr, read_reg(addr) & ~val);
}

/* clock defines */
#define RCC_BASE 0x40023800
#define RCC_CR (RCC_BASE + 0x00)
#define RCC_PLLCFGR (RCC_BASE + 0x04)
#define RCC_CFGR (RCC_BASE + 0x08)

/* flash defines */
#define FLASH_IFACE_BASE 0x40023C00
#define FLASH_ACR (FLASH_IFACE_BASE + 0x00)

/* GPIO defines */
#define GPIO_BASE 0x40020000
#define GPIOA_BASE (GPIO_BASE + 0x0000)
#define GPIOB_BASE (GPIO_BASE + 0x0400)
#define GPIOC_BASE (GPIO_BASE + 0x0800)
#define GPIOD_BASE (GPIO_BASE + 0x0C00)
#define GPIOE_BASE (GPIO_BASE + 0x1000)
#define GPIOF_BASE (GPIO_BASE + 0x1400)
#define GPIOG_BASE (GPIO_BASE + 0x1800)
#define GPIOH_BASE (GPIO_BASE + 0x1C00)
#define GPIOI_BASE (GPIO_BASE + 0x2000)
#define GPIOJ_BASE (GPIO_BASE + 0x2400)
#define GPIOK_BASE (GPIO_BASE + 0x2800)

#define GPIO_MODER 0x00
#define GPIO_OTYPER 0x04
#define GPIO_OSPEEDR 0x08
#define GPIO_PUPDR 0x0C
#define GPIO_IDR 0x10
#define GPIO_ODR 0x14
#define GPIO_BSRR 0x18
#define GPIO_LCKR 0x1C
#define GPIO_AFRL 0x20
#define GPIO_AFRH 0x24

#define RCC_AHB1ENR (RCC_BASE + 0x30)


#endif
