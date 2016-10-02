#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
static double diff_in_second(struct timespec t1, struct timespec t2);

int main(void){
  list *head = NULL;
  struct timespec start, end;
  // Append list (Test here)
  srand(time(NULL));
  for(int i=0;i<10000;i++){
    head = append(head,rand()%100);
  }
  // First view
  print_list(head);
  // Split up and sort
  clock_gettime(CLOCK_REALTIME, &start);
  if(llsize(head)>=2)
    head = cut_sort(head);
  clock_gettime(CLOCK_REALTIME, &end);
  // View result
  print_list(head);

  printf("Total time is %lf\n",diff_in_second(start, end));
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
  printf("\n");
}

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}
