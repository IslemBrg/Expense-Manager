CC = gcc
CFLAGS = -Wall -Wextra

all: financial_management

financial_management: main.c
	$(CC) $(CFLAGS) $< -o $@

reset:
	rm -f financial_management

clean:
	rm -f myincome.bin myexpense.bin Record.bin

run: financial_management
	./financial_management

.PHONY: all reset reset