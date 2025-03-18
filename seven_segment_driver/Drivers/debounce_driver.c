#include "debounce_driver.h"

static inline bool GPIO_DebounceReadPin(GPIO_TypeDef *port, uint16_t pin) { // polled with a timer ISR
	static uint32_t State = 0;
	State = (State << 1) | HAL_GPIO_ReadPin(port, pin) | 0xFFFE0000;
	if (State == 0xFFFF0000) {
		return true;
	}
	return false;
}

