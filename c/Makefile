SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -O2 -std=c11

a.out: $(OBJ)
	$(CC) $(CFLAGS) $^

src/%.o: src/%.c
	$(CC) $(CLAGS) -o $@ -c $<

clean:
	rm src/*.o
