##########################################################################
# BUILDING CONFIGURATION

IDIR = headers
SDIR = src
ODIR = obj
BDIR = bin


CC     = arm-linux-gnueabihf-g++
CFLAGS = -Wall -std=c++11 -I$(IDIR)/ -I/usr/local/include
LFLAGS = -L/usr/local/lib
LIBS   = -lbcm2835


##########################################################################
# Default current action

all: simple_reading load_rpi

load_rpi: load_rpi_simple_reading


##########################################################################
# Objetive files compilation

$(ODIR)/%.o:  $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


##########################################################################
# Program's specific compilation and loading

# hola_mundo actions ############################

#load_rpi_hola_mundo: hola_mundo
load_rpi_hola_mundo:
	scp $(BDIR)/hola_mundo root@192.168.0.14:/root/tests/

hola_mundo: $(ODIR)/hola_mundo.o
	$(CC) -o $(BDIR)/$@ $^

# GPIO simple reading ###########################

load_rpi_simple_reading:
	scp $(BDIR)/simple_reading root@192.168.0.14:/root/tests/

simple_reading: $(ODIR)/simple_reading.o
	$(CC) $(LFLAGS) -o $(BDIR)/$@ $^ $(LIBS)

##########################################################################
# CLEANING

clean: clean_obj clean_bin

clean_obj:
	rm -f $(ODIR)/*.o

clean_bin:
	rm -f $(BDIR)/*
