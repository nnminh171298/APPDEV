// this program will open a wave file, and display WAV header info
#include "wave.h"	// double quotation marks are used for user defined header
#include "screen.h"
#include <stdio.h>
#include <math.h>

void displayWAVHDR(WAVHDR hdr){
	double duration;
	duration = (double)hdr.Subchunk2Size/hdr.ByteRate;
#ifdef DEBUG
	printf("Duration of audio: %.3f sec\n", duration);
	printf("Chunk ID: "); printID(hdr.ChunkID);
	printf("Chunk Size: %d\n", hdr.ChunkSize);
	printf("Format: "); printID(hdr.Format);
	printf("Subchunk1 ID: "); printID(hdr.Subchunk1ID);
	printf("Subchunk1 Size: %d\n", hdr.Subchunk1Size);
	printf("Audio Format: %d\n", hdr.AudioFormat);
	printf("Num of Channels: %d\n", hdr.NumChannels);
	printf("Sample Rate: %d\n", hdr.SampleRate);
	printf("Byte Rate: %d\n", hdr.ByteRate);
	printf("Block Align: %d\n", hdr.BlockAlign);
	printf("Bits per Sample: %d\n", hdr.BitsPerSample);
	printf("Subchunk2 ID: "); printID(hdr.Subchunk2ID);
	printf("Subchunk2 Size: %d\n", hdr.Subchunk2Size);
#else
	gotoXY(1,1);	setFGcolor(RED);	printf("%.2f sec", duration);
	gotoXY(1,10);	setFGcolor(CYAN);	printf("%d bit/s", hdr.BitsPerSample);
	gotoXY(1,20);	setFGcolor(YELLOW);	printf("%d sps", hdr.SampleRate);
	resetColors();
#endif
}

void testTone(int freq, double d){
	FILE *fp;
	int i;
	short int sample;
	WAVHDR h;
	fp = fopen("testTone.wav", "w");
	fillID("RIFF", h.ChunkID);
	fillID("WAVE", h.Format);
	fillID("fmt ", h.Subchunk1ID);
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.NumChannels = 2;
	h.SampleRate = SAMPLE_RATE;
	h.BitsPerSample = 16;
	h.ByteRate = h.SampleRate * h.NumChannels * (h.BitsPerSample/8);
	h.BlockAlign = h.NumChannels * (h.BitsPerSample/8);
	fillID("data", h.Subchunk2ID);
	h.Subchunk2Size = (int)(h.ByteRate * d);
	h.ChunkSize = h.Subchunk2Size + 36;
	fwrite(&h, sizeof(h), 1, fp);
	for(i=0; i<d*SAMPLE_RATE; i++){
		sample = 32768*sin(2*PI*freq*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
		sample = 32768*sin(2*PI*freq/2*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp);
}

void fillID(const char *s, char d[]){
	int i;
	for(i=0; i<4; i++) d[i] = *s++;
}

void printID(char id[]){
	int i;
	for(i=0; i<4; i++) putchar(id[i]);
	printf("\n");
}

void displayWAVdata(short int d[]){
	int i, j;
	double sum200, rms200;
	for(i=0; i<80; i++){
		sum200 = 0.0;
		for(j=0; j<SAMPLE_RATE/80; j++){
			sum200 += (*d)*(*d);
			d++;
		}
		rms200 = sqrt(sum200/(SAMPLE_RATE/80));
#ifdef DEBUG		//conditional compiling
		printf("%d.%10.2f ", i, rms200);
#else
		displayBar(rms200, i+1);
#endif
	}
}
