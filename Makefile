EXEC = crc
CC = gcc

CFLAGS = -D CRC_32
CFLAGS += -g -Wall -std=gnu99 -I./inc/

SRC_DIR += ./src

SRCS += $(wildcard $(SRC_DIR)/*.c)

OBJS += main.o
OBJS += $(patsubst %.c, %.o, $(SRCS))

$(EXEC):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) 
clean:
	rm -rf $(EXEC) $(OBJS)
