all:
	gcc -o richard -Wall ./src/main.c ./src/list.c

clean:
	rm ./richard
