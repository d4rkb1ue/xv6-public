#include "types.h"
#include "stat.h"
#include "user.h"

struct balance {
	char name[32];
	int amount;
};

volatile int total_balance = 0;

int pubint = 0;

volatile unsigned int delay (unsigned int d) {
	unsigned int i; 
	for (i = 0; i < d; i++) {
		__asm volatile( "nop" ::: );
	}

	return i;   
}
void inc(void *arg) {
	printf(1, "in func inc(), arg: %d\n", (uint)arg);
	pubint++;
	thread_exit();
}
void do_work(void *arg){
	int i; 
	int old;

	struct balance *b = (struct balance*) arg; 
	printf(1, "Starting do_work: s:%s\n", b->name);

	for (i = 0; i < b->amount; i++) {
		// thread_spin_lock(&lock);
		old = total_balance;
		delay(100000);
		total_balance = old + 1;
		//thread_spin_unlock(&lock);
	}

	printf(1, "Done s:%s\n", b->name);

	thread_exit();
	return;
}

int main(int argc, char *argv[]) {

	struct balance b1 = {"b1", 3200};
	struct balance b2 = {"b2", 2800};

	void *s1, *s2;
	int t1, t2, r1, r2;

	s1 = malloc(4096);
	s2 = malloc(4096);

	t1 = thread_create(do_work, (void*)&b1, s1);
	//printf(1, "passing b1 = %d\n", (uint)&b1);
	//t1 = thread_create(inc, (void*)&b1, s1);
	t2 = thread_create(do_work, (void*)&b2, s2); 
	//printf(1, "passing b2 = %d\n", (uint)&b2);
	//t2 = thread_create(inc, (void*)&b2, s2);
	
	r1 = thread_join();
	r2 = thread_join();


	printf(1, "Threads finished: (%d):%d, (%d):%d, shared balance:%d\n", 
			t1, r1, t2, r2, total_balance);
	
	//printf(1, "Thread v1 finished, (%d):%d, (%d):%d, pubint: %d\n", t1, r1, t2, r2, pubint);
	exit();
}
