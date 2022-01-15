#include "bmp_header.h"
int main()
{
	char command[100];
	char filename[100];
	bmp_pntr edit_mode;
	fscanf(stdin, "%s %s", &command, &filename);
	if ((strcmp("edit", command)) == 0)
	{
		edit_mode=edit(filename);
	}
	if ((strcmp("save", command)) == 0)
	{
		save(filename);
	}
	return 0;
}