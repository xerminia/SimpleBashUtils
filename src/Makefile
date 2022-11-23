CC = gcc
CFLAGS = -Wall -Werror -Wextra
PATHCAT = cat/
PATHGREP = grep/

all: clean s21_cat s21_grep test

s21_cat.o:
	$(CC) $(CFLAGS) -c $(PATHCAT)s21_cat.c -o $(PATHCAT)s21_cat.o

s21_grep.o:
	$(CC) $(CFLAGS) -c $(PATHGREP)s21_grep.c -o $(PATHGREP)s21_grep.o

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) $(PATHCAT)s21_cat.o -o $(PATHCAT)s21_cat

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) $(PATHGREP)s21_grep.o -o $(PATHGREP)s21_grep

test: s21_test.o
	sh test.sh
	$(CC) $(CFLAGS) s21_test.o -o test -lcheck
	./test

s21_test.o:
	$(CC) $(CFLAGS) -c test.c -o s21_test.o

clean:
	rm -rf cat/*.o grep/*.o cat/s21_cat grep/s21_grep *.o cat_log.txt s21_cat_log.txt test
	rm -rf grep_log.txt s21_grep_log.txt

check:
	cppcheck --enable=all --suppress=missingIncludeSystem cat/*.c *.c grep/*.c cat/*.h grep/*.h
