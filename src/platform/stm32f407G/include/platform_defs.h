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
#define RCC_APB1ENR (RCC_BASE + 0x40)
#define RCC_APB2ENR (RCC_BASE + 0x44)
#define RCC_AHB1ENR (RCC_BASE + 0x30)
#define RCC_APB1RSTR (RCC_BASE + 0x20)

#define RCC_PLLI2S (RCC_BASE + 0x84)
#define RCC_PLLI2SON (1 << 26)
#define RCC_PLLI2SRDY (1 << 27)
#define PLLI2SR(x) (x << 28)
#define PLLI2SN(x) (x << 6)

#define RCC_APB1ENR_TIM2EN (1 << 0)
#define RCC_RST_TIM2 (1 << 6)

/* RCC_APB2ENR defines */
#define SYSCFGEN (1 << 14)

/* RCC_APB1ENR defines */
#define SPI1EN (1 << 12)
#define SPI2EN (1 << 14)
#define SPI3EN (1 << 15)

/* I2S defines */
#define I2S2_BASE 0x40003800
#define I2S3_BASE 0x40003C00
#define I2S2_CR2 (I2S2_BASE + 0x04)
#define I2S3_CR2 (I2S3_BASE + 0x04)
#define I2S2_I2SCFGR (I2S2_BASE + 0x1C)
#define I2S2_I2SPR (I2S2_BASE + 0x20)
#define I2S3_I2SCFGR (I2S3_BASE + 0x1C)
#define I2S3_I2SPR (I2S3_BASE + 0x20)

#define SPI_SETUP_I2S (1 << 11)
#define I2S_I2SE (1 << 10)
#define I2S_I2SCFG(x) (x << 8)
#define I2S_I2SSTD(x) (x << 4)
#define I2S_CKPOL (1 << 3)
#define I2S_DATLEN(x) (x << 1)
#define I2S_CHLEN (1 << 0)

#define I2S_MCKOE (1 << 9)
#define I2S_ODD (1 << 8)
#define I2S_I2SDIV(x) (x << 0)

#define I2S2_RXDMAEN (1 << 0)
#define I2S2_TXDMAEN (1 << 1)

/* syscfg defines */
#define SYSCFG_BASE 0x40013800
#define SYSCFG_EXTICR(x) SYSCFG_EXTICR ## x
#define SYSCFG_EXTICR1 (SYSCFG_BASE + 0x08)
#define SYSCFG_EXTICR2 (SYSCFG_BASE + 0x0C)
#define SYSCFG_EXTICR3 (SYSCFG_BASE + 0x10)
#define SYSCFG_EXTICR4 (SYSCFG_BASE + 0x14)


/* exti defines */
#define EXTI_BASE 0x40013C00
#define EXTI_IMR (EXTI_BASE + 0x00)
#define EXTI_RTSR (EXTI_BASE + 0x08)
#define EXTI_FTSR (EXTI_BASE + 0x0C)
#define EXTI_PR (EXTI_BASE + 0x14)

/* flash defines */
#define FLASH_IFACE_BASE 0x40023C00
#define FLASH_ACR (FLASH_IFACE_BASE + 0x00)

/* Timer defines */
#define TIM2_BASE 0x40000000
#define TIM2_CR1 (TIM2_BASE + 0x00)
#define TIM2_PSC (TIM2_BASE + 0x28)
#define TIM2_ARR (TIM2_BASE + 0x2C)
#define TIM2_EGR (TIM2_BASE + 0x14)
#define TIM2_DIER (TIM2_BASE + 0x0C)
#define TIM2_SR (TIM2_BASE + 0x10)

#define TIM_CEN (1 << 0)
#define TIM_UG (1 << 0)
#define TIM_UIE (1 << 0)
#define TIM_UIF (1 << 0)

/* DMA defines */
#define DMA1_BASE 0x40026000
#define DMA2_BASE 0x40026400

#define RCC_DMA1EN (1 << 21)
#define RCC_DMA2EN (1 << 22)

#define DMA1_LISR (DMA1_BASE + 0x00)
#define DMA1_HISR (DMA1_BASE + 0x04)
#define DMA2_LISR (DMA2_BASE + 0x00)
#define DMA2_HISR (DMA2_BASE + 0x04)
#define DMA1_LIFCR (DMA1_BASE + 0x08)
#define DMA1_SxCR(channel) (DMA1_BASE + 0x10 + 0x18 * channel)
#define DMA2_SxCR(channel) (DMA2_BASE + 0x10 + 0x18 * channel)
#define DMA1_SxNDTR(channel) (DMA1_BASE + 0x14 + 0x18 * channel)
#define DMA2_SxNDTR(channel) (DMA2_BASE + 0x14 + 0x18 * channel)
#define DMA1_SxPAR(channel) (DMA1_BASE + 0x18 + 0x18 * channel)
#define DMA2_SxPAR(channel) (DMA2_BASE + 0x18 + 0x18 * channel)
#define DMA1_SxM0AR(channel) (DMA1_BASE + 0x1C + 0x18 * channel)
#define DMA2_SxM0AR(channel) (DMA2_BASE + 0x1C + 0x18 * channel)
#define DMA1_SxM1AR(channel) (DMA1_BASE + 0x20 + 0x18 * channel)
#define DMA2_SxM1AR(channel) (DMA2_BASE + 0x20 + 0x18 * channel)
#define DMA1_SxFCR(channel) (DMA1_BASE + 0x24 + 0x18 * channel)
#define DMA2_SxFCR(channel) (DMA2_BASE + 0x24 + 0x18 * channel)

#define DMA_CHSEL(x) (x << 25)
#define DMA_PRIO(prio_level) (prio_level << 16)
#define DMA_MSIZE(size) (size << 13)
#define DMA_PSIZE(size) (size << 11)
#define DMA_MINC (1 << 10)
#define DMA_PINC (1 << 9)
#define DMA_CIRC (1 << 8)
#define DMA_DIR(dir) (dir << 6)
#define DMA_EN (1 << 0)

#define DMA_FIFO_EN (1 << 7)
#define DMA_TCIE (1 << 4)

#define DMA_TEIF0 (1 << 5)
#define DMA_TEIF1 (1 << 11)
#define DMA_TEIF2 (1 << 21)
#define DMA_TEIF3 (1 << 27)


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

/* irqs */
/* from ARMv7-M_ARM datasheet */
#define NVIC_BASE 0xE000E100
/* am not defining all of those just for consistency */
struct NVIC
{
	volatile uint32_t ISER[8U];
	uint32_t rsv0[24U];
	volatile uint32_t ICER[8U];
	uint32_t rsv1[24U];
	volatile uint32_t ISPR[8U];
	uint32_t rsv2[24U];
	volatile uint32_t ICPR[8U];
	uint32_t rsv3[24U];
	volatile uint32_t IABR[8U];
	uint32_t rsv4[56U];
	volatile uint8_t  IP[240U];
	uint32_t rsv5[644U];
	volatile  uint32_t STIR;
};
#define NVIC ((struct NVIC *) NVIC_BASE)

static inline void irq_enable(uint32_t irq_n)
{
	NVIC->ISER[irq_n / 32] = (0x01 << (irq_n % 32));
}

static inline void irq_set_priority(uint32_t irq_n, uint32_t prio)
{
	/* use only 8 priority levels */
	NVIC->IP[irq_n] = (prio << 5) % 255;
}


/* copied shamelesly from CMSIS header, not gonna retype this myself. */
enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
  CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  TIM8_BRK_TIM12_IRQn         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  TIM8_UP_TIM13_IRQn          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
  TIM8_TRG_COM_TIM14_IRQn     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                                    */
  DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                             */
  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
  UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
  TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  TIM7_IRQn                   = 55,     /*!< TIM7 global interrupt                                             */
  DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  ETH_IRQn                    = 61,     /*!< Ethernet global Interrupt                                         */
  ETH_WKUP_IRQn               = 62,     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
  CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
  CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
  CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
  CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
  OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  OTG_HS_EP1_OUT_IRQn         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
  OTG_HS_EP1_IN_IRQn          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
  OTG_HS_WKUP_IRQn            = 76,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
  OTG_HS_IRQn                 = 77,     /*!< USB OTG HS global interrupt                                       */
  DCMI_IRQn                   = 78,     /*!< DCMI global interrupt                                             */
  CRYP_IRQn                   = 79,     /*!< CRYP crypto global interrupt                                      */
  HASH_RNG_IRQn               = 80,     /*!< Hash and Rng global interrupt                                     */
  FPU_IRQn                    = 81      /*!< FPU global interrupt                                              */
  };


#endif
