#include "PPintrin.h"
#include <iostream>
// implementation of absSerial(), but it is vectorized using PP intrinsics
void absVector(float *values, float *output, int N)
{
  __pp_vec_float x;
  __pp_vec_float result;
  __pp_vec_float zero = _pp_vset_float(0.f);
  __pp_mask maskAll, maskIsNegative, maskIsNotNegative;

  //  Note: Take a careful look at this loop indexing.  This example
  //  code is not guaranteed to work when (N % VECTOR_WIDTH) != 0.
  //  Why is that the case?
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {

    // All ones
    maskAll = _pp_init_ones();

    // All zeros
    maskIsNegative = _pp_init_ones(0);

    // Load vector of values from contiguous memory addresses
    _pp_vload_float(x, values + i, maskAll); // x = values[i];

    // Set mask according to predicate
    _pp_vlt_float(maskIsNegative, x, zero, maskAll); // if (x < 0) {

    // Execute instruction using mask ("if" clause)
    _pp_vsub_float(result, zero, x, maskIsNegative); //   output[i] = -x;

    // Inverse maskIsNegative to generate "else" mask
    maskIsNotNegative = _pp_mask_not(maskIsNegative); // } else {

    // Execute instruction ("else" clause)
    _pp_vload_float(result, values + i, maskIsNotNegative); //   output[i] = x; }

    // Write results back to memory
    _pp_vstore_float(output + i, result, maskAll);
  }
}

void clampedExpVector(float *values, int *exponents, float *output, int N)
{
  //
  // PP STUDENTS TODO: Implement your vectorized version of
  // clampedExpSerial() here.
  //
  // Your solution should work for any value of
  // N and VECTOR_WIDTH, not just when VECTOR_WIDTH divides N
  //
  __pp_vec_float singleVal;
  __pp_vec_int singleExp;
  __pp_vec_float result;
  __pp_vec_int intAllZero = _pp_vset_int(0);
  __pp_vec_int intAllOne = _pp_vset_int(1);
  __pp_vec_float clampBound = _pp_vset_float(9.999999f);

  __pp_mask maskAll,notfinish,maskNumElements,clampMask,finish; 
  maskAll=_pp_init_ones();
  printf("N: %d\n",N); 
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  {
    maskNumElements=_pp_init_ones(N - i); // all ones
    _pp_vload_int(singleExp,exponents+i,maskNumElements);
    _pp_vload_float(singleVal,values+i,maskNumElements);
    //_pp_veq_int(finish,singleExp,intAllZero,maskNumElements);
    //notfinish=_pp_mask_not(finish);
    _pp_vgt_int(notfinish,singleExp,intAllZero,maskNumElements);
    result=_pp_vset_float(1.f);// all one at begining    

    while(_pp_cntbits(notfinish)){
      _pp_vmult_float(result,result,singleVal,notfinish);
      _pp_vsub_int(singleExp,singleExp,intAllOne,notfinish);//update singleExp
      //_pp_veq_int(finish,singleExp,intAllZero,notfinish);
      //notfinish=_pp_mask_not(finish);
      _pp_vgt_int(notfinish,singleExp,intAllZero,notfinish);//notfinish//maskNumElements?? //update not finish vector
    }
    //clampMask, initial 0, if greater than 9.999999f, becomes 1
    _pp_vgt_float(clampMask,result,clampBound,maskNumElements); 
    _pp_vmove_float(result,clampBound,clampMask);
    _pp_vstore_float(output+i,result,maskNumElements);
  }
}

// returns the sum of all elements in values
// You can assume N is a multiple of VECTOR_WIDTH
// You can assume VECTOR_WIDTH is a power of 2
float arraySumVector(float *values, int N)
{
  //
  // PP STUDENTS TODO: Implement your vectorized version of arraySumSerial here
  //
  __pp_mask maskAll,maskNumElements; 
  __pp_vec_float orginVal;
  maskAll=_pp_init_ones();
  float finalSum=0.0;
  for (int i = 0; i < N; i += VECTOR_WIDTH)
  { 
    _pp_vload_float(orginVal, values + i, maskAll); 
    int copyWidth=VECTOR_WIDTH;
    while(copyWidth>2){
      _pp_hadd_float(orginVal,orginVal);
      _pp_interleave_float(orginVal,orginVal);
      copyWidth/=2;
    }
    _pp_hadd_float(orginVal,orginVal);
    _pp_vstore_float(values+i,orginVal,maskAll);
  }
  // for (int i=0;i<N;i++){
  //   printf("values: %f\n",*(values+i)); 
  // }
  for (int i = 0; i < N; i += VECTOR_WIDTH){
    finalSum+=*(values+i);
  }
  return finalSum;
}