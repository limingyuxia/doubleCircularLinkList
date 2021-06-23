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
    if (NULL == list)
    {
        return -1;
    }

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

int listSort(listNode *list, listOrd *ord)
{
    if (NULL == list)
    {
        return -1;
    }

    listNode *ptr1 = list->prev;
    listNode *ptr2 = list;
    listNode *swap;

    // 时间复杂度很高的冒泡排序
    do
    {
        ptr1 = ptr1->next;
        do
        {
            ptr2 = ptr2->next;
            if (ord(ptr1->data, ptr2->data) == 0)
            {
                swap->data = ptr1->data;
                ptr1->data = ptr2->data;
                ptr2->data = swap->data;
            }
        } while (ptr2->next != list);
    } while (ptr1->next != list);

    return 0;
}

int listChange(listNode *list, const void *key, listCmp *cmp,
               listMod *mod, const void *newData)
{
    if (NULL == list)
    {
        return -1;
    }

    listNode *node;
    node = findNode(list, key, cmp);
    if (NULL != node)
    {
        if (mod(node->data, newData) == 0)
        {
            return 0;
        }
    }

    return -1;
}

int listTravel(listNode *list, listOper *oper)
{
    if (NULL == list)
    {
        return -1;
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
