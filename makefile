CC=cc
CCFLAGS=-Wall -Wextra
olcd.o:olcd.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
main:main.c olcd.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@

