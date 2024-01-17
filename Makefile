PROGRAM	= main
OBJS	= main.o list.o
OBJLIB	= list.o
LIBRARY	= libmylist.so

SRCS	= $(OBJS:%.o=%.cpp)
CC		= gcc
LN	= ln
CCFLAGS	= -Wall -O2 -fPIC
LFLAGS	= -L. -llist -Wl,-rpath,.

$(PROGRAM):	$(OBJS)
		$(CC) $(CCFLAGS) -g -o $(PROGRAM) $^

.c.o:
		$(CC) $(CCFLAGS) -c $<

test:	$(PROGRAM)
		./main

libmylist.so:	$(OBJS)
		$(CC) -shared -Wl,-soname,$(LIBRARY).1 -o $(LIBRARY).1.0.0 $(OBJS1)
		$(LN) -s $(LIBRARY).1.0.0 $(LIBRARY)
		$(LN) -s $(LIBRARY).1.0.0 $(LIBRARY).1

lib:	$(LIBRARY)

docs:; doxygen

gdb:		$(PROGRAM)
		gdb main

clean:;		rm -rf *.o *~ main lib* *.bak html/

zip:;
		zip -r -o ./list.zip \
			  ./*.c \
			  ./*.h \
			  ./Makefile