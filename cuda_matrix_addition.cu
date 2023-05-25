
// HEADERS
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void arradd(int *x, int *y, int *z) // kernel definition
{
    int id = blockIdx.x;
    /* blockIdx.x gives the respective block id which starts from 0 */
    z[id] = x[id] + y[id];
}

//ENTRY POINT OF MAIN FUNCTION
int main(void)  
{
    int arr1[6];
    int arr2[6];
    int arr3[6];
    int *gpu_arr1, *gpu_arr2, *gpu_arr3;
    int i;


    printf("\n putting values in first array\n");
    for (i = 0; i < sizeof(arr1)/sizeof(arr1[0]) ; i++)
    {
        arr1[i] = rand() % 1024;
    }
    printf("\n putting values in second array\n");
    for (i = 0; i < sizeof(arr1)/sizeof(arr1[0]) ; i++)
    {
        arr2[i] = rand();
    }

    printf("\nprinting values of first array\n");
    for (i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++)
    {
        printf("arr1[%d] = %d\n", i, arr1[i]);
    }

    printf("\nprinting values of second array\n");
    for (i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++)
    {
        printf("arr2[%d] = %d\n", i, arr2[i]);
    }


    /* cudaMalloc() allocates memory from Global memory on GPU */
    cudaMalloc((void **)&gpu_arr1, 6 * sizeof(int)); 
    cudaMalloc((void **)&gpu_arr2, 6 * sizeof(int));
    cudaMalloc((void **)&gpu_arr3, 6 * sizeof(int));

    /* cudaMemcpy() copies the contents from destination to source. Here destination is GPU(gpu_arr1, gpu_arr2)
    and source is CPU(a,b) */
    cudaMemcpy(gpu_arr1, arr1, 6 * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_arr2, arr2, 6 * sizeof(int), cudaMemcpyHostToDevice);

    /* call to kernel. Here 6 is number of blocks, 1 is the number of threads per block and gpu_arr1, gpu_arr2, gpu_arr3 are
    the arguments */
    arradd<<<6, 1>>>(gpu_arr1, gpu_arr2, gpu_arr3);
    
    /* Here we are copying content from GPU(Device) to CPU(Host) */
    cudaMemcpy(arr3, gpu_arr3, 6 * sizeof(int), cudaMemcpyDeviceToHost);
    printf("\nSum of two arrays:\n ");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", arr3[i]);
    }

    /* Free the memory allocated to pointers gpu_arr1, gpu_arr2, gpu_arr3 */
    cudaFree(gpu_arr1);
    cudaFree(gpu_arr2);
    cudaFree(gpu_arr3);

    return 0;
}
