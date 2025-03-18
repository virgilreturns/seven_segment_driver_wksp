#include "GPIO_driver.h"


// ISR should call every CHECK_MSEC
static inline bool GPIO_DigitalRead(GPIO_TypeDef* port, uint16_t pin) {
	static bool isDebounced = false;
	static



	


	//debounce control, change state type or return (condition) to fine tune
	static uint32_t State = 0;
	State = (State << 1) | HAL_GPIO_ReadPin(port, pin) | 0xFFFE0000;
	return (State == 0xFFFF0000);
}

