#include <stdio.h>
#include <stdlib.h>    
#include <time.h>       

void randomFile(const char* name, int size)
{
	FILE* f = fopen(name, "wt");
	fprintf(f, "%d\n", size);
	for (int i = 0; i < size; i++)
	{
		int num = rand() % 100001;
		int flag = rand() % 2;
		if (flag == 0)
			num *= -1;
		fprintf(f, "%d ", num);
		fprintf(f, " ");
	}
	fclose(f);
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	if (argc == 3)
	{
		const char* file = argv[1];
		int size = atoi(argv[2]);
		randomFile(file, size);
	}
	return 0;
}
