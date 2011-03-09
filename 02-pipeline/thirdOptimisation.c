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
	
	int ret,j,sum,a,b,c,d,e,f,g,h;
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
	for (a=0,b=0,c=0,d=0,e=0,f=0,g=0,j = 0; j < arraySize; j+=29) {
		a+=buffer[j];
		b+=buffer[j+1];
		c+=buffer[j+2];
		d+=buffer[j+3];
		e+=buffer[j+4];
		f+=buffer[j+5];

		g+=buffer[j+6];
		a+=buffer[j+7];
		b+=buffer[j+8];
		c+=buffer[j+9];
		d+=buffer[j+10];
		e+=buffer[j+11];
		f+=buffer[j+12];
		g+=buffer[j+13];

		a+=buffer[j+14];
		b+=buffer[j+15];
		c+=buffer[j+16];
		d+=buffer[j+17];
		e+=buffer[j+18];
		f+=buffer[j+19];
		g+=buffer[j+21];

		a+=buffer[j+22];
		b+=buffer[j+23];
		c+=buffer[j+24];
		d+=buffer[j+25];
		e+=buffer[j+26];
		f+=buffer[j+27];
		g+=buffer[j+28];
	}
	
	sum = a+b+c+d+e+f+g;
	t2 = rdtsc();
	
	printf(" - thirdOptimisation:    delta t = %lld [ms]\n", (t2 - t1) / t1ms);
	
	ret = setpriority(which, pid, oldPriority);
	return 0;
}
