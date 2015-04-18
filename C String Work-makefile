reverse: reverse.o lines.o chars.o mwords.o
	gcc -o reverse reverse.o lines.o chars.o mwords.o

reverse.o: reverse.c myFunctions.h
	gcc -c reverse.c


lines.o: lines.c
	gcc -c lines.c

chars.o: chars.c
	gcc -c chars.c

mwords.o: mwords.c
	gcc -c mwords.c

.PHONY: clean

clean: @rm -f *.o core reverse
