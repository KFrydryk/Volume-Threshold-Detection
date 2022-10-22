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

/* clock defines */
#define RCC_BASE 0x40023800
#define RCC_CR (RCC_BASE + 0x00)
#define RCC_PLLCFGR (RCC_BASE + 0x04)
#define RCC_CFGR (RCC_BASE + 0x08)

/* flash defines */
#define FLASH_IFACE_BASE 0x40023C00
#define FLASH_ACR (FLASH_IFACE_BASE + 0x00)

#endif
