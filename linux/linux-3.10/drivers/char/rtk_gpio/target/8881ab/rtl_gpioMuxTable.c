#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/init.h>
#include <linux/version.h>
#include <asm/delay.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#endif
#include "../../rtl_gpiocommon.h"

#define PIN_MUX_SEL_1		0xB8000040	
#define PIN_MUX_SEL_2		0xB8000044
#define PIN_MUX_SEL_3		0xB800004C


/* CONFIG MACRO */
//#undef CONFIG_P0_RGMII 			//port0 RGMII
#define CONFIG_P0_RGMII
#undef CONFIG_I2S					//I2S support
#undef CONFIG_MCS1					//sdarm2
#define CONFIG_RTL_PCIE				//pcie wifi need 
#define CONFIG_SERIAL_RTL_UART0
#undef CONFIG_SF_CS1				// spiflash 2
#undef CONFIG_NF_CE1				// nandflash 2

/* list macro need check */
#undef CONFIG_EXT_HW_RESET
#undef CONFIG_LED_SCAN

static PinMuxTbl MuxTable[] = 
{
/* pin mux sel1 */
#if (!defined(CONFIG_P0_RGMII) && !defined(CONFIG_MTD_NAND))
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x1C,{GPIO_ID('F',5),0xC},0x0},					/*bit2~4*/
#endif
#if !defined(CONFIG_P0_RGMII)
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x1C,{GPIO_ID('F',6),0xC},0x0},					/*bit2~4*/ 
#endif
/* bit 5 start */
#if !defined(CONFIG_SERIAL_RTL_UART0)
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x20,{GPIO_ID('B',0),0x20},0x0},					/*bit5*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x20,{GPIO_ID('A',7),0x20},0x0},					/*bit5*/
#endif
/* bit 5 end */
#if !defined(CONFIG_RTL_PCIE)
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x40,{GPIO_ID('B',1),0x40},0x0},					/*bit6*/
#endif
#if (!defined(CONFIG_P0_RGMII) && !defined(CONFIG_MTD_NAND))
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',0),0x180},0x0},					/*bit7~9*/		
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',1),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',2),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',3),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',4),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',5),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',6),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('E',7),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('F',0),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('F',1),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('F',2),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('F',3),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x380,{GPIO_ID('F',4),0x180},0x0},					/*bit7~9*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',0),0xC00},0x0},					/*bit10~11*/	
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',1),0xC00},0x0},					/*bit10~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',2),0xC00},0x0},					/*bit10~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',3),0xC00},0x0},					/*bit10~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',4),0xC00},0x0},					/*bit10~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',5),0xC00},0x0},					/*bit10~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',6),0xC00},0x0},					/*bit10~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00,{GPIO_ID('G',7),0xC00},0x0},					/*bit10~11*/
#endif
#if (!defined(CONFIG_MTD_NAND) && !defined(CONFIG_RTL819X_SPI_FLASH))
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x3000,{GPIO_ID('A',1),0x3000},0x0},				/*bit12~13*/	
#endif
#if !defined(CONFIG_MCS1)
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x30000,{GPIO_ID('A',0),0x30000},0x0},				/*bit16~17*/
#endif
#if (!defined(CONFIG_MTD_NAND) && !defined(CONFIG_RTL819X_SPI_FLASH))
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC0000,{GPIO_ID('C',6),0xC0000},0x0},				/*bit18~19*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x300000,{GPIO_ID('C',1),0x300000},0x0},			/*bit20~21*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC00000,{GPIO_ID('C',2),0xC00000},0x0},			/*bit22~23*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x3000000,{GPIO_ID('C',3),0x3000000},0x0},			/*bit24~25*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0xC000000,{GPIO_ID('C',4),0xC000000},0x0},			/*bit26~27*/
{PIN_GPIO_MODE,PIN_MUX_SEL_1,0x30000000,{GPIO_ID('C',5),0x30000000},0x0},		/*bit28~29*/
#endif
/* pin mux sel2 */
#if !defined(CONFIG_I2S)
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x7,{GPIO_ID('B',2),0x3},0x0},						/*bit0~2*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x38,{GPIO_ID('B',3),0x18},0x0},					/*bit3~5*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x1C0,{GPIO_ID('B',4),0xC0},0x0},					/*bit6~8*/
#endif
#if !defined(CONFIG_EXT_HW_RESET)
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0xE00,{GPIO_ID('B',5),0x600},0x0},					/*bit9~11*/
#endif
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x3000,{GPIO_ID('B',6),0x3000},0x0},				/*bit12~13*/
/* D0 to D5 need check */
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x18000,{GPIO_ID('D',0),0x18000},0x0},				/*bit15~16*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x60000,{GPIO_ID('D',1),0x60000},0x0},				/*bit17~18*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x180000,{GPIO_ID('D',2),0x180000},0x0},			/*bit19~20*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x600000,{GPIO_ID('D',3),0x600000},0x0},			/*bit21~22*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x1800000,{GPIO_ID('D',4),0x1800000},0x0},			/*bit23~24*/
{PIN_GPIO_MODE,PIN_MUX_SEL_2,0x6000000,{GPIO_ID('D',5),0x6000000},0x0},			/*bit25~26*/
/* pin mux sel3 */
#if (!defined(CONFIG_I2S) && !defined(CONFIG_USING_JTAG))
{PIN_GPIO_MODE,PIN_MUX_SEL_3,0xF0,{GPIO_ID('A',3),0x60},0x0},					/*bit4~7*/
#endif
#if (!defined(CONFIG_I2S) && !defined(CONFIG_USING_JTAG) && !defined(CONFIG_SERIAL_RTL_UART1))
{PIN_GPIO_MODE,PIN_MUX_SEL_3,0xF,{GPIO_ID('A',2),0x6},0x0},						/*bit0~3*/
{PIN_GPIO_MODE,PIN_MUX_SEL_3,0xF00,{GPIO_ID('A',4),0x600},0x0},					/*bit8~11*/
{PIN_GPIO_MODE,PIN_MUX_SEL_3,0xF000,{GPIO_ID('A',5),0x6000},0x0},				/*bit12~15*/
{PIN_GPIO_MODE,PIN_MUX_SEL_3,0xF0000,{GPIO_ID('A',6),0x60000},0x0},				/*bit16~19*/
#endif
};


/* test */
#ifdef __KERNEL__
#ifdef CONFIG_RTL_NEW_GPIO_API_TEST
static uint32 pinmuxsel1,pinmuxsel2,pinmuxsel3;

void getPinMuxInitalVal(void)
{
	pinmuxsel1 = REG32(PIN_MUX_SEL_1);
	pinmuxsel2 = REG32(PIN_MUX_SEL_2);	
	pinmuxsel3 = REG32(PIN_MUX_SEL_3);
	return;
}

void setPinMuxInitalVal(void)
{
	REG32(PIN_MUX_SEL_1) = pinmuxsel1;
	REG32(PIN_MUX_SEL_2) = pinmuxsel2;
	REG32(PIN_MUX_SEL_3) = pinmuxsel3;
	return;
}
#endif

int getPinMuxVal(uint32 gpioId,uint32* pData)
{	
	int i;
	for(i = 0;i < sizeof(MuxTable)/sizeof(PinMuxTbl);i++){
		if(gpioId == MuxTable[i].gpiopin.gpionum){
			*pData = REG32(MuxTable[i].muxReg) & MuxTable[i].muxBitMask;
			break;
		}
	}
	
	if(i == sizeof(MuxTable)/sizeof(PinMuxTbl)){
		gpioPrintf("%s:%d\n",__func__,__LINE__);
		return FAILED;
	}
	return SUCCESS;
}


int setPinMuxVal(uint32 gpioId)
{
	int i;
	
	for(i = 0;i < sizeof(MuxTable)/sizeof(PinMuxTbl);i++){
		if(gpioId == MuxTable[i].gpiopin.gpionum){
			if((REG32(MuxTable[i].muxReg) & MuxTable[i].muxBitMask) == MuxTable[i].gpiopin.muxBitVal)
				return SUCCESS;
			REG32(MuxTable[i].muxReg) = REG32(MuxTable[i].muxReg) & (~(MuxTable[i].muxBitMask)) | MuxTable[i].gpiopin.muxBitVal;
			break;
		}
	}

	if(i == sizeof(MuxTable)/sizeof(PinMuxTbl)){
		gpioPrintf("%s:%d\n",__func__,__LINE__);
		return FAILED;
	}
}
#endif

int checkPinMuxVal(uint32 gpioId,uint32 data)
{
	int j;
	for(j = 0;j < sizeof(MuxTable)/sizeof(PinMuxTbl);j++){
		if(gpioId == MuxTable[j].gpiopin.gpionum)
			break;
	}
	if(j == sizeof(MuxTable)/sizeof(PinMuxTbl)){
		//gpioDebug("GPIO%c%d not exist in MuxTable\n",port,pin);
		return FAILED;
	}

	if(data != (MuxTable[j].muxBitMask & MuxTable[j].gpiopin.muxBitVal)){
		return FAILED;
	}
	return SUCCESS;
}

int checkPinExist(char port,uint32 pin)
{
	int j;
	for(j = 0;j < sizeof(MuxTable)/sizeof(PinMuxTbl);j++){
		if(GPIO_ID(port,pin) == MuxTable[j].gpiopin.gpionum)
			break;
	}
	if(j == sizeof(MuxTable)/sizeof(PinMuxTbl)){
		gpioDebug("GPIO%c%d not exist in MuxTable\n",port,pin);
		return FAILED;
	}
	return SUCCESS;
}


#ifdef CONFIG_RTL_NEW_GPIO_API_TEST
//check
#define RESETPIN		GPIO_ID('A',4)
#define WPSPIN			GPIO_ID('A',3)

void getRestWpsPin(uint32 *resetPin,uint32 *wpsPin)
{
	*resetPin = RESETPIN;
	*wpsPin = WPSPIN;
}
#endif

