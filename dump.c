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
	// int pid = fork();

	//if (pid == 0) {
		/* child spins and yields */
	//	while (1) {
	//		sleep(5);
	//	};
	//}
	int i = 0;
	/* parent dumps memory of the child */
	void *buffer = (void *)malloc(PGSIZE);
	// void *buffer2 = (void *)malloc(PGSIZE);
	memset(buffer, 0, PGSIZE);
	// memset(buffer, 1, PGSIZE);
	dump(12, (void *)0x1, buffer, PGSIZE);
	for (i = 0; i < PGSIZE; i++)
	{
		if (*((char *)buffer + i) != (char)1)
			printf(1, "buffer[%d] = %d\n", *((char *)buffer + i));
	}
	printf(1, "buffer[0] = 1 ? %c\n", *((char *)buffer) == (char)1 ? 'T' : 'F');
	return 0;
}

int main(int argc, char *argv[])
{
	printf(1, "in dump.c main\n");
	_dump();
	exit();
}

