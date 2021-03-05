CC = gcc
PROGRAMS = pling
CFLAGS = -g -O2 -std=gnu11 -static -lm


.PHONY : all
all: $(PROGRAMS)

.PHONY : clean
clean:
	@rm -f $(PROGRAMS)

p:
	$(CC) $(CFLAGS) -o pling pling.c
debug:
	$(CC) $(CFLAGS) -o pling pling.c && valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./pling < plingtest2.txt
