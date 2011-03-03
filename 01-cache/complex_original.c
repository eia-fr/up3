#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>

struct TEST {
	int a;
	char b;
	int c;
	char d;
} test[1000];

static __inline__ unsigned long long rdtsc(void) {
	unsigned long long int x;
	struct timeval tp;
	
	gettimeofday(&tp, NULL);
	
	x = tp.tv_sec * 1000 * 1000 + tp.tv_usec;
	
	return x;
}

void testit() {
	int i;

	for (i = 0; i < 1000; i++) {
		test[i].a = 1;
		test[i].b = 2;
		test[i].c = 3;
		test[i].d = 4;
	}
}

int main(int argc, char * argv[]) {
	int repetitions = atoi(argv[1]);
	
	int j;
	int i;
	int k;
	
	int ret;
	long long t1, t2, t1ms;
	int which = PRIO_PROCESS;
	id_t pid;
	int oldPriority;
	int priority;
	
	pid = getpid();
	oldPriority = getpriority(which, pid);
	priority = -20;
	ret = setpriority(which, pid, priority);
	
	t1 = rdtsc();
	sleep(1);
	t2 = rdtsc();
	
	t1ms = (t2 - t1) / 1000L;
	
	t1 = rdtsc();
	for (k = 0; k < repetitions; k++) {
		testit();
	}
	t2 = rdtsc();
	
	printf("delta t = %lld [ms]\n", (t2 - t1) / t1ms);
	
	ret = setpriority(which, pid, oldPriority);
	return 0;
}