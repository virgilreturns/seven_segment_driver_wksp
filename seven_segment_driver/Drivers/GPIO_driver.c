#include "GPIO_driver.h"


// ISR should call every CHECK_PERIOD ms
void GPIO_DigitalRead(Switch_TypeDef* switch) {

	static uint8_t raw = HAL_GPIO_ReadPin(switch->port, switch->pin);
	if (raw == 0) switch->integrator > 0 ? switch->integrator--;
	else if (switch->integrator < INTEGRATOR_MAXIMUM) switch->integrator++;

	if (switch->integrator == 0)
		return GPIO_PIN_RESET;
	else if (switch->integrator >= INTEGRATOR_MAXIMUM) {
		switch->integrator = INTEGRATOR_MAXIMUM;
		return GPIO_PIN_SET;
	}
}

