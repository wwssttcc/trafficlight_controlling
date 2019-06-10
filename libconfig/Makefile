#####################################################################  
## file        :                                                   ##  
## author      : sh                                                ##  
## date-time   : 03/30/2018                                        ##  
#####################################################################  

#CC      =  arm-poky-linux-gnueabi-gcc
#CPP     = arm-poky-linux-gnueabi-g++
RM      = rm -rf  

## debug flag  
DBG_ENABLE   = 1  

## source file path  
SRC_PATH   := src 

## target exec file name  
TARGET     := liblibconfig.so  

## get all source files  
#SRCS         += $(wildcard $(SRC_PATH)/*.c)  

SRCS   = $(foreach dir, $(SRC_PATH), $(wildcard $(dir)/*.c)) 
#SRCS += $(wildcard src/*.c)

## all .o based on all .c  
OBJS        := $(SRCS:.c=.o)  


## need libs, add at here  
#LIBS := pthread  

## used headers  file path  
INCLUDE_PATH := include  

## used include librarys file path  
#LIBRARY_PATH := /lib  

## debug for debug info, when use gdb to debug  
ifeq (1, ${DBG_ENABLE})   
CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1  
endif  

## get all include path  
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))  

## get all library path  
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))  

## get all librarys  
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))  

CFLAGS += -shared -fPIC


all: clean build  
#all:
#	@echo $(OBJS)
#	@echo $(SRCS)
build: $(OBJS)  
	$(CC) -c $(CFLAGS) $(SRCS)  
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)  
	$(RM) $(OBJS)
	$(RM) *.o

clean:  
	$(RM) $(OBJS) $(TARGET)  
