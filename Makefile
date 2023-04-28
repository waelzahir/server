server:
	@gcc	cp_dae.c -o server
client:
	@gcc cp_client.c -o client

clean:
	@rm -rf server client
	@rm -rf output

test: clean server client
	@./server
	@chmod 666 output
	@cat output
	@rm -rf output
