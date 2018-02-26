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

	/* parent dumps memory of the child */
	dump(12, (void *)0x1, (void *)0x2, 78);
	return 0;
}

int main(int argc, char *argv[])
{
	printf(1, "in dump.c main\n");
	_dump();
	exit();
}

