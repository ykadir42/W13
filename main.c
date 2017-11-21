#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int fds0[2];
	int fds1[2];

	pipe(fds0);
	pipe(fds1);

	int f = fork();

	if(f) {
		close(fds0[0]); //closes read end
		close(fds1[1]); //closes write end

		printf("[parent] sending: 2\n");
		int num = 2;
		write(fds0[1], &num, sizeof(int));

		int ans;

		read(fds1[0], &ans, sizeof(int));

		printf("[parent] received: %d\n", ans);

		return 0;
	}
	else{
		close(fds0[1]); //closes write end
		close(fds1[0]); //closes read end

		printf("[child] doing quick maths on: %d\n", 2);
		int ting;
		read(fds0[0], &ting, sizeof(int));
		ting = ting + ting - 1;
		write(fds1[1], &ting, sizeof(int));

		return 0;
	}
}
