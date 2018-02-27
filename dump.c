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
	void *buffer, *target;

	size = 128;
	target = (void *)malloc(size);
	memset(target, 2, size);
	//printf(1, "target[0] = %x\n", (uint)(*(char *)target));	

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
	// +3 for test non-page aligned data
	if (dump(pid, target + 3, buffer, size - 3) != 0)
		printf(1, "error! dump return non 0\n");
	
	for (i = 0; i < size - 3; i++) {
		if (i % 16 == 0)
			printf(1, "\n0x%x:", (uint)target + i);
		if (i % 4 == 0)
			printf(1, "\t0x");
		if ((uint)*((char *)buffer + i) < 16)
			printf(1, "0");
		printf(1, "%x", (uint)*((char *)buffer + i) % 0x100);
	}
	printf(1, "\n");

	return 0;
}

int main(int argc, char *argv[])
{
	//printf(1, "in dump.c main\n");
	_dump();
	exit();
}

