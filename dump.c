#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096
int _dump()
{
	/* Fork a new process to play with */
	/* We don't have a good way to list all pids in the system
	 *      so forking a new process works for testing */ 
	int i, pid, size;
	void *buffer, *addr;

	size = 128;
	addr = 0;

	pid = fork();
	if (pid == 0) {
	      /* child spins and yields */
		while (1) {
			sleep(5);
		};
	}

	/* parent dumps memory of the child */
	buffer = (void *)malloc(size);
	memset(buffer, 0, size);
	dump(pid, addr, buffer, size);
	
	for (i = 0; i < size; i++) {
		if (i % 16 == 0)
			printf(1, "\n0x%x:", (uint)addr + i);
		if (i % 4 == 0)
			printf(1, "\t0x");
		if ((uint)*((char *)buffer + i) < 16)
			printf(1, "0");
		printf(1, "%x", (uint)*((char *)buffer + i));
	}
	printf(1, "\n");

//	for (i = 0; i < PGSIZE; i++)
//	{
//		if (*((char *)buffer + i) != (char)1)
//			printf(1, "buffer[%d] = %d\n", *((char *)buffer + i));
//	}
//	printf(1, "buffer[0] = 1 ? %c\n", *((char *)buffer) == (char)1 ? 'T' : 'F');
	return 0;
}

int main(int argc, char *argv[])
{
	printf(1, "in dump.c main\n");
	_dump();
	exit();
}

