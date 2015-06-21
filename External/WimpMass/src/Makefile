ROOTHOME = /home/zhenyuhan/work/codes/root
ROOTLIB  = $(ROOTHOME)/lib
ROOTINC  = $(ROOTHOME)/include

CFLAGS   = -I $(ROOTINC) -I ../WIMPMASS
CC = gcc
all:	topology22 topology33

topology22: topology22.cpp ../WIMPMASS/WIMPMASS.h
	$(CC) -I ../WIMPMASS  -c -o topology22.o topology22.cpp

topology33: topology33.cpp ../WIMPMASS/WIMPMASS.h	
	$(CC) $(CFLAGS) -c -o topology33.o topology33.cpp

clean:
	rm -f *.o *~ 

