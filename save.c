#include "bmp_header.h"
void save(char filename[])
{
	// save
	// cream fisierul la adresa primita
	FILE* f2;
	f2 = fopen(filename, "wb");
	// verificam daca s-a deschis corect
	if (f2 == NULL)
	{
		printf("Can't create file");
	}
	// scriem fileMarker1
	//fwrite(&open_fileheader->fileMarker1, sizeof(unsigned char), 1, f2);

}