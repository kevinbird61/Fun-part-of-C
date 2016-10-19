#include <stdio.h>
#include <xmmintrin.h>

void naive_sum(float *src1,float *src2,float *res,int length){
  for(int i=0;i<length;i++){
    res[i] = src1[i]+src2[i];
  }
}

void sse_sum(float *src1,float *src2,float *res){
  __m128 prev = _mm_load_ps(src1);
  __m128 post = _mm_load_ps(src2);
  __m128 sum = _mm_add_ps(prev,post);
  _mm_store_ps(res,sum);
}

int main(void){
  float in1[4] = {1.2f,3.5f,1.7f,2.8f};
  float in2[4] = {-0.7f,2.6f,3.3f,-0.8f};
  float naive_output[4],sse_output[4];

  naive_sum(in1,in2,naive_output,4);
  sse_sum(in1,in2,sse_output);

  for(int i=0;i<4;i++){
    printf("%f\t",naive_output[i]);
  }
  printf("\n");
  for(int i=0;i<4;i++){
    printf("%f\t",sse_output[i]);
  }
  printf("\n");

}
