TARGET = target
####################################
CC = g++ 
OBJS = $(TARGET).o
######### FASTJET ##################
FASTJETLIB  = -L${FASTJET}/lib -lfastjet
#-------- INCLUDE -----------------#
INCLUDE=./include
INCLUDES += -I${FASTJET}/include/ 
#########  FLAGS, LIBS  ############
CXXFLAGS += -m32 ${INCLUDES}
CXXLIBS =${FASTJETLIB}
#########################################################

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(CXXLIBS) -o $@

.cc.o:
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $<

$(OBJS):

clean:
	rm -f $(TARGET) $(OBJS)
