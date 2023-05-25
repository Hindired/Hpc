
// PREPROCESSING INSTRUCTIONS
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<omp.h>

//using namespace std;

// GLOBAL VAIRABLE
double startTime = 0;
double endTime = 0; 

// FUNCTION DECLARATIONS
void bubble(int* arr, int size);
void swap(int &, int &);

// ENTRY POINT OF MAIN FUNCTION
int main(void)
{
    // LOCAL VAIRABLES
    int* arr = NULL;
    int nr_elements = 0;
    double startTime = 0;
    double endTime = 0;
    double seq_time = 0;
    double par_time = 0;    


    std::cout<<"\n enter total no of elements=>";
    std::cin>>nr_elements;

    arr = (int*) malloc(sizeof(int) * nr_elements);

    for(int i = 0 ; i < nr_elements ; i++)
    {
   	   arr[i] = rand();
    }

    std::cout<< "printing unsorted array" << std::endl;
    
    for(int i = 0; i < nr_elements ; i++)
    {
        std::cout<< "arr[" << i << "] = " << arr[i] << std::endl;
    }

    
    // Sequential algorithm 
    startTime = omp_get_wtime();      // start time
    bubble(arr, nr_elements);          // bubble sort call
    endTime = omp_get_wtime();        // end time
    seq_time = endTime - startTime;
    std::cout << "\nSequential Time: " << seq_time << std::endl;

    
    // parallel algorithm
    startTime = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            bubble(arr, nr_elements); 
        }
    }
    endTime = omp_get_wtime();
    par_time = endTime - startTime;
    std::cout << "\nParallel Time: " << par_time << std::endl;
    
    
    std::cout<<"\n printing sorted array " <<std::endl;

    for(int i = 0; i < nr_elements ; i++)
    {
        std::cout<< "arr[" << i << "] = " << arr[i] << std::endl;
    }

    std::cout<< std::endl;


    exit(EXIT_SUCCESS);
}

void bubble(int *arr, int size)
{
    startTime = omp_get_wtime();

    for(int i = 0;  i < size ; i++) 
    {  	 
   	   int first = i % 2; 

   	   #pragma omp parallel for shared(a, first)
   	   for(int j = first ; j < (size - 1) ;  j += 2)
   	   {  	 
   		  if(arr[j] > arr[j+1])
   		  {  	 
     		swap(arr[ j ], arr[ j+1 ]);
   		  }  	 
   	   }  

       	 
    }
    
    endTime = omp_get_wtime();

    return;
}


void swap(int &a, int &b)
{

    int test;
    test = a;
    a = b;
    b = test;

    return;
}



