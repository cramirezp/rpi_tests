#include <iostream>

#include "rpi_gpio.h"
#include "rpi_gpio_sensor.h"

class sharp_gp2y: public Rpi_GPIO_sensor{
private:
	float meters;
protected:
public:
	sharp_gp2y():meters(.0){}
	~sharp_gp2y(){}

	virtual void tick(){
		//Rpi_GPIO_sensor::tick();
		uint8_t pin11 = bcm2835_gpio_lev(RPI_GPIO_P1_11);

		meters = pin11*1.3 + 0.2;
	}

	float measurement(){ return meters;}
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