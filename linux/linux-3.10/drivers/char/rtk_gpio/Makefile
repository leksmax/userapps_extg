#
# Makefile for RTK_GPIO Modem .
#
# See the README file in this directory for more info. <winfred_wang@realsil.com.cn>
#
ifeq ($(CONFIG_RTL_8198C),y)
TARGET=target/98C
endif

obj-$(CONFIG_RTL_NEW_GPIO_API) += rtk_gpio.o

rtk_gpio-y := rtl_gpioProc.o rtl_gpioOps.o rtl_gpioOpsApi.o rtl_pinMuxOps.o rtl_gpioInterrupt.o rtl_gpioInterruptHandler.o
rtk_gpio-y += $(TARGET)/rtl_gpioMuxTable.o
rtk_gpio-$(CONFIG_RTL_NEW_GPIO_API_TEST) += test.o 
