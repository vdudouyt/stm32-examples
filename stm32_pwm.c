#include <stdio.h>
#include "stm32f30x_gpio.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_misc.h"
#include "math.h"

void gpio_init() {
  // Enable GPIO Peripheral clock
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_2);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void tim1_init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 2000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 500;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &timerInitStructure);
}

void tim1_pwm_init()
{
	TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;

    outputChannelInit.TIM_Pulse = 300; // preset pulse width 0..pwm_period
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High; // Pulse polarity
    //    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_Low;
    outputChannelInit.TIM_OCIdleState = TIM_OCIdleState_Set;

    // These settings must be applied on the timer 1.
    outputChannelInit.TIM_OutputNState = TIM_OutputNState_Disable;
    outputChannelInit.TIM_OCNPolarity = TIM_OCNPolarity_High;
    outputChannelInit.TIM_OCNIdleState = TIM_OCIdleState_Set;

    TIM_OC1Init(TIM1, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, DISABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}

void tim2_init()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 40000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 5000;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE);
}

int fade_fun(int arg)
{
	if(arg < 2500)
		return arg/20;
	else
		return 250 - arg/20;
}

int main()
{
  gpio_init();
  tim1_init();
  tim1_pwm_init();
  tim2_init();
  while (1) {
	  TIM_SetCompare1(TIM1, fade_fun(TIM_GetCounter(TIM2)));
  }
}

// ----------------------------------------------------------------------------
