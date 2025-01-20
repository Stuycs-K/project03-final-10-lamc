.PHONY: clean server client
compile:
	@gcc -o server server.c
	@gcc -o client client.c
clean:
	@rm -f server
	@rm -f client
	@rm -f money.txt
	@rm -f usernames.txt
server:
	@./server
client:
	@./client
