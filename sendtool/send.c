#include <stdio.h>

int main(){
	int i=0;
	printf("start up\n");
	while(i<5){
		sleep(3);
		printf("waiting...\n");
		i++;
	}
	return 0;
}
