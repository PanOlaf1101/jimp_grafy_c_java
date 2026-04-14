SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -O2 -D_USE_MATH_DEFINES=1 -std=c11

graf: $(OBJ)
	$(CC) $(CFLAGS) -o graf $^ -lm

src/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm src/*.o
