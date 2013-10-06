#include <stdio.h>
#include <pthread.h>
#include <time.h>

void readFile();
void insertSort(int start, int end);
static void *threadFunc(void *vptr_args);
void recordFile();
void recordFile1();
int* array;
int length;
pthread_t firstThr, secondThr, resultThr;
struct parms
{
	int left;
	int right;
}p;

main()
{
	clock_t timer;
	clock_t timer1;
	readFile();
	struct parms first = {0, length / 2};
	struct parms second = {length / 2, length};
	struct parms result = {0, length};
	timer = clock();
	pthread_create(&firstThr, NULL, threadFunc, &first);
	pthread_create(&secondThr, NULL, threadFunc, &second);
	pthread_join(firstThr, NULL);
	pthread_join(secondThr, NULL);
	pthread_create(&resultThr, NULL, threadFunc, &result);
	timer = clock() - timer;
	pthread_join(resultThr, NULL);
	printf("Time for thread sort: %f\n", (double)timer/CLOCKS_PER_SEC);
	//printf("\n");
	recordFile();
    delete[] array;
	
	readFile();
	timer1 = clock();
	insertSort(result.left, result.right);
	timer1 = clock() - timer1;
	printf("Time for sort: %f\n", (double)timer1/CLOCKS_PER_SEC);
	recordFile1();
	delete[] array;
}

static void *threadFunc(void *vptr_args)
{
	struct parms *arg = (struct parms *)vptr_args;
	insertSort(arg->left, arg->right);

}


// static void *firstPart(void *vptr_args)
// {
// 	insertSort(0, (p.length - 1) / 2);

// }

	
void readFile()
{
	FILE *f;
	f = fopen("in.txt", "rt");
	if(!f)
   	{
    	printf("Can't open in.txt\n");
   	}
   	 	   
	else
	{
		fscanf(f, "%d", &length);
		array = new int[length];
		for(int i = 0; i <= length; i++)
		{
			fscanf(f, "%d", &array[i]);
		}
	}
}



void insertSort(int start, int end)
{
	// struct params *first = arg;
	// struct params *second = arg;
	// struct params *result = arg;
	//params = (struct parms_t)*arg;
	//int len = end - start + 1;
 	int i, j, temp;
      for (i = start; i < end; i++)
      {
            temp = array[i];
            for (j = i - 1; j >= start; j--)
            {
                  if (array[j] < temp)
                  break;
                  array[j + 1] = array[j];
                  array[j] = temp;
            }   
      }
}


void recordFile()
{
	FILE *f;
	f = fopen("out.txt", "wt");
	if(!f)
   {
      printf("Can't open out.txt\n");
   }
   else
   {
		fprintf(f, "%d", length);
		fprintf(f, "\n");
		for(int i = 0; i < length; i++)
		{
			fprintf(f, "%d", array[i]);
			fprintf(f, " ");
		}
	}
}

void recordFile1()
{
	FILE *f;
	f = fopen("out1.txt", "wt");
	if(!f)
   {
      printf("Can't open out.txt\n");
   }
   else
   {
		fprintf(f, "%d", length);
		fprintf(f, "\n");
		for(int i = 0; i < length; i++)
		{
			fprintf(f, "%d", array[i]);
			fprintf(f, " ");
		}
	}
}

