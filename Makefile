all:
	gcc -o richard -Wall main.c list.c

clean:
	rm ./richard
