#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define NAMESIZE 128

struct data
{
    int id;
    char name[NAMESIZE];
    int score;
};

void print(const void *data)
{
    struct data listData = *((struct data *)data);
    printf("id: %d\tname: %s\tscore: %d\n",
           listData.id, listData.name, listData.score);
}

int main()
{
    int i = 1;
    listNode *list = NULL;
    struct data data;

    for (; i < 6; i++)
    {
        data.id = i;
        snprintf(data.name, NAMESIZE, "stu%d", i);
        data.score = rand() % 100;
        listInsert(&list, &data, sizeof(struct data), INSERTTAIL);
    }

    listTravel(list, print);

    listDestory(list);

    return 0;
}
