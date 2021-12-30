__kernel void convolution(int filterWidth, __constant float * filter,
			  int imageHeight, int imageWidth,
			  __global float * inputImage, __global float * outputImage) 
{
    int row = get_global_id(1);
    int col = get_global_id(0);

    int halffilterSize = filterWidth / 2;
    float sum=0;
    int k, l;

    for (k = -halffilterSize; k <= halffilterSize; k++){
        for (l = -halffilterSize; l <= halffilterSize; l++){
            if(filter[(k + halffilterSize) * filterWidth + l + halffilterSize] != 0){
                if (row + k >= 0 && row + k < imageHeight && col + l >= 0 && col + l < imageWidth){
                        sum += inputImage[(row + k) * imageWidth + col + l] *
                            filter[(k + halffilterSize) * filterWidth + l + halffilterSize];
                }
            }
        }
    }
    outputImage[row * imageWidth + col] = sum;
}
