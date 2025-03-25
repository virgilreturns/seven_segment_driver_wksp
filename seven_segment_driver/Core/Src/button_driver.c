#include "button_driver.h"



/* GPIO_PinState GPIO_DigitalRead(Switch_TypeDef* button) {

	static uint8_t raw = HAL_GPIO_ReadPin(button->port, button->pin);
	if (raw == 0) button->integrator > 0 ? button->integrator--;
	else if (button->integrator < INTEGRATOR_MAXIMUM) button->integrator++;

	if (button->integrator == 0)
		return GPIO_PIN_RESET;
	else if (button->integrator >= INTEGRATOR_MAXIMUM) {
		button->integrator = INTEGRATOR_MAXIMUM;
		return GPIO_PIN_SET;
	}
}
*/

