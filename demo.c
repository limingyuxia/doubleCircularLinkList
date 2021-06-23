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

// 打印节点中的数据
static int print(const void *data)
{
    const struct data *listData = data;
    printf("id: %d\tname: %s\tscore: %d\n",
           listData->id, listData->name, listData->score);

    return 0;
}

// 根据id查找节点
static int idCompare(const void *key, const void *data)
{
    const int *id = key;
    const struct data *listData = data;

    // 相同为1，不同为0
    return (*id == listData->id);
}

// 修改节点中的数据
static int dataModify(void *oldData, const void *newData)
{
    struct data *listOldData = oldData;
    const struct data *listNewData = newData;

    strncpy(listOldData->name, listNewData->name, NAMESIZE);
    listOldData->score = listNewData->score;

    return 0;
}

// 按节点数据域中的score字段，降序排列链表
static int scoreSort(const void *data1, const void *data2)
{
    const struct data *listData1 = data1;
    const struct data *listData2 = data2;

    if (listData1->score > listData2->score)
    {
        return 0;
    }

    return 1;
}

int main()
{
    int i = 1;
    listNode *list = NULL;
    struct data data;

    // 初始化链表
    for (; i < 10; i++)
    {
        data.id = i;
        snprintf(data.name, NAMESIZE, "stu%d", i);
        data.score = rand() % 100;
        listInsert(&list, &data, sizeof(struct data), INSERTTAIL);
    }

    listTravel(list, print);

    int key = 3;        // 要查找的节点索引
    listNode *findNode; // 查找的节点
    if (listSearch(list, &key, idCompare, &findNode) == 0)
    {
        const struct data *nodeData = findNode->data;
        printf("\n");
        print(nodeData);
    }

    // 删除id为3的节点
    listDetele(list, &key, idCompare);
    printf("\n");
    listTravel(list, print);

    // 修改节点为4节点的数据
    key = 4;
    struct data newData = {0, "test", 100};
    listChange(list, &key, idCompare, dataModify, &newData);
    printf("\n");
    listTravel(list, print);

    // 按成绩降序排列链表
    listSort(list, scoreSort);
    printf("\n");
    listTravel(list, print);

    // 销毁链表，释放内存
    listDestory(list);

    return 0;
}
