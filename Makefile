TARGET = main

CC = g++
CFLAGS = #-g -fsanitize=address

SRC_DIR = ./Source/

SRC = 	$(SRC_DIR)Onegin.cpp		\
	  	$(SRC_DIR)functions.cpp		\

$(TARGET) :
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean :
	rm -f *.o $(TARGET)
