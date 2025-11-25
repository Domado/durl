CC = gcc
OPENSSL_PATH = /opt/homebrew/opt/openssl@3

CFLAGS = -Iinclude -Ilib -I$(OPENSSL_PATH)/include -Wall -Wextra -std=c11
LDFLAGS = -L$(OPENSSL_PATH)/lib -lssl -lcrypto

SRCS = main.c $(wildcard lib/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = durl

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET) lib/*.o



