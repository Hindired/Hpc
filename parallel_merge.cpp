
// PRE PROCESSING INSTRUCTIONS
#include<iostream>
#include<cstdlib>
#include<assert.h>
#include<ctime>
#include<omp.h>

#define TRUE  1

//using namespace std;

// FUNCTION DECLARATIONS
void mergesort(int* p_arr, int i, int j);
void merge(int* p_arr, int p, int q, int r);

// ENTRY POINT OF MAIN FUNCTION
int main(void)
{ 
	int* arr = NULL;
	int nr_elements = 0;
	double startTime = 0;
	double endTime = 0;
	double seq_time = 0; 
	double par_time = 0;

	std::cout<<"\n enter total no of elements=>";
	std::cin>>nr_elements;

	arr = (int*) malloc(sizeof(int) * nr_elements);

	for(int i = 0; i<nr_elements; i++)
	{
    	arr[i] = rand();
	}

	std::cout<< "printing unsorted array" << std::endl;

	for(int i = 0; i < nr_elements ; i++)
	{
		std::cout<< "arr[" << i << "] = " << arr[i] << std::endl;
	}

    // Sequential algorithm 
    startTime = omp_get_wtime();             // start time
	mergesort(arr, 0, nr_elements - 1);      // calling merge sort
	endTime = omp_get_wtime();               // end time
    seq_time =  endTime - startTime;
    std::cout << "\nSequential Time: " << seq_time << std::endl;

	// parallel algorithm
	startTime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergesort(arr, 0, nr_elements - 1); 
        }
    }
    endTime = omp_get_wtime();
    par_time = endTime - startTime;
    std::cout << "\nParallel Time: " << par_time << std::endl;


	std::cout<<"\n printing sorted array is" << std::endl;

	for(int i = 0 ; i < nr_elements ; i++)
	{
    	std::cout<< "arr[" << i << "] = " << arr[i] << std::endl;
	}

	exit(EXIT_SUCCESS);
}

void mergesort(int* p_arr, int p, int r)
{
	int q;
	if(p < r) 
	{
    	q = (p+r) / 2;
   	 
    	#pragma omp parallel sections
    	{

        	#pragma omp section
        	{
            	mergesort(p_arr, p, q);   	 
        	}

        	#pragma omp section
        	{
            	mergesort(p_arr, q+1, r);    
        	}
    	}

    	merge(p_arr, p, q, r);    
	}
    
	return;
}
 
void merge(int* p_arr, int p, int q, int r)
{
	 int* p_arr1 = NULL;
    int  N1 = 0;

    int* p_arr2 = NULL;
    int  N2 = 0;

    N1 = q-p+1;
    N2 = r-q;

    p_arr1 = (int*) malloc(N1 * sizeof(int));
    p_arr2 = (int*) malloc(N2 * sizeof(int));
    assert(p_arr1 != NULL && p_arr2 != NULL);

    
    for(int le = 0; le < N1 ; le++)
    {
        p_arr1[le] = p_arr[p + le];
    }

    for(int le = 0; le < N2 ; le++)
    {
       p_arr2[le] = p_arr[q+1 + le];
    }

    //output_arr(p_arr1 , N1, "subarray 1: ");
    //output_arr(p_arr2 , N2, "subarray 2: ");

    int i = 0;
    int j = 0;
    int k = 0;

    
    while(TRUE)
    {
        if(p_arr1[i] <= p_arr2[j])
        {
           p_arr[p+k] = p_arr1[i];
           i++;
           k++;

           if(i == N1)
           {
              while(j < N2)
              {
                p_arr[p+k] = p_arr2[j];
                j++;
                k++;
              }
              break;
           }
        }
        else
        {
           p_arr[p+k] = p_arr2[j];
           j++;
           k++;

           if(j == N2)
           {
              while(i < N1)
              {
                p_arr[p+k] = p_arr1[i];
                i++;
                k++;
              }
              break;
           }
        }
    }

    free(p_arr1);
    p_arr1 = NULL;

    free(p_arr2);
    p_arr2 = NULL;

    return;
}






