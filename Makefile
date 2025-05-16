cc = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = chat-sim
SRC = main.c chat.c commands.c persistence.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o $(TARGET)
