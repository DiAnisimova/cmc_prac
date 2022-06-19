#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int info;
    struct list *next;
    struct list *prev;
}list;

list *add_element(list *phead, list *end, int elem)
{
    if (!phead)
      {
        phead = malloc(sizeof(list));
        phead->info = elem;
        phead->prev = NULL;
        phead->next = NULL;
        return phead;
      }
    end->next = malloc(sizeof(list));
    end->next->info = elem;
    end->next->prev = end;
    end->next->next = NULL;
    return phead;
}

list *change(list *phead, list **end, list *pos_b, list *pos_c)
{
    if (pos_b == phead)
      {
        return phead;
      }
    printf("NOT ERROR\n");
    if (pos_c == *end)
      {
        *end = pos_b->prev;
        pos_c->next = phead;
        phead->prev = pos_c;
        pos_b->prev->next = NULL;
        pos_b->prev = NULL;
        phead = pos_b;
        return phead;
      }
    pos_b->prev->next = pos_c->next;
    pos_c->next->prev = pos_b->prev;
    pos_c->next = phead;
    phead->prev = pos_c;
    pos_b->prev = NULL;
    phead = pos_b;
    return phead;
}

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    int n, m;
    fscanf(f, "%d%d", &n, &m);
    list **pos = malloc(n * sizeof(list));
    list *phead = NULL;
    list *end = NULL;
    for (int i = 0; i < n; i++)
      {
        phead = add_element(phead, end, i + 1);
        if (!end)
          {
            end = phead;
          }
        else
          {
            end = end->next;
          }
        pos[i] = end;
      }
    int b;
    int c;
    for (int i = 0; i < m; i++)
      {
        fscanf(f, "%d%d", &b, &c);
        list *pos_b = pos[b - 1];
        list *pos_c = pos[c - 1];
        phead = change(phead, &end, pos_b, pos_c);
      }
    fclose(f);
    FILE *f1 = fopen("output.txt", "w");
    while (phead->next != NULL)
      {
        fprintf(f1, "%d ", phead->info);
        list *ph = phead;
        phead = phead->next;
        free(ph);
      }
    fprintf(f1, "%d", phead->info);
    free(phead);
    free(pos);
    fclose(f1);
    return 0;
}

