all: app
app:
	gcc -Wall -Werror -c src/*.c
	gcc -Wall -Werror *.o -o app
	rm *.o
clean:
	rm app
run:
	./app