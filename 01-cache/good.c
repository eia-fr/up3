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
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int repetitions = atoi(argv[3]);
	
	int x[width][height];
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
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				x[i][j] = x[i][j] * 2;
			}
		}
	}
	t2 = rdtsc();
	
	printf(" - Good:   delta t = %lld [ms]\n", (t2 - t1) / t1ms);
	
	ret = setpriority(which, pid, oldPriority);
	return 0;
}