#include "wave.h"	// double quotation marks are used for user defined 
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]){
	FILE *fp;
	WAVHDR myhdr;
	int answer;
	if (argc != 2){
		printf("Usuage: %s wave_file\n", argv[0]);
		return -1;
	}
	fp = fopen(argv[1], "r");	// try to open the wav file
	if(fp==NULL){
		printf("Cannot find file %s\n", argv[1]);
		return -1;
	}
	fread(&myhdr, sizeof(myhdr), 1, fp); displayWAVHDR(myhdr);
	fclose(fp);
	printf("Do you want to generate a test tone? (1: Yes, 0: No)\n");
	scanf("%d", &answer);
	if(answer == 1) testTone(1000, 5);
}

void displayWAVHDR(WAVHDR hdr){
	double duration;
	duration = (double)hdr.Subchunk2Size/hdr.ByteRate;
	printf("Chunk ID: ");
	printID(hdr.ChunkID);
	printf("Chunk Size: %d\n", hdr.ChunkSize);
	printf("Format: "); printID(hdr.Format);
	printf("Subchunk1 ID: ");
	printID(hdr.Subchunk1ID);
	printf("Subchunk1 Size: %d\n", hdr.Subchunk1Size);
	printf("Audio Format: %d\n", hdr.AudioFormat);
	printf("Num of Channels: %d\n", hdr.NumChannels);
	printf("Sample Rate: %d\n", hdr.SampleRate);
	printf("Byte Rate: %d\n", hdr.ByteRate);
	printf("Block Align: %d\n", hdr.BlockAlign);
	printf("Bits per Sample: %d\n", hdr.BitsPerSample);
	printf("Subchunk2 ID: ");
	printID(hdr.Subchunk2ID);
	printf("Subchunk2 Size: %d\n", hdr.Subchunk2Size);
	printf("Duration of audio: %.3f sec\n", duration);
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
	h.ByteRate = h.SampleRate *	h.NumChannels * (h.BitsPerSample/8);
	h.BlockAlign = h.NumChannels * (h.BitsPerSample/8);
	fillID("data", h.Subchunk2ID);
	h.Subchunk2Size = (int)(h.ByteRate * d); h.ChunkSize = h.Subchunk2Size + 36;
	fwrite(&h, sizeof(h), 1, fp); for(i=0; i<d*SAMPLE_RATE; i++){
		sample = 32767*sin(2*PI*freq*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
		sample = 32767*sin(2*PI*freq/2*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp);
}
void fillID(const char *s, char d[]){
	int i; for(i=0; i<4; i++) d[i] = *s++;
}
void printID(char id[]){
	int i; for(i=0; i<4; i++) putchar(id[i]);
	printf("\n");
}
