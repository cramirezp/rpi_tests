#include <iostream>

#include "rpi_gpio.h"
#include "rpi_gpio_sensor.h"
	
class PWM_HS422: public Rpi_GPIO_sensor{
private:
	uint8_t duty_cycle;
protected:
public:
	PWM_HS422():duty_cycle(0){
		bcm2835_gpio_fsel(12, BCM2835_GPIO_FSEL_ALT5);
		bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_64);
	    bcm2835_pwm_set_mode(0, 1, 1);
	    bcm2835_pwm_set_range(0, 1024);
	}
	~PWM_HS422(){}

	virtual void tick(){
		bcm2835_pwm_set_data(0, duty_cycle);
	}

	int measurement(){ return duty_cycle; }
	void update(uint8_t dc) { duty_cycle = dc; }
};

int main(int argc, char *argv[]){
	Rpi_GPIO gpio;
	PWM_HS422 pwm;
	
	gpio.add_sensor("PWM_HS422", &pwm, 12);

	for(int i=0; i<255; i=(i>=254)? 0: i+1){
		gpio.tick();

		std::cout << "Valor: " << pwm.measurement() << std::endl;

		pwm.update(i);
	}

	return 0;
}