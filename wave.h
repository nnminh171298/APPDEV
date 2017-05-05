/* this hearder file contains wave header nformation as a struct
 * it also contains necessary constants, definitions and the function
 * prototypes used in this project */

typedef struct {
	char ChunkID[4];
	int ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	int Subchunk1Size;
	short int AudioFormat;
	short int NumChannels;
	int SampleRate;
	int ByteRate;
	short int BlockAlign;
	short int BitsPerSample;
	char Subchunk2ID[4];
	int Subchunk2Size;
}WAVHDR;

// #define DEBUG 1
#define SAMPLE_RATE 16000
#define PI 3.141592654

// function prototypes
void displayWAVHDR(WAVHDR hdr);				// display the header of the .wav file
void printID(char *);
void testTone(int freq, double duration);	// create a 1s test tone
void fillID(const char *, char []);
void displayWAVdata(short int []);			// display the data of the .wav file
