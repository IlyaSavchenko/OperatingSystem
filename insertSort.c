#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>


void readFile();
void sort(int start, int end);
static void *threadFunc(void *vptr_args);
void mergeArray(int *newArr);
void recordFile(int *arr);
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
	readFile();
	struct parms first = {0, length / 2};
	struct parms second = {length / 2, length};
	struct timespec startThread;
    clock_gettime(1, &startThread);
	pthread_create(&firstThr, NULL, threadFunc, &first);
	pthread_create(&secondThr, NULL, threadFunc, &second);
	pthread_join(firstThr, NULL);
	pthread_join(secondThr, NULL);
	int *final = new int[length];
	mergeArray(final);
	struct timespec stopThread;
	clock_gettime(1, &stopThread);
    printf("ThreadSort: %d sec %lu nanosec\n", abs(stopThread.tv_sec - startThread.tv_sec), labs(stopThread.tv_nsec - startThread.tv_nsec));
    recordFile(final);
	
	readFile();
	struct timespec startSort;
    clock_gettime(1, &startSort);
	sort(0, length);
	struct timespec stopSort;
	clock_gettime(1, &stopSort);
    printf("ThreadSort: %d sec %lu nanosec\n", abs(stopSort.tv_sec - startSort.tv_sec), labs(stopSort.tv_nsec - startSort.tv_nsec));
	recordFile1();
}

static void *threadFunc(void *vptr_args)
{
	struct parms *arg = (struct parms *)vptr_args;
	sort(arg->left, arg->right);

}

	
void readFile()
{
	FILE *f;
	f = fopen("./in.txt", "rt");
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


void sort(int start, int end)
{
	// //int len = end - start + 1;
 	// int i, j, temp;
  //     for (i = start; i < end; i++)
  //     {
  //           temp = array[i];
  //           for (j = i - 1; j >= start; j--)
  //           {
  //                 if (array[j] < temp)
  //                 break;
  //                 array[j + 1] = array[j];
  //                 array[j] = temp;
  //           }   
  //     }
	for (int i = start; i < end - 1; ++i) {
/* устанавливаем начальное значение минимального индекса */
        int min_i = i;
        /* находим индекс минимального элемента */
        for (int j = i + 1; j < end; ++j) {
                if (array[j] < array[min_i]) {
                        min_i = j;
                }
        }
        /* меняем значения местами */
        int temp = array[i];
        array[i] = array[min_i];
        array[min_i] = temp;
}
}


	void mergeArray(int *newArr){
	int c1 = 0, c2 = length / 2;
    for (int i = 0; i < length; i++) {
        if (c1 < length / 2 && c2 <= length) {
            newArr[i] = array[c1] > array[c2] ? array[c2++] : array[c1++];
        }	
        if (c1 > length / 2 && c2 <= length) {
            newArr[i] = array[c2++];
        }
        if (c1 <= length / 2 && c2 > length) {
            newArr[i] = array[c1++];
        }
    }
}


void recordFile(int *arr)
{
	FILE *f;
	f = fopen("./out.txt", "wt");
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
			fprintf(f, "%d", arr[i]);
			fprintf(f, " ");
		}
	}
}

void recordFile1()
{
	FILE *f;
	f = fopen("./out1.txt", "wt");
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
