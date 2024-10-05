#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<stdlib.h>


int main(int argc, char *argv[]){

	int pipe1_fd[2], pipe2_fd[2], status; // pipe1_fd[0],pipe1_fd[1] and pipe2_fd[0],pipe2_fd[1]

	if(pipe(pipe1_fd) < 0){return EXIT_FAILURE;}
	if(pipe(pipe2_fd) < 0){ return EXIT_FAILURE;}

	int pid = fork();
	
	if(!pid){
		close(pipe1_fd[1]); close(pipe2_fd[0]);
		
		int childnum;
		
		read(pipe1_fd[0],&childnum,sizeof(int));
		
		printf("Recevice number: %d\n",childnum);

		childnum *= 10;
		
		write(pipe2_fd[1],&childnum,sizeof(int));
		
		close(pipe1_fd[0]);close(pipe2_fd[1]);
	
	} else{
		
		close(pipe1_fd[0]); close(pipe2_fd[1]);
		
		int number;
		
		printf("Enter a number: ");
		
		scanf("%d",&number);
		
		write(pipe1_fd[1],&number,sizeof(int));

		read(pipe2_fd[0],&number,sizeof(int));		
		
		printf("The final result: %d\n",number);

		close(pipe1_fd[1]); close(pipe2_fd[0]);
		
		waitpid(pid,&status,0);
	}

	return 0;
}