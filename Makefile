cc = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = chat-sim
SRC = chat-sim.c

$TARGET: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean

clean:
	rm -f $(TARGET)
