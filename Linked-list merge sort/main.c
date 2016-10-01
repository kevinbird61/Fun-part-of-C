#include <stdio.h>
#include <stdlib.h>

typedef struct __LIST{
  int value;
  struct __LIST *next;
}list;

list *cut_sort(list *each_head);
list *mergesort(list *left,list *right);
list *llconcat(list *front,list *back);
list *cut(list *orig,int cutSize);
int llsize(list *head);
list *append(list *head,int new);
void print_list(list *p_head);

int main(void){
  list *head = NULL;
  // Append list (Test here)
  for(int i=0;i<11;i++){
    head = append(head,11-i);
  }
  // First view
  print_list(head);
  // Split up and sort
  if(llsize(head)>=2)
    head = cut_sort(head);
  // View result
  print_list(head);
}

list *cut_sort(list *each_head){
  // Find size
  list *right,*left;
  right = cut(each_head,llsize(each_head)/2);
  left = each_head;
  if(llsize(right)>1)
    right = cut_sort(right);
  if(llsize(left)>1)
    left = cut_sort(left);

  // merge it
  return mergesort(left,right);
}

list *mergesort(list *left,list *right){
  list *merge = NULL;
  while(llsize(left) && llsize(right)){
    if(left->value >= right->value){
      merge = append(merge,right->value);
      right = right->next;
    }
    else{
      merge = append(merge,left->value);
      left = left->next;
    }
  }
  // One side if empty
  return (llsize(left)==0 ? llconcat(merge,right) : llconcat(merge,left));
}

list *llconcat(list *front,list *back){
  list *temp = NULL;
  while(front != NULL){
    temp = append(temp,front->value);
    front = front->next;
  }
  while(back != NULL){
    temp = append(temp,back->value);
    back=back->next;
  }
  return temp;
}

list *cut(list *orig,int cutSize){
  for(int i=0;i<cutSize-1;i++)
    orig = orig->next;
  list *new_head = orig->next;
  orig->next = NULL;
  return new_head;
}

int llsize(list *head){
  int i = 0;
  while(head != NULL && ++i)
    head = head->next;
  return i;
}

list *append(list *head,int new){
  list *new_node,*real_head,*travel;
  if( (new_node = (list *)malloc(sizeof(list))) == NULL){
    fprintf(stderr,"Memory can't allocate!\n");
    exit(1);
  }
  if(head == NULL){
    real_head = new_node;
  }
  else{
    real_head = head;
    travel = head;
    while(travel->next!=NULL)
      travel = travel->next;
    travel->next = new_node;
  }
  new_node->value = new;
  new_node->next = NULL;
  return real_head;
}

void print_list(list *p_head){
  while (p_head != NULL) {
    printf("Value in list: %d\n",p_head->value);
    p_head = p_head->next;
  }
}
