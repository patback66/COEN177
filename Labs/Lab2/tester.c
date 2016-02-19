#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
	int pid;
	int i = 0;
	int j = 0;
	/*fork a bunch of times*/
	while(i < 6) {
		pid = fork();
		printf("PID: %d\n", pid);
		j = 0;
		/* arbitrary loop for padding*/
		while(j<10000) {
			j++;
		}
		i++;
	}
	return 0;
} 

/* Expected behavior:
	standard: print PIDs in order
	random: random distribution of PID prints
*/
