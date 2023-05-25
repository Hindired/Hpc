#include <iostream>
#include <omp.h>
#include <climits>


//using namespace std;

void min_reduction(int* arr, int n) 
{
  int min_value = INT_MAX;

  #pragma omp parallel for reduction(min: min_value)
  for(int i = 0; i < n; i++)
  {
	  if (arr[i] < min_value) 
    {
  	  min_value = arr[i];
	  }
  }

  std::cout << "Minimum value: " << min_value << std::endl;
  
  return;
}

void max_reduction(int* arr, int n)
{
  int max_value = INT_MIN;

  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++)
  {
	  if (arr[i] > max_value) 
    {
  	  max_value = arr[i];
	  }
  }

  std::cout << "Maximum value: " << max_value << std::endl;

  return;
}

void sum_reduction(int* arr, int n) 
{
  int sum = 0;

  #pragma omp parallel for reduction(+: sum)
  for(int i = 0; i < n; i++) 
  {
	  sum += arr[i];
  }

  std::cout << "Sum: " << sum << std::endl;

  return;
}

void average_reduction(int* arr, int n) 
{
  int sum = 0;

  #pragma omp parallel for reduction(+: sum)

  for(int i = 0; i < n ; i++) 
  {
	  sum += arr[i];
  }

  std::cout << "Average: " << (double)sum / (n-1) << std::endl;

  return;
}


// ENTRY POINT OF MAIN FUNCTION
int main(void) 
{
  int *arr = NULL;
  int nr_elements = 0;
  double startTime = 0;
	double endTime = 0;
	double seq_time = 0; 
	double par_time = 0;
    
  std::cout<<"\n enter total no of elements=>" <<std::endl;
  std::cin>>nr_elements;
    
  arr = (int*) malloc(sizeof(int) * nr_elements);

  //printf("size of *arr = %d", sizeof((*arr)));

  //cout<<"\n enter elements=>";

  for(int i=0; i < nr_elements ; i++)
  {
   	arr[i] = rand();
  }

  // printing array
  for(int i = 0; i < nr_elements ; i++)
  {
    std::cout<<"arr[" << i << "] = " << arr[i] <<std::endl;
  }

  std::cout<< std::endl;

  
  // Implementing functions
  
  startTime = omp_get_wtime();
  min_reduction(arr, nr_elements);
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\n Time taken: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;
   
  startTime = omp_get_wtime();
  max_reduction(arr, nr_elements);
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\n Time Taken: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;

  startTime = omp_get_wtime();
  sum_reduction(arr, nr_elements);
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\nTime taken: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;

  startTime = omp_get_wtime();
  average_reduction(arr, nr_elements);
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\nTime Taken: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;


  std::cout<< std::endl;

  /*// parallel algorithms
  std::cout<< "\t\t parallel implemintation" << std::endl;
  
  startTime = omp_get_wtime();
  #pragma omp parallel
  {
    min_reduction(arr, nr_elements);
  }
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\nparallel Time: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;
   
  startTime = omp_get_wtime();
  #pragma omp parallel
  {
    max_reduction(arr, nr_elements);
  }
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\nparallel Time: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;

  startTime = omp_get_wtime();
  #pragma omp parallel
  {
    sum_reduction(arr, nr_elements);
  }
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\nparallel Time: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;

  startTime = omp_get_wtime();
  #pragma omp parallel
  {
    average_reduction(arr, nr_elements);
  }
  endTime = omp_get_wtime();
  seq_time =  endTime - startTime;
  std::cout << "\nparallel Time: " << seq_time << std::endl;
  std::cout << "------------------------" << std::endl;*/

  exit(EXIT_FAILURE);
}

