#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void mandelKernel(int* d_pixels, float stepX, float stepY, float lowerX, float lowerY, int maxIterations, int pitch) {
    // To avoid error caused by the floating number, use the following pseudo code
    //
    // float x = lowerX + thisX * stepX;
    // float y = lowerY + thisY * stepY;
    int thisX = blockIdx.x * blockDim.x + threadIdx.x;
    int thisY = blockIdx.y * blockDim.y + threadIdx.y;
    // int index = thisX + thisY * width;

    float c_x = lowerX + thisX * stepX;
    float c_y = lowerY + thisY * stepY;

    float z_x = c_x;
    float z_y = c_y;
    int i; // i: iteration
    for (i = 0; i < maxIterations; ++i){
        if (z_x * z_x + z_y * z_y > 4.f) 
            break;

        float new_x = z_x * z_x - z_y * z_y;
        float new_y = 2.f * z_x * z_y;
        z_x = c_x + new_x;
        z_y = c_y + new_y;
    }

    int* row = (int*)((char*)d_pixels + thisY * pitch);
    row[thisX] = i;
    // d_pixels[index] = i;    
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;
    int size=resX * resY *sizeof(int); //N = resX * resY  //size=N*sizeof(int)
    size_t pitch = 0;

    int *h_pixels, *d_pixels;
    cudaHostAlloc(&h_pixels, size, cudaHostAllocMapped);
    cudaMallocPitch(&d_pixels, &pitch, resX * sizeof(int), resY);

    dim3 threadsPerBlock(25, 25);
    dim3 numBlock(resX/threadsPerBlock.x, resY/threadsPerBlock.y);
    
    mandelKernel<<<numBlock, threadsPerBlock>>>(d_pixels, stepX, stepY, lowerX, lowerY, maxIterations,pitch);
    
    cudaMemcpy2D(h_pixels,resX * sizeof(int), d_pixels, pitch, resX * sizeof(int), resY, cudaMemcpyDeviceToHost);
    memcpy(img, h_pixels, size);

    cudaFree(d_pixels);
    cudaFreeHost(h_pixels);
}
