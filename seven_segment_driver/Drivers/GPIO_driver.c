#include "GPIO_driver.h"

static inline bool GPIO_DigitalRead(GPIO_TypeDef *port, uint16_t pin) { // polled with a timer ISR
	static uint32_t State = 0;
	State = (State << 1) | HAL_GPIO_ReadPin(port, pin) | 0xFFFE0000;
	return (State == 0xFFFF0000) {
}

