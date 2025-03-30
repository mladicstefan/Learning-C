/* linked-list.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_book{
  char title[64];
  int pages;
  struct s_book *next;
};
typedef struct s_book Book;

Book *first;
int numBooks;

void addbook(char *title, int pages)
{
  Book *p, *new;
  if (!first){
    p = malloc(sizeof(Book));
    memset(p,0,sizeof(Book));
    numBooks++;
    strncpy(p->title,title,63);
    p ->pages = pages;
    p-> next = 0;
    first = p;
    
  }

  for (p=first; p->next; p++);
  new = malloc(sizeof(Book));
  memset (new,0,sizeof(Book));
  numBooks++;
  strncpy(new->title,title,63);
  new -> pages = pages;
  new -> next = 0;

  p->next = new;

}

int main()
{
  first = 0;
  numBooks = 0;

  addbook("Old Testament", 3500);
  printf("%s\n", first->title);
  printf("%d\n", first->pages);
  addbook("New Testament", 350);
  printf("%s\n", first->next->title);
}
