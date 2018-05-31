PROG = exec
CC = g++
CPPFLAGS = -O0 -g -W -Wall -pedantic -std=c++11
OBJS = main.o processos.o

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

main.o:
	$(CC) $(CPPFLAGS) -c main.cpp
processos.o:
	$(CC) $(CPPFLAGS) -c processos.cpp
clean: 
	del /f *.o exec