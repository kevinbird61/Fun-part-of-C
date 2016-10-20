#include <stdio.h>
#include <stdlib.h>

struct _rect{
  int x,y;
  int (**prototype)(struct _rect *); // Where prototype now?
};

typedef struct _rect Rect;

typedef int (*Rect_method)(Rect *); /* Denote: method enumeration */

enum{ GET_X, GET_Y, END_OF_NAME_TABLE }; /* Denote: name table */

Rect_method *rect_prototype; /* Denote: method as an array of prototypes */

// Constructor & destructor
Rect *rect_new(int x,int y)
{
  Rect *p = (Rect *)malloc(sizeof(Rect));
  p->x = x;
  p->y = y;
  p->prototype = rect_prototype;
  return p;
}

void rect_delete(Rect *p) { free(p); }

// Methods: getter
int rect_get_x(Rect *p){ return p->x;}
int rect_get_y(Rect *p){ return p->y;}

// Register prototype
void rect_init_prototype(void)
{
  rect_prototype = (Rect_method *)malloc((sizeof(Rect_method))*END_OF_NAME_TABLE);
  rect_prototype[GET_X] = rect_get_x;
  rect_prototype[GET_Y] = rect_get_y;
}

// deregister prototype
void rect_delete_prototype(void) { free(rect_prototype);}

static void test_suite(void)
{
  Rect *r1 = rect_new(1,2);
  Rect *r2 = rect_new(3,4);
  printf("r1=(%d,%d),r2=(%d,%d)\n",
          r1->prototype[GET_X](r1),r1->prototype[GET_Y](r1),
          r2->prototype[GET_X](r2),r2->prototype[GET_Y](r2));
  rect_delete(r1);
  rect_delete(r2);
}

int main(void)
{
  rect_init_prototype();
  test_suite();
  rect_delete_prototype();
  return 0;
}
