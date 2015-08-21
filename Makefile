IDIR = headers
SDIR = src
ODIR = obj
BDIR = bin

CC     = arm-linux-gnueabihf-g++
CFLAGS = -Wall -std=c++11 -I$(IDIR)/ -I/usr/local/include/
LIBS   = -L/usr/local/lib -lbcm2835

# Default action

all: hola_mundo load_rpi


# LOAD TO Raspbian

load_rpi: load_rpi_hola_mundo


# hola_mundo actions

#load_rpi_hola_mundo: hola_mundo
load_rpi_hola_mundo:
	scp $(BDIR)/hola_mundo root@192.168.0.14:/root/tests/

hola_mundo: $(ODIR)/hola_mundo.o
	$(CC) -o $(BDIR)/hola_mundo $(ODIR)/hola_mundo.o

# Objetive files compilation

$(ODIR)/%.o:  $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


# CLEANING

clean: clean_obj clean_bin

clean_obj:
	rm -f $(ODIR)/*.o

clean_bin:
	rm -f $(BDIR)/*
