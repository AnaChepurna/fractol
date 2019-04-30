#include <unistd.h>
# include <sys/wait.h>

int main(){
	pid_t p = vfork();

	if (p == 0)
	{
		while(42) {}
	}
wait(&p);
}