#include "bmp_header.h"
void edit(char filename[])
{
	// edit
	// deschidem fisierul de la adresa primita
	FILE* f1;
	f1 = fopen(filename, "rb");
	// verificam daca s-a deschis corect
	if (f1 == NULL)
	{
		printf("Can't open file");
	}

	// alocam dinamic o structura bmp_fileheader in care vom stoca headerul fisierului
	bmp_fileheader *open_fileheader= malloc(sizeof(bmp_fileheader));
	// alocam si citim fileMarker1
	open_fileheader->fileMarker1 = malloc(sizeof(unsigned char));
	fread(&open_fileheader->fileMarker1, sizeof(unsigned char), 1, f1);
	printf("fileMarker1 = %u\n", open_fileheader->fileMarker1);
	// alocam si citimi fileMarker2
	open_fileheader->fileMarker2 = malloc(sizeof(unsigned char));
	fread(&open_fileheader->fileMarker2, sizeof(unsigned char), 1, f1);
	printf("fileMarker2 = %u\n", open_fileheader->fileMarker2);
	// alocam si citimi bfSize
	open_fileheader->bfSize = malloc(sizeof(unsigned int));
	fread(&open_fileheader->bfSize, sizeof(unsigned int), 1, f1);
	printf("bfSize = %u\n", open_fileheader->bfSize);
	// verificam daca fisierul chiar este de tip .bmp
	if ((open_fileheader->fileMarker1 == 66) && (open_fileheader->fileMarker2 == 77))
	{
		printf ("Fisierul este .bmp\n");
	}
	// nu memoram unused1 sau unused2 si sarim peste bytii respectivi
	fseek(f1, 4, SEEK_CUR);
	// alocam si citim imageDataOffset
	open_fileheader->imageDataOffset = malloc(sizeof(unsigned int));
	fread(&open_fileheader->imageDataOffset, sizeof(unsigned int), 1, f1);
	printf("imageDataOffset = %u (bytes)\n", open_fileheader->imageDataOffset);

	// alocam dinamic o structura bmp_infoheader in care vom stoca infoheaderul fisierului
	bmp_infoheader* open_infoheader = malloc(sizeof(bmp_infoheader));
	
	// memoram biSize temporar (DE SCOS INAINTE DE FINALIZAT TEMA SI INLOCUIT CU CE E JOS)
	open_infoheader->biSize = malloc(sizeof(unsigned int));
	fread(&open_infoheader->biSize, sizeof(unsigned int), 1, f1);
	printf("biSize = %u\n", open_infoheader->biSize);

	// nu memoram biSize(=40), si sarim peste bytii respectivi
	//fseek(f1, 4, SEEK_CUR);
	
	// alocam si citim width
	open_infoheader->width = malloc(sizeof(unsigned int));
	fread(&open_infoheader->width, sizeof(unsigned int), 1, f1);
	printf("width = %u\n", open_infoheader->width);
	// alocam si citim height
	open_infoheader->height = malloc(sizeof(unsigned int));
	fread(&open_infoheader->height, sizeof(unsigned int), 1, f1);
	printf("height = %u\n", open_infoheader->height);
	// nu memoram planes (=1), bitPix (=24) sau bitCompression (=0) si sarim peste bytii respectivi
	fseek(f1, 8, SEEK_CUR);
	// alocam si biSizeImage
	open_infoheader->biSizeImage = malloc(sizeof(unsigned int));
	fread(&open_infoheader->biSizeImage, sizeof(unsigned int), 1, f1);
	printf("biSizeImage = %u\n", open_infoheader->biSizeImage);
	// nu memoram biXPelsPerMeter (=0) si sarim peste bytii respectivi
	fseek(f1, 4, SEEK_CUR);
	// nu memoram biYPelsPerMeter (=0) si sarim peste bytii respectivi
	fseek(f1, 4, SEEK_CUR);
	// nu memoram biClrUsed (=0) si sarim peste bytii respectivi
	fseek(f1, 4, SEEK_CUR);
	// nu memoram biClrImportant (=0) si sarim peste bytii respectivi
	fseek(f1, 4, SEEK_CUR);
	// indicele 0=rosu, 1=verde, 2=albastru
	// NU UITAT MATRICEA E PE DOS!!!!!!!!!!!!!!
	// PADDING
	// calculam padding
	int padding = (open_infoheader->width) * 3;
	if ((padding % 4) == 0)
	{
		padding = 0;
	}
	else
	{
		padding = ((padding / 4) + 1) * 4 - padding;
	}
	printf("Padding = %d bytes\n", padding);
	// alocam dinamic o matrice 3d matrice_rgb_pixeli[3][height][width]
	unsigned char*** matrice_rgb_pixeli = (unsigned char***)malloc(3 * sizeof(unsigned char**));
	for (int i = 0; i < 3; i++)
	{
		matrice_rgb_pixeli[i] = (unsigned char**)malloc(open_infoheader->height *sizeof(unsigned char*));
		for (int j = 0; j < open_infoheader->height; j++)
		{
			matrice_rgb_pixeli[i][j] = (unsigned char*)malloc(open_infoheader->width * sizeof(unsigned char));
		}
	}
	// ne mutam la inceputul pixel data-ului
	fseek(f1, open_fileheader->imageDataOffset, SEEK_SET);
	for (int i = 0; i < open_infoheader->height; i++)
	{
		for (int j = 0; j < open_infoheader->width; j++)
		{
			fread(&matrice_rgb_pixeli[2][open_infoheader->height-1-i][j], sizeof(unsigned char), 1, f1);
			fread(&matrice_rgb_pixeli[1][open_infoheader->height - 1 - i][j], sizeof(unsigned char), 1, f1);
			fread(&matrice_rgb_pixeli[0][open_infoheader->height - 1 - i][j], sizeof(unsigned char), 1, f1);
		}
		fseek(f1, padding, SEEK_CUR);
	}
	// printam matricea de culori
	printf("\nR G B (asa cum apar in imagine)\n\n");
	for (int i = 0; i < open_infoheader->height; i++)
	{
		for (int j = 0; j < open_infoheader->width; j++)
		{
			printf("%d %d %d   ", matrice_rgb_pixeli[0][i][j], matrice_rgb_pixeli[1][i][j], matrice_rgb_pixeli[2][i][j]);
		}
		printf("\n");
	}
	printf("\n");
	fclose(f1);
}