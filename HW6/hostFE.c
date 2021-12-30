#include <stdio.h>
#include <stdlib.h>
#include "hostFE.h"
#include "helper.h"

void hostFE(int filterWidth, float *filter, int imageHeight, int imageWidth,
            float *inputImage, float *outputImage, cl_device_id *device,
            cl_context *context, cl_program *program)
{
    cl_int status;
    int filterSize = filterWidth * filterWidth * sizeof(float);
    int mem_size = imageHeight * imageWidth * sizeof(float);

    // create command queue
    cl_command_queue commandQueue = clCreateCommandQueue(*context, *device, 0, &status);

    // allocate device memory
    cl_mem d_filter = clCreateBuffer(*context, CL_MEM_READ_ONLY, filterSize, NULL, &status);
    cl_mem d_inputImage = clCreateBuffer(*context, CL_MEM_READ_ONLY, mem_size, NULL, &status);
    cl_mem d_outputImage = clCreateBuffer(*context, CL_MEM_WRITE_ONLY, mem_size, NULL, &status);

    // copy data from host memory to device memory
    status=clEnqueueWriteBuffer(commandQueue, d_inputImage , CL_TRUE, 0,mem_size, inputImage, 0, NULL, NULL);
    status=clEnqueueWriteBuffer(commandQueue, d_filter, CL_TRUE, 0,filterSize, filter, 0, NULL, NULL);

    // create kernel function
    cl_kernel kernelFunc = clCreateKernel(*program, "convolution", status);

    clSetKernelArg(kernelFunc, 0, sizeof(cl_int), (void *)&filterWidth);
    clSetKernelArg(kernelFunc, 1, sizeof(cl_mem), (void *)&d_filter);
    clSetKernelArg(kernelFunc, 2, sizeof(cl_int), (void *)&imageHeight);
    clSetKernelArg(kernelFunc, 3, sizeof(cl_int), (void *)&imageWidth);
    clSetKernelArg(kernelFunc, 4, sizeof(cl_mem), (void *)&d_inputImage);
    clSetKernelArg(kernelFunc, 5, sizeof(cl_mem), (void *)&d_outputImage);

    size_t localws[2] = {25, 25};
    size_t globalws[2] = {imageWidth, imageHeight};
    
    // execute kernel function
    clEnqueueNDRangeKernel(commandQueue, kernelFunc, 2, 0, globalws, localws, 0, NULL, NULL);
    // copy data from device memory to host memory
    clEnqueueReadBuffer(commandQueue,d_outputImage, CL_TRUE, 0, mem_size, (void*)outputImage, NULL, NULL, NULL);

    // release opencl object
    status = clReleaseCommandQueue(commandQueue);
    status = clReleaseMemObject(d_filter);
    status = clReleaseMemObject(d_inputImage);
    status = clReleaseMemObject(d_outputImage);
    status = clReleaseKernel(kernelFunc);
}