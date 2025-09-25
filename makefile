# =============================
# Makefile para projeto de sorting
# =============================

CC = gcc
CFLAGS = -Wall -O2
TARGET = main
SRCS = main.c codigo/algoritmos.c codigo/monitor_memoria.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean