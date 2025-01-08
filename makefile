.PHONY: clean client server compile
compile: compile_client compile_server
compile_client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o
compile_server: forking_server.o pipe_networking.o
	gcc -o server forking_server.o pipe_networking.o
basic_client.o: basic_client.c gamble.h
	gcc -c basic_client.c
forking_server.o: forking_server.c gamble.h
	gcc -c forking_server.c
pipe_networking.o: pipe_networking.c gamble.h
	gcc -c pipe_networking.c
client:
	./client
server:
	./server
clean:
	rm *.o
	rm *~
