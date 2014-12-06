ROOTHOME = /home/zhenyuhan/work/codes/root
ROOTLIB  = $(ROOTHOME)/lib
ROOTINC  = $(ROOTHOME)/include

CFLAGS   = -I $(ROOTINC) -I ../WIMPMASS -L $(ROOTLIB)  -lMatrix -l Core -lgslcblas -lMathCore -ldl

OBJDIR = ../src
CC     = g++

all:	obj example22 example33
obj:	
	cd ../src;make
example22: example22.cpp  
	$(CC) -I ../WIMPMASS  -o example22 example22.cpp $(OBJDIR)/topology22.o 

example33: example33.cpp 
	$(CC) $(CFLAGS)  -o example33 example33.cpp  $(OBJDIR)/topology33.o
clean:
	rm -f *.o *~ example22 example33
