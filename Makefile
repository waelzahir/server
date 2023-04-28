server:
	@gcc	cp_dae.c -o server
client:
	@gcc cp_client.c -o client

clean:
	@rm -rf server client

test: clean server client
	@./server &
