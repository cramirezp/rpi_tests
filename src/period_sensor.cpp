#include <iostream>
#include <cstdint>
#include <bcm2835.h>

#include "rpi_gpio.h"
#include "rpi_gpio_sensor.h"

#define N 4

class Period_sensor: public Rpi_GPIO_sensor{
private:
	uint8_t last_pin_value;
	uint64_t last_time;
	uint64_t rising_edge_period;

protected:
public:
	Period_sensor():last_time((uint64_t)0), rising_edge_period((uint64_t)0), last_pin_value((uint8_t)0){}
	~Period_sensor(){}

	virtual void tick(){
		int lpv = last_pin_value;
		int cpv = bcm2835_gpio_lev(RPI_GPIO_P1_11);
		if(cpv - lpv > 0){
			uint64_t current_time = bcm2835_st_read();
			rising_edge_period = current_time - last_time;
			last_time = current_time;
		}
		last_pin_value = bcm2835_gpio_lev(RPI_GPIO_P1_11);
	}
  
	float measurement(){ return (float) rising_edge_period/1000000; } // Primera aprox. [us]k
};

int main(int argc, char *argv[]){
	Period_sensor period_sensor;

	Rpi_GPIO gpio;
	gpio.add_sensor("period_sensor", &period_sensor, 11);

	for(;;){
		gpio.tick();

		std::cout << "Valor: " << period_sensor.measurement() << std::endl;
	}

	return 0;
}