#include <stdio.h>
#include <stdlib.h>

#define FINAL 10

int rec_loop(int i){
  if(i == 10) return 0;
  else{
    for(int k=0;k<i || rec_loop(i+1) ;k++){
      printf("This is in %d\n",i);
    }
  }
}

int main(void){
  rec_loop(1);
}
