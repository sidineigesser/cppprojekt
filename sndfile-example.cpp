/*
	libsoundfile:
	g++ -o output input.cpp -lsndfile

 */

#include <iostream>

#include <sndfile.h>

using namespace std;

int main()
{

	SNDFILE *inFile, *outFile;
	SF_INFO sfInfo;
	double  **soundArray;			// 2-dimensionales Array (Array von Arrays)

	string filePath = "InputFile.wav";
	string outFilePath = "OutputFile.wav";


	inFile = sf_open(filePath.c_str(), SFM_READ, &sfInfo);

	if(inFile == NULL)		// or  "if(inFile == 0)" or "if(!inFile)"
		{
			cout << "Not able to open " << filePath << endl;
			sf_perror(NULL);
			return 0;
		}


	outFile = sf_open(outFilePath.c_str(), SFM_WRITE, &sfInfo);
	 
	double buffer[500];	// Puffer für Soundsamples, Größe ist variabel
	int    itemsRead;
	double amplitude = 0.5;
	
	while (itemsRead = sf_read_double(inFile, buffer, 500)) {
		
		for (int item = 0; item < itemsRead; item++) {
			buffer[item] *= amplitude;
		}
		
		sf_write_double(outFile, buffer, itemsRead);
	}
	
	sf_close(outFile);	
	sf_close(inFile);	

	return 0;
}
