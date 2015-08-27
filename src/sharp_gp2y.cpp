#include <iostream>

#include "rpi_gpio.h"
#include "rpi_gpio_sensor.h"
	
class sharp_gp2y: public Rpi_GPIO_sensor{
private:
	uint8_t pin;
protected:
public:
	sharp_gp2y():pin(0){}
	~sharp_gp2y(){}

	virtual void tick(){
		pin = bcm2835_gpio_lev(RPI_GPIO_P1_11);
	}

	float measurement(){ return ((float)pin)*1.3 + 0.2; }
};

int main(int argc, char *argv[]){
	sharp_gp2y distance;

	Rpi_GPIO gpio;
	gpio.add_sensor("sharp_gp2y", &distance, 11);

	for(;;){
		gpio.tick();

		std::cout << "Valor: " << distance.measurement() << std::endl;
	}

	return 0;
}