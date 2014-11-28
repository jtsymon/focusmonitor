#!/usr/bin/env make -f

CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lX11
SOURCES=focusmonitor.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=focusmonitor

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
