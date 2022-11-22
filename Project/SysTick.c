/**
 * @file SysTick.h
 * @author D. Funke
 * @brief Module to configure the SysTick interrupt
 * @date 2022-11-19
 * 
 */

void SysTick_init(void)
{

}

void SysTick_Handler(void)
{
    event_publish(&SysTick_event, NULL);
}