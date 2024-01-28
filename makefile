CC = gcc
CFLAGS = -Wall -Wextra

all: financial_management

financial_management: main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f financial_management myincome.bin myexpense.bin Record.bin

run: financial_management
	./financial_management

.PHONY: all clean run