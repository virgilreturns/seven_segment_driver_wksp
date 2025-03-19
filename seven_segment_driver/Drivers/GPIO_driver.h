#include "main.h"
#define CHECK_PERIOD 5
#define DEBOUNCE_TIME 0.200 // seconds
#define INTEGRATOR_MAXIMUM ((CHECK_PERIOD)*(DEBOUNCE_TIME))


//using input pin struct for scalability
typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	uint8_t integrator;
	bool SwitchActivated;
} Switch_TypeDef;


bool GPIO_DigitalRead(GPIO_TypeDef* port, uint16_t pin, uint8_t* integrator) {}


