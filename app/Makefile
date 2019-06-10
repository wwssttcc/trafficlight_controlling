TARGET=tl_running.out
APP_DIR = $(CURDIR)
APP_BIN = $(APP_DIR)/tl_running.out

MK2_IP_ADDR :=192.168.1.1
MK2_APP_DIR :=/home/root

	
INC = -I/home/bzm/Project/protobuf/protobuf-c/build/protobuf-c-arm/include \
			-I/home/bzm/Project/app/trafficlight_controlling/app/include
LIBS = -L$(CURDIR)/lib/ -llibconfig -lprotobuf-c -lzmq

OBJ = main.o \
	  tl_controlling.o \
	  tl_tcpserver.o	\
	  tl_message.pb-c.o

CFLAGS +=  -fPIC

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS) -lpthread $(CFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ $(INC) -o $@

proto:
	protoc-c --c_out=. ./tl_message.proto

install:$(APP_BIN)
	sudo rm ~/.ssh -rf
	sshpass -p root scp -o "StrictHostKeyChecking no" $(APP_BIN) $(MK2_IP_ADDR):$(MK2_APP_DIR)
	#sshpass -p root scp -o "StrictHostKeyChecking no" $(APP_CONFIG) $(MK2_IP_ADDR):$(MK2_CONFIG_DIR)

clean:
	rm -rf $(TARGET) $(OBJ)
	