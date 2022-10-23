/* 
 * Basic start file example
 * Jan Swanepoel, 2019
 * 
*/

// Create references to symbols defined in the linker script 
extern unsigned int _data_start;	
extern unsigned int _data_end;
extern unsigned int _data_load;
extern unsigned int _bss_start;
extern unsigned int _bss_end;

#define __bss_start__ _bss_start
#define __bss_end__ _bss_end

void startup();			// Function prototype (forward declaration) for startup function
int main();			// Function prototype for main function

// Default interrupt handler. All notimplemented interrupts are aliases to this function.
static void __attribute__ ((interrupt))
default_handler(void)
{
    while (1) {
    }
}

void __attribute__ ((interrupt, weak, alias("default_handler")))
NMI_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
HardFault_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
MemManage_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
BusFault_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
UsageFault_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
__Reserved_0x1C_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
__Reserved_0x20_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
__Reserved_0x24_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
__Reserved_0x28_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
SVC_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DebugMon_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
__Reserved_0x34_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
PendSV_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
SysTick_Handler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
WWDG_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
PVD_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TAMP_STAMP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
RTC_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
FLASH_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
RCC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream6_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
ADC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN1_TX_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN1_RX0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN1_RX1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN1_SCE_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI9_5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM1_BRK_TIM9_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM1_UP_TIM10_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM1_TRG_COM_TIM11_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM1_CC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
I2C1_EV_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
I2C1_ER_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
I2C2_EV_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
I2C2_ER_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
SPI1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
SPI2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
USART1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
USART2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
USART3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
EXTI15_10_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
RTC_Alarm_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
OTG_FS_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM8_BRK_TIM12_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM8_UP_TIM13_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM8_TRG_COM_TIM14_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM8_CC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA1_Stream7_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
FSMC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
SDIO_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
SPI3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
UART4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
UART5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM6_DAC_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
TIM7_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream2_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream3_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream4_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
ETH_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
ETH_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN2_TX_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN2_RX0_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN2_RX1_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CAN2_SCE_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
OTG_FS_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream5_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream6_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DMA2_Stream7_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
USART6_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
I2C3_EV_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
I2C3_ER_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
OTG_HS_EP1_OUT_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
OTG_HS_EP1_IN_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
OTG_HS_WKUP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
OTG_HS_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
DCMI_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
CRYP_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
HASH_RNG_IRQHandler(void);

void __attribute__ ((interrupt, weak, alias("default_handler")))
FPU_IRQHandler(void);

// Below we create an array of pointers which would form our vector table
// We use __attribute__ ((section(".vectors"))) to tell the compiler that we want the
// array to be placed in a memory section that we call ".vectors"
unsigned int * vectors[] __attribute__ ((section(".vectors"))) = 
{
	(unsigned int *)	0x20020000,  	// Address of top of stack. 20kB = 1024 x 20 = 20480 bytes = 0x5000 
	(unsigned int *)    startup,     	// Address of the reset handler which is also our startup function
	(unsigned int *)    NMI_Handler,
	(unsigned int *)    HardFault_Handler,
	(unsigned int *)    MemManage_Handler,
	(unsigned int *)    BusFault_Handler,
	(unsigned int *)    UsageFault_Handler,
	(unsigned int *)    __Reserved_0x1C_Handler,
	(unsigned int *)    __Reserved_0x20_Handler,
	(unsigned int *)    __Reserved_0x24_Handler,
	(unsigned int *)    __Reserved_0x28_Handler,
	(unsigned int *)    SVC_Handler,
	(unsigned int *)    DebugMon_Handler,
	(unsigned int *)    __Reserved_0x34_Handler,
	(unsigned int *)    PendSV_Handler,
	(unsigned int *)    SysTick_Handler,
	(unsigned int *)    WWDG_IRQHandler,
	(unsigned int *)    PVD_IRQHandler,
	(unsigned int *)    TAMP_STAMP_IRQHandler,
	(unsigned int *)    RTC_WKUP_IRQHandler,
	(unsigned int *)    FLASH_IRQHandler,
	(unsigned int *)    RCC_IRQHandler,
	(unsigned int *)    EXTI0_IRQHandler,
	(unsigned int *)    EXTI1_IRQHandler,
	(unsigned int *)    EXTI2_IRQHandler,
	(unsigned int *)    EXTI3_IRQHandler,
	(unsigned int *)    EXTI4_IRQHandler,
	(unsigned int *)    DMA1_Stream0_IRQHandler,
	(unsigned int *)    DMA1_Stream1_IRQHandler,
	(unsigned int *)    DMA1_Stream2_IRQHandler,
	(unsigned int *)    DMA1_Stream3_IRQHandler,
	(unsigned int *)    DMA1_Stream4_IRQHandler,
	(unsigned int *)    DMA1_Stream5_IRQHandler,
	(unsigned int *)    DMA1_Stream6_IRQHandler,
	(unsigned int *)    ADC_IRQHandler,
	(unsigned int *)    CAN1_TX_IRQHandler,
	(unsigned int *)    CAN1_RX0_IRQHandler,
	(unsigned int *)    CAN1_RX1_IRQHandler,
	(unsigned int *)    CAN1_SCE_IRQHandler,
	(unsigned int *)    EXTI9_5_IRQHandler,
	(unsigned int *)    TIM1_BRK_TIM9_IRQHandler,
	(unsigned int *)    TIM1_UP_TIM10_IRQHandler,
	(unsigned int *)    TIM1_TRG_COM_TIM11_IRQHandler,
	(unsigned int *)    TIM1_CC_IRQHandler,
	(unsigned int *)    TIM2_IRQHandler,
	(unsigned int *)    TIM3_IRQHandler,
	(unsigned int *)    TIM4_IRQHandler,
	(unsigned int *)    I2C1_EV_IRQHandler,
	(unsigned int *)    I2C1_ER_IRQHandler,
	(unsigned int *)    I2C2_EV_IRQHandler,
	(unsigned int *)    I2C2_ER_IRQHandler,
	(unsigned int *)    SPI1_IRQHandler,
	(unsigned int *)    SPI2_IRQHandler,
	(unsigned int *)    USART1_IRQHandler,
	(unsigned int *)    USART2_IRQHandler,
	(unsigned int *)    USART3_IRQHandler,
	(unsigned int *)    EXTI15_10_IRQHandler,
	(unsigned int *)    RTC_Alarm_IRQHandler,
	(unsigned int *)    OTG_FS_WKUP_IRQHandler,
	(unsigned int *)    TIM8_BRK_TIM12_IRQHandler,
	(unsigned int *)    TIM8_UP_TIM13_IRQHandler,
	(unsigned int *)    TIM8_TRG_COM_TIM14_IRQHandler,
	(unsigned int *)    TIM8_CC_IRQHandler,
	(unsigned int *)    DMA1_Stream7_IRQHandler,
	(unsigned int *)    FSMC_IRQHandler,
	(unsigned int *)    SDIO_IRQHandler,
	(unsigned int *)    TIM5_IRQHandler,
	(unsigned int *)    SPI3_IRQHandler,
	(unsigned int *)    UART4_IRQHandler,
	(unsigned int *)    UART5_IRQHandler,
	(unsigned int *)    TIM6_DAC_IRQHandler,
	(unsigned int *)    TIM7_IRQHandler,
	(unsigned int *)    DMA2_Stream0_IRQHandler,
	(unsigned int *)    DMA2_Stream1_IRQHandler,
	(unsigned int *)    DMA2_Stream2_IRQHandler,
	(unsigned int *)    DMA2_Stream3_IRQHandler,
	(unsigned int *)    DMA2_Stream4_IRQHandler,
	(unsigned int *)    ETH_IRQHandler,
	(unsigned int *)    ETH_WKUP_IRQHandler,
	(unsigned int *)    CAN2_TX_IRQHandler,
	(unsigned int *)    CAN2_RX0_IRQHandler,
	(unsigned int *)    CAN2_RX1_IRQHandler,
	(unsigned int *)    CAN2_SCE_IRQHandler,
	(unsigned int *)    OTG_FS_IRQHandler,
	(unsigned int *)    DMA2_Stream5_IRQHandler,
	(unsigned int *)    DMA2_Stream6_IRQHandler,
	(unsigned int *)    DMA2_Stream7_IRQHandler,
	(unsigned int *)    USART6_IRQHandler,
	(unsigned int *)    I2C3_EV_IRQHandler,
	(unsigned int *)    I2C3_ER_IRQHandler,
	(unsigned int *)    OTG_HS_EP1_OUT_IRQHandler,
	(unsigned int *)    OTG_HS_EP1_IN_IRQHandler,
	(unsigned int *)    OTG_HS_WKUP_IRQHandler,
	(unsigned int *)    OTG_HS_IRQHandler,
	(unsigned int *)    DCMI_IRQHandler,
	(unsigned int *)    CRYP_IRQHandler,
	(unsigned int *)    HASH_RNG_IRQHandler,
	(unsigned int *)    FPU_IRQHandler,
};

// The startup function, address was provided in the vector table	
void startup()
{
	volatile unsigned int *src, *dest;

	// Copy data section values from load time memory address (LMA) to their address in SRAM 
	for (src = &_data_load, dest = &_data_start; dest < &_data_end; src++, dest++) 
		*dest = *src;
	
	// Initialize all uninitialized variables (bss section) to 0
	for (dest = &_bss_start; dest < &_bss_end; dest++)
		*dest = 0;

	// Calling the main function
	main ();
	
	while(1);	// Normally main() should never return, but just incase we loop infinitely
}