##########################################################################
# BUILDING CONFIGURATION

IDIR = ./headers
SDIR = ./src
ODIR = ./obj
BDIR = ./bin
LDIR = ./lib


CC     = arm-linux-gnueabihf-g++
CFLAGS = -Wall -std=c++11 -I$(IDIR)/ -I/usr/local/include
LFLAGS = -L/usr/local/lib
LIBS   = -lbcm2835
AR     = arm-linux-gnueabihf-ar
AFLAGS = rvs

IP    = 192.168.0.14
DUSER = root
DDEST = /root/tests

##########################################################################
# Default current action

all: librpi_gpio.a pwm_hs422 load_rpi_pwm_hs422

load_rpi: load_rpi_simple_reading


##########################################################################
# Object files compilation

$(ODIR)/%.o:  $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


##########################################################################
# Program's specific compilation and loading

# hola_mundo actions ############################

#load_rpi_hola_mundo: hola_mundo
load_rpi_hola_mundo:
	scp $(BDIR)/hola_mundo $(DUSER)@$(IP):$(DDEST)

hola_mundo: $(ODIR)/hola_mundo.o
	$(CC) -o $(BDIR)/$@ $^

# GPIO simple reading ###########################

load_rpi_simple_reading:
	scp $(BDIR)/simple_reading $(DUSER)@$(IP):$(DDEST)

simple_reading: $(ODIR)/simple_reading.o
	$(CC) $(LFLAGS) -o $(BDIR)/$@ $^ $(LIBS)

# Rpi_GPIO class static library #################

load_rpi_rpi_gpio_lib:
	scp $(LDIR)/librpi_gpio.a $(DUSER)@$(IP):$(DDEST)

librpi_gpio.a: $(ODIR)/rpi_gpio.o $(ODIR)/rpi_gpio_sensor.o
	$(AR) $(AFLAGS) $(LDIR)/$@ $^

# Sharp_GP2Y tests ##############################

load_rpi_sharp_gp2y:
	scp $(BDIR)/sharp_gp2y $(DUSER)@$(IP):$(DDEST)

sharp_gp2y: $(ODIR)/sharp_gp2y.o
	$(CC) $(LFLAGS) -o $(BDIR)/$@ $^ $(LIBS) -L$(LDIR) -lrpi_gpio

# Period Reader #################################

load_rpi_period_sensor:
	scp $(BDIR)/period_sensor $(DUSER)@$(IP):$(DDEST)

period_sensor: $(ODIR)/period_sensor.o
	$(CC) $(LFLAGS) -o $(BDIR)/$@ $^ $(LIBS) -L$(LDIR) -lrpi_gpio

# Basic PWM #####################################

load_rpi_pwm_hs422:
	scp $(BDIR)/pwm_hs422 $(DUSER)@$(IP):$(DDEST)

pwm_hs422: $(ODIR)/pwm_hs422.o
	$(CC) $(LFLAGS) -o $(BDIR)/$@ $^ $(LIBS) -L$(LDIR) -lrpi_gpio

##########################################################################
# CLEANING

clean: clean_obj clean_bin clean_lib

clean_obj:
	rm -f $(ODIR)/*.o

clean_bin:
	rm -f $(BDIR)/*

clean_lib:
	rm -f $(LDIR)/*
