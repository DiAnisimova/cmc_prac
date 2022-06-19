#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    unsigned info;
    struct list *next;
}list;

list *add_element(list *phead, unsigned elem)
{
    if (!phead)
      {
        phead = malloc(sizeof(list));
        phead->info = elem;
        phead->next = NULL;
        return phead;
      }
    list *ph = phead;
    while (ph->next != NULL)
      {
        ph = ph->next;
      }
    ph->next = malloc(sizeof(list));
    ph->next->info = elem;
    ph->next->next = NULL;
    return phead;
}

list *equals(list *phead, unsigned x)
{
    list *ph = phead;
    while(ph->info != x && ph->next != NULL)
      {
        ph = ph->next;
      }
    if (ph->info == x)
      {
        return ph;
      }
    return NULL;
}

int main(void)
{
    list *phead = NULL;
    FILE *f = fopen("input.txt", "r");
    unsigned x;
    fscanf(f, "%u", &x);
    while (x != -1)
      {
        phead = add_element(phead, x);
        fscanf(f, "%u", &x);
      }
    fscanf(f, "%u", &x);
    while (x != -1)
      {
        list *t = equals(phead, x);
        while (t != NULL)
          {
            if (t != NULL)
              {
                t->info = -1;
              }
            t = equals(phead, x);
          }
        fscanf(f, "%u", &x);
      }
    fclose(f);
    FILE *f1 = fopen("output.txt", "w");
    while (phead->next != NULL)
      {
        if (phead->info != -1)
          {
            fprintf(f1, "%u ", phead->info);
          }
        list *t = phead;
        phead = phead->next;
        free(t);
      }
    if (phead->info != -1)
      {
        fprintf(f1, "%u", phead->info);
      }
    free(phead);
    fclose(f1);
    return 0;
}
