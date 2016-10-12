#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_char(char *a,char *b){
  printf("a: %d , b: %d\n",a,b);
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

void recurse_reverse(char *head,char *tail){
  if(head >= tail) return;
  swap_char(head,tail);
  recurse_reverse(head+=sizeof(char),tail-=sizeof(char));
}

int main(void){
  char *str = malloc(1*sizeof(char));
  scanf("%s",str);
  recurse_reverse(str,(str+strlen(str)-1));
  printf("%s , %d\n",str,(int)strlen(str));
}
