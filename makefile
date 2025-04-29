CC=cc
CCFLAGS=-Wall -Wextra
queue.o:queue.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
test:test.c queue.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@	
net.o:net.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
olcd.o:olcd.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
olc:olc.c net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@	
main:main.c olcd.o net.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@

