CC=cc
CCFLAGS=-Wall -Wextra
net.o:net.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
olcd.o:olcd.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
main:main.c olcd.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@

