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
	int i, pid, size, ret, addr;
	void *buffer;
	//void *target;

	/* it's ok size is not PAGESIZE */
	size = 1280;
	ret = 0;
	addr = 0;

	/* extra test for testing the correctness of the read result */
	//target = (void *)malloc(size);
	//memset(target, 2, size);	

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
	while ((ret = dump(pid, (void *)addr, buffer, size)) != -1) {
		for (i = 0; i < ret; i++) {
			if (i % 16 == 0)
				printf(1, "\n0x%x:", (uint)addr + i);
			if (i % 4 == 0)
				printf(1, "\t0x");
			if ((uint)*((char *)buffer + i) < 16)
				printf(1, "0");
			printf(1, "%x", (uint)*((char *)buffer + i) % 0x100);
		}		
		addr += size;
		if (ret < size)
			break;
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

