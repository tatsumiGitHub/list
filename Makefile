PROGRAM	= main
OBJS	= main.o list.o

SRCS	= $(OBJS:%.o=%.cpp)
CC		= clang
CCFLAGS	= -Wall -O2
LFLAGS	=

$(PROGRAM):	$(OBJS)
		$(CC) $(CCFLAGS) $(LFLAGS) -g -o $(PROGRAM) $^

.c.o:
		$(CC) $(CCFLAGS) -c $<

test:		$(PROGRAM)
		./main

gdb:		$(PROGRAM)
		gdb main

clean:;		rm -rf *.o *~ main

zip:;
		zip -r -o ./list.zip \
			  ./*.c \
			  ./*.h \
			  ./Makefile