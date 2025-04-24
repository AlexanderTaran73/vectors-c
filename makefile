run:
	gcc src/main.c -o bin/main
	./bin/main

clean:
	rm -f bin/main
