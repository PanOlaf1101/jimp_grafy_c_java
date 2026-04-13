SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -lm -Werror -Wextra -O2 -std=c11

graf: $(OBJ)
	$(CC) $(CFLAGS) -o graf $^

src/%.o: src/%.c
	$(CC) $(CLAGS) -o $@ -c $<

clean:
	rm src/*.o
