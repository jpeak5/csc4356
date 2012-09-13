p1 : main.o
	gcc -o p1 main.o

main.o : main.c
	gcc -c main.c

clean :
	rm main.o p1
