// this program will open a wave file, and display WAV header info
#include "wave.h"	// double quotation marks are used for user defined header
#include "screen.h"
#include <stdio.h>
#include <math.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>	// eliminate warning when s99 std is used

int main(int argc, char *argv[]){
	FILE *fp;
	WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
	int answer, ret;

/*	if (argc != 2){
		printf("Usuage: %s wave_file\n", argv[0]);
		return -1;
	}
	fp = fopen(argv[1], "r");	// try to open the wav file
	if(fp==NULL){
		printf("Cannot find file %s\n", argv[1]);
		return -1;
	}*/

	for(;;){
		ret = system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
		clearScreen();
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT)) break;
		fp = fopen("data.wav", "r");
		fread(&myhdr, sizeof(myhdr), 1, fp);
		displayWAVHDR(myhdr);
		fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
		displayWAVdata(sa);
		fclose(fp);
	}
	printf("Do you want to generate a test tone? (1: Yes, 0: No)\n");
	scanf("%d", &answer);
	if(answer == 1) testTone(1000, 5);
}
