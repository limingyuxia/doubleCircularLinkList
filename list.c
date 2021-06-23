#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int listInsert(listNode **list, const void *data, int size, int mode)
{
    if (NULL == data)
    {
        return -1;
    }

    // 链表为空
    if (NULL == *list)
    {
        listNode *firstNode;

        firstNode = malloc(sizeof(listNode));
        if (NULL == firstNode)
        {
            perror("malloc: ");
            return -2;
        }
        firstNode->data = malloc(size);
        if (NULL == firstNode)
        {
            perror("malloc: ");
            return -2;
        }

        firstNode->prev = firstNode;
        firstNode->next = firstNode;
        if (NULL == memcpy(firstNode->data, data, size))
        {
            perror("memcpy: ");
            return -3;
        }

        *list = firstNode;
    }
    else
    {
        listNode *newNode;

        newNode = malloc(sizeof(listNode) + size);
        if (NULL == newNode)
        {
            perror("malloc: ");
            return -2;
        }
        if (NULL == (newNode->data = malloc(size)))
        {
            perror("malloc: ");
            return -2;
        }

        if (mode == INSERTHEAD)
        {
            newNode->prev = (*list);
            newNode->next = (*list)->next;
        }
        else if (mode == INSERTTAIL)
        {
            newNode->next = (*list);
            newNode->prev = (*list)->prev;
        }
        else
        {
            return -4;
        }
        newNode->prev->next = newNode;
        newNode->next->prev = newNode;
        if (NULL == memcpy(newNode->data, data, size))
        {
            perror("memcpy: ");
            return -3;
        }
    }

    return 0;
}

static void *findNode(listNode *list, const void *key, listCmp *cmp)
{
    listNode *ptr = list->prev;

    do
    {
        ptr = ptr->next;
        if (cmp(key, ptr->data) != 0)
        {
            return ptr;
        }
    } while (ptr->next != list);

    return NULL;
}

int listSearch(listNode *list, const void *key, listCmp *cmp, listNode **data)
{
    if (NULL == list)
    {
        return -1;
    }

    listNode *node;
    node = findNode(list, key, cmp);
    if (node != NULL)
    {
        *data = node;
        return 0;
    }

    return -2;
}

int listDetele(listNode *list, const void *key, listCmp *cmp)
{
    listNode *node;
    node = findNode(list, key, cmp);
    if (NULL != node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
        free(node->data);
    }

    return 0;
}

int listSort(listNode *list)
{

    return 0;
}

int listChange(listNode *list, void *key, void *newdata)
{
    return 0;
}

int listTravel(listNode *list, listOper *oper)
{
    if (NULL == list)
    {
        printf("empty list\n");
        return 0;
    }

    listNode *ptr = list->prev;

    // 遍历到最后一个节点结束
    do
    {
        ptr = ptr->next;
        oper(ptr->data);
    } while (ptr->next != list);

    return 0;
}

int listDestory(listNode *list)
{
    listNode *ptr, *cur;

    for (cur = list; cur->next != list; cur = ptr)
    {
        ptr = cur->next;

        free(cur);
        free(cur->data);
    }
    free(cur);
    free(cur->data);

    return 0;
}
