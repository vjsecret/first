#include <stdio.h>
#include <windows.h>
static char *sSDKsample = "matrixmul";
void computeGold(float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

main()
{ 
    printf("[ %s ]\n", sSDKsample);  
    
   
    //shrSetLogFileName ("matrixMul.txt");
    //shrLog("%s Starting...\n\n", argv[0]);
//    cutilSafeCall(cudaGetDevice(&devID));
//cudaDeviceProp props;
     // set seed for rand()                 
     srand(2006);
     unsigned int uiWA, uiHA, uiWB, uiHB, uiWC, uiHC;
      int iSizeMultiple = 1;
  // For GPUs with fewer # of SM's, we limit the maximum size of the matrix
//	if (props.multiProcessorCount <= 4) {
//	    uiWA = 2 * BLOCK_SIZE * iSizeMultiple;
//	    uiHA = 4 * BLOCK_SIZE * iSizeMultiple;
//		uiWB = 2 * BLOCK_SIZE * iSizeMultiple;
//		uiHB = 4 * BLOCK_SIZE * iSizeMultiple;
//		uiWC = 2 * BLOCK_SIZE * iSizeMultiple;
//		uiHC = 4 * BLOCK_SIZE * iSizeMultiple;
//	} else {
		uiWA = WA * iSizeMultiple;
		uiHA = HA * iSizeMultiple;
		uiWB = WB * iSizeMultiple;
		uiHB = HB * iSizeMultiple;
		uiWC = WC * iSizeMultiple;
		uiHC = HC * iSizeMultiple;
//	}
    // allocate host memory for matrices A and B
    unsigned int size_A = uiWA * uiHA;
    unsigned int mem_size_A = sizeof(float) * size_A;
    float* h_A = (float*)malloc(mem_size_A);
    unsigned int size_B = uiWB * uiHB;
    unsigned int mem_size_B = sizeof(float) * size_B;
    float* h_B = (float*)malloc(mem_size_B);
    // initialize host memory
    randomInit(h_A, size_A);
    randomInit(h_B, size_B);
	system ("pause");
}
