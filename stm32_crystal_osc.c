void clock_init()
{
    /*RCC system reset(for debug purpose) */
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    int HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus != SUCCESS)
    {
    	return;
    }

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08) {}
}