all:
	gcc -c launch.c -Wall -Wextra
	gcc -o launch launch.o -lm
	gcc -c tube.c -Wall -Wextra
	gcc -o tube tube.o -lm

launch:
	gcc -c launch.c -Wall -Wextra
	gcc -o launch launch.o -lm

tube:
	gcc -c tube.c -Wall -Wextra
	gcc -o tube tube.o -lm

clean:
	rm launch launch.o
	rm tube tube.o
