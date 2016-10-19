#include <stdio.h>

int add(int a,int b){
  return a+b;
}

int mult(int a,int b){
  return a*b;
}

int main(void){
  int (*op)(int a,int b);
  op = add; // assign function add to op
  printf("add-op(3,5)=%d\n",op(3,5));
  op = mult;
  printf("mult-op(3,5)=%d\n",op(3,5));
}
