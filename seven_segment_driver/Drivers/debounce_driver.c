#include "debounce_driver.h"

bool debounce() { // polled with a timer ISR
	static uint32_t State = 0;
	State = (State << 1) | HAL_GPIO_ReadPin() | 0xFFFE0000;
	if (State == 0xFFFF0000) {
		return true;
	}
	return false;
}
