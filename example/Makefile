TARGET  = lidar
LIBS    =
CC      = gcc
CFLAGS  = -Wall -pedantic -Wfatal-errors -O2
LDFLAGS = -lm

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = main.o ../src/serial.o ../src/lidar.o
HEADERS = ../src/serial.h ../src/lidar.h

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
