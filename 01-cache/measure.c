#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>


static __inline__ unsigned long long rdtsc(void) {
	unsigned long long int x;
	__asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
	return x;
}

int main(void) {
	int ret;
	int i;
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
	t1ms = (t2 - t1) / 1000;
	t1 = rdtsc();
	t2 = rdtsc();
	printf("delta t = %lld [ms]\n", (t2 - t1) / t1ms);
	
	ret = setpriority(which, pid, oldPriority);
	return 0;
}
