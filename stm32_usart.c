#include <stdio.h>
#include "stm32f30x_gpio.h"
#include "stm32f30x_usart.h"

void usart_init() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// Datasheet -> Alternate functions for port D -> PD5
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_7);

	// Configure pin in output push/pull mode
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_InitTypeDef usart1_init_struct;
	usart1_init_struct.USART_BaudRate = 9600;
	usart1_init_struct.USART_WordLength = USART_WordLength_8b;
	usart1_init_struct.USART_StopBits = USART_StopBits_1;
	usart1_init_struct.USART_Parity = USART_Parity_No ;
	usart1_init_struct.USART_Mode = USART_Mode_Tx;
	usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &usart1_init_struct);
	USART_Cmd(USART2, ENABLE);
}

int main()
{
	usart_init();
	USART_SendData(USART2, 'W');
	// ...Or press 'Reset'
	while (1) { }
}