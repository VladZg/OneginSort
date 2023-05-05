TARGET = main

CC = g++
CFLAGS = #-g -fsanitize=address

SRC_DIR = ./Source/
APP_DIR = ./App/

SRC = 	$(APP_DIR)Onegin.cpp		\
	  	$(SRC_DIR)functions.cpp		\

all: compile

compile:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
