#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sched.h>


static __inline__ unsigned long long rdtsc(void) {
	unsigned long long int x;
	struct timeval tp;
	
	gettimeofday(&tp, NULL);
	
	x = tp.tv_sec * 1000 * 1000 + tp.tv_usec;
	
	return x;
}

int main(int argc, char * argv[]) {
	int arraySize = atoi(argv[1]);// The size of the buffer array
	
	int buffer[arraySize];
	
	int ret,j,sum,a,b,c,d;
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

	for (a=0,b=0,c=0,d=0,j = 0; j < arraySize; j+=4) {
		a+=buffer[j];
		b+=buffer[j+1];
		c+=buffer[j+2];
		d+=buffer[j+3];
	}
	sum = a+b+c+d;
	t2 = rdtsc();
	
	printf(" - firstOptimisation:    delta t = %lld [ms]\n", (t2 - t1) / t1ms);
	
	ret = setpriority(which, pid, oldPriority);
	return 0;
}
