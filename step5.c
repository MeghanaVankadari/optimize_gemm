#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#define mat_alloc(r,c) (int *)malloc(r*c*sizeof(int))
int m,n,k;
int *first,*second,*multiply;
#define A(i,j) first[ (j)*m + (i) ] //mxk matrix
#define B(i,j) second[(j)*k +i] //kxn matrix
#define C(i,j) multiply[(j)*m +i] //mxn matrix
void print_matrix(int *address,int rows, int columns)	//function to print a matrix
{
	int c,d;
	for (c = 0; c < rows; c++) {
      		for (d = 0; d < columns; d++)
        		printf("%d\t", *(address+d*rows +c));
      	printf("\n");
    	}
}

void AddDot1x4( int k, int *first, int lda,  int *second, int ldb, int *multiply, int ldc )
{
int p;

  //  AddDot( k, &A( 0, 0 ), lda, &B( 0, 0 ), &C( 0, 0 ) );
  for ( p=0; p<k; p++ ){
	C( 0, 0 ) += A( 0, p ) * B( p, 0 );
	C( 0, 1 ) += A( 0, p ) * B( p, 1 );
	C( 0, 2 ) += A( 0, p ) * B( p, 2 );
	C( 0, 3 ) += A( 0, p ) * B( p, 3 );

  }
}

double cpu_time_used = 0;
int main(int argc,char *argv[])
{
	struct timeval start, end;
	//start = clock();
	if(argc!=5)
	{
		printf("usage: ./a.out m k n iterations\n");
		exit(1);
	}
	m = atoi(argv[1]);
	k = atoi(argv[2]);
	n = atoi(argv[3]);
	int iterations = atoi(argv[4]);
	//printf("size = %d , iterations = %d\n",size,iterations);
	//int m,n,k;
	int ite = 0;
	for(ite = 0; ite < iterations ; ite++)
	{
	//start = clock();
	first = mat_alloc(m,k);
	second = mat_alloc(k,n);
	multiply = mat_alloc(m,n);
	if(first ==NULL || second ==NULL || multiply == NULL)
	{
		printf("Failed to allocate memory\n");
		return -1;
	}
	int c,d,e,sum = 0;
	for (c = 0; c < m; c++)
        	for (d = 0; d < k; d++){
            		A(c,d) = rand()%10+1;
		}
	for (c = 0; c < k; c++)
        	for (d = 0; d < n; d++){
            		B(c,d) = rand()%10+1;
		}

	gettimeofday(&start,NULL);
	for (d = 0; d < n; d = d+4) {
      		for (c = 0; c < m; c++) {
			//printf("inside for loops\n");
        		AddDot1x4( k, &A( c,0 ), m, &B( 0,d ), k, &C( c,d ), m );
      		}
    	}
 
    	/*printf("Product of the matrices:\n");
	for (c = 0; c < size; c++) {
      		for (d = 0; d < size; d++)
        		printf("%d\t", *(multiply+c*size+d));
      	printf("\n");
    	}*/
	printf("first matrix\n");
	print_matrix(first,m,k);
	printf("second matrix:\n");
	print_matrix(second,k,n);
	printf("product Mtrix:\n");
	print_matrix(multiply,m,n);
	gettimeofday(&end,NULL);
	cpu_time_used = cpu_time_used + (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
	}
	cpu_time_used = cpu_time_used / iterations;
	//printf("%d	%f\n",size,cpu_time_used);
	return 0;
}
