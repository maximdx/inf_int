CC=g++
CFLAGS=-c -Wall -ggdb3
DEBUG=-ggdb3

all : Test

Test : Test.o  inf_int.o inf_int_func.o
	$(CC) $(DEBUG) Test.o inf_int.o inf_int_func.o -o Test

inf_int_func.o : inf_int_func.cpp inf_int_func.h
	$(CC) $(CFLAGS) inf_int_func.cpp

inf_int.o : inf_int.cpp inf_int.h
	$(CC) $(CFLAGS) inf_int.cpp

Test.o : Test.cpp inf_int.h
	$(CC) $(CFLAGS) Test.cpp

clean :
	rm *.o Test
