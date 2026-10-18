#Generate application
app1: app1.o part1.o
	gcc -o app1 app1.o part1.o

#generate part1.o
part1.o: part1.c part1.h
	gcc -c part1.c

#generate app1.o
app1.o: app1.c
	gcc -c app1.c

clean:
	rm *.o