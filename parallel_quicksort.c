#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<stdlib.h>

#define N 2
#define MAX 10
int A[MAX]={3,1,5,2,8,6,9,4,7,3};

struct v
{
	int l;
	int h;
};


void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

int partition(int l,int h)
{
	int j;
	int pivot=A[h];
	int i=l-1;
	for(j=l;j<h;j++)
	{
		if(A[j]<=pivot)
		{
			i++;
			swap(&A[i],&A[j]);
		}
	}
	swap(&A[i+1],&A[h]);
	return (i+1);	
}


void * quicksort(void * arg)
{
	struct v *data=arg;
	pthread_t thread[N];
	struct v pt[N];

	if((data->l) < (data->h))
	{
		int p=partition(data->l,data->h);
		int i;

		pt[0].l=data->l;
		pt[0].h=p-1;
		pt[1].l=p+1;
		pt[1].h=data->h;

		for(i=0;i<N;i++)
			pthread_create(&thread[i],NULL,quicksort,&pt[i]);
		for(i=0;i<N;i++)
			pthread_join(thread[i],NULL);
	}	
}

int main(int argc, char * argv[])
{
	int i;
	pthread_t t;
	struct v *data=(struct v*)malloc(sizeof(struct v));
	data->l=0;
	data->h=MAX-1;
	pthread_create(&t,NULL,quicksort,data);	
	pthread_join(t,NULL);
	printf("Sorted array using quicksort is:\n");
	for(i=0;i<MAX;i++)
		printf("%d ",A[i]);

	printf("\n");
}

