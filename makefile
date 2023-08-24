CC = gcc

CFLAGS = -O2 -g -Wall

LINKS = -lpthread -lm -lsdrplay_api

# ADD project flag!!! 		PROJECT=rtty


%: %.c 
	@echo "Compiling" $<
	$(CC) $(CFLAGS) -c $<
	$(CC) -g -o $@ $@.o $(LINKS)