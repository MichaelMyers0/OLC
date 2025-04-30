CC=cc
CCFLAGS=-Wall -Wextra
queue.o:queue.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
net.o:net.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@	
olcr.o:olcr.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
olcd.o:olcd.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
olc_mod.o:olc_mod.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@	
olc:olc.c net.o olc_mod.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@	
olc2:olc2.c net.o olc_mod.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@	
main:main.c olcd.o net.o queue.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@

