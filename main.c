// this program will open a wave file, and display WAV header info
#include "wave.h"	// double quotation marks are used for user defined header
#include "screen.h"
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>	// eliminate warning when s99 std is used

int main(int argc, char *argv[]){
	FILE *fp;
	WAVHDR myhdr;
	short int sa[SAMPLE_RATE];
	int answer, ret;

	for(;;){
		ret = system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
		clearScreen();			// define in screen.c
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT || WTERMSIG(ret)==SIGQUIT)) break;
		fp = fopen("data.wav", "r");
		fread(&myhdr, sizeof(myhdr), 1, fp);
		displayWAVHDR(myhdr);	// define in wave.c
		fread(&sa, sizeof(short int), SAMPLE_RATE, fp);
		displayWAVdata(sa);		// define in wave.c
		fclose(fp);
	}
}
