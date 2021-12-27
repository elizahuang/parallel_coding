#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void mandelKernel(int* d_pixels, int width, float stepX, float stepY, float lowerX, float lowerY, int count) {
    // To avoid error caused by the floating number, use the following pseudo code
    //
    // float x = lowerX + thisX * stepX;
    // float y = lowerY + thisY * stepY;
    int thisX = blockIdx.x * blockDim.x + threadIdx.x;
    int thisY = blockIdx.y * blockDim.y + threadIdx.y;
    int index = thisX + thisY * width;

    float c_x = lowerX + thisX * stepX;
    float c_y = lowerY + thisY * stepY;

    float z_x = c_x;
    float z_y = c_y;
    int i; // i: iteration
    for (i = 0; i < count; ++i){
        if (z_x * z_x + z_y * z_y > 4.f) 
            break;

        float new_x = z_x * z_x - z_y * z_y;
        float new_y = 2.f * z_x * z_y;
        z_x = c_x + new_x;
        z_y = c_y + new_y;
    }

    d_pixels[index] = i;    
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;
    int size=resX * resY *sizeof(int); //N = resX * resY  //size=N*sizeof(int)

    int *h_pixels, *d_pixels;

    // h_pixels = (int *)malloc(size);
    cudaMalloc((void **)&d_pixels, size);

    dim3 threadsPerBlock(25, 25);
    dim3 numBlock(resX/threadsPerBlock.x, resY/threadsPerBlock.y);
    
    mandelKernel<<<numBlock, threadsPerBlock>>>(d_pixels, resX, stepX, stepY, lowerX, lowerY, maxIterations);
    
    cudaMemcpy(img, d_pixels, size, cudaMemcpyDeviceToHost);
    // memcpy(img, h_pixels, size);

    cudaFree(d_pixels);
    // free(h_pixels);
}


/*
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void mandelKernel() {
    // To avoid error caused by the floating number, use the following pseudo code
    //
    // float x = lowerX + thisX * stepX;
    // float y = lowerY + thisY * stepY;
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;
}
*/