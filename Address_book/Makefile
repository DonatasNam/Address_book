exec:= list
BIN:= main.c linkedlist.c

.PHONY: all clean

all:$(exec)

$(exec):$(BIN)

	$(CC) -Wall -o $@ $^


clean:
	$(RM) $(exec)