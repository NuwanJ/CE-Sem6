#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#define DATA_PORT 0x378	/* parallel port base address */
#define STATUS_PORT DATA_PORT+1
#define CONTROL_PORT DATA_PORT​+2

unsigned char status,data;

void delay(int);

void main(){
	if(ioperm(DATA_PORT, 1, 1)){
	  fprintf(stderr, "Access denied to %x\n",DATA_PORT);
	  exit(1);	
	}
	if(ioperm(STATUS_PORT, 1, 1)){
	  fprintf(stderr, "Access denied to %x\n",STATUS_PORT);
	  exit(1);		
	}
	status = inb(STATUS_PORT);
	//test();

	int digits[10] = {0b00111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111100, 0b0000111, 0b1111111, 0b1100111};
	while(1){
		int i;
		for(i=0;i<10;i++){
			outb((i), DATA_PORT);
			printf("%d\n", i);
			delay(10000);
		}	
	}
}

void test(int val){
	int i;
	for(i=0;i<7;i++){
		outb(~(1<<i), DATA_PORT);
		delay(10000);
	}	
}
void delay(int n){
	int i,j;	
	for(i = 0; i < 32766; i++){
		for(j = 0; j < n; j++){
		}
	}
}
