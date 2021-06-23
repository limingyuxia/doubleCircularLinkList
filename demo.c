#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define NAMESIZE 128

struct data
{
    int id;
    char name[NAMESIZE];
    int score;
};

// 函数只在内部使用
static int print(const void *data)
{
    const struct data *listData = data;
    printf("id: %d\tname: %s\tscore: %d\n",
           listData->id, listData->name, listData->score);

    return 0;
}

static int id_compare(const void *key, const void *data)
{
    const int *id = key;
    const struct data *listData = data;

    // 相同为1，不同为0
    return (*id == listData->id);
}

static int data_modify(void *oldData, const void *newData)
{
    struct data *listOldData = oldData;
    const struct data *listNewData = newData;

    strncpy(listOldData->name, listNewData->name, NAMESIZE);
    listOldData->score = listNewData->score;

    return 0;
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

    int key = 3;        // 要查找的节点索引
    listNode *findNode; // 查找的节点
    if (listSearch(list, &key, id_compare, &findNode) == 0)
    {
        const struct data *nodeData = findNode->data;
        printf("\n");
        print(nodeData);
    }

    listDetele(list, &key, id_compare);
    printf("\n");
    listTravel(list, print);

    key = 4;
    struct data newData = {0, "test", 100};
    listChange(list, &key, id_compare, data_modify, &newData);
    printf("\n");
    listTravel(list, print);

    listDestory(list);

    return 0;
}
