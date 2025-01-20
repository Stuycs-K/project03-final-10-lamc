compile:
	gcc -o server server.c
	gcc -o client client.c
clean:
	@rm server
	@rm client
	@rm money.txt
	@rm usernames.txt
server:
	@./server
client:
	@./client
