#include <stdio.h>

#include "Windows3D.h"

int main()
{
	try
	{
		Windows3D window = Windows3D();
	}
	catch (char *err)
	{
		fprintf(stderr, "error: %s\n", err);
#ifdef WINDOWS
		system("pause");
#endif
	}

	return 0;
}