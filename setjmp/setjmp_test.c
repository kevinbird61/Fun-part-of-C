#include <stdio.h>
#include <setjmp.h>

jmp_buf bufferA,bufferB;

void routineA();
void routineB();

void routineA(){
  int r;
  printf("A(1)\n");

  r = setjmp(bufferA);
  if(r == 0) routineB();

  printf("A(2) r = %d\n",r);

  r = setjmp(bufferA);
  if(r == 0) longjmp(bufferB,20001);

  printf("A(3) r = %d\n",r);

  r = setjmp(bufferA);
  if(r == 0) longjmp(bufferB,20002);

  printf("A(4) r = %d\n",r);
}

void routineB()
{
    int r;

    printf("B(1)\n");

    r = setjmp(bufferB);
    if (r == 0) longjmp(bufferA, 10001);

    printf("B(2) r=%d\n", r);

    r = setjmp(bufferB);
    if (r == 0) longjmp(bufferA, 10002);

    printf("B(3) r=%d\n", r);

    r = setjmp(bufferB);
    if (r == 0) longjmp(bufferA, 10003);
}


int main(int argc, char **argv)
{
    routineA();
    return 0;
}
