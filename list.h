#ifndef LIST_H__
#define LIST_H__

typedef struct ListNode
{
    struct ListNode *prev;
    struct ListNode *next;
    void *data;
} listNode;

#define INSERTHEAD 1 // 头部插入
#define INSERTTAIL 2 // 尾部插入

typedef void listOper(const void *);

int listInsert(listNode **, const void *, int, int);

int listDetele(listNode *, void *);

int listSearch(listNode *, void *);

int listChange(listNode *, void *, void *);

int listSort(listNode *);

int listTravel(listNode *, listOper *); // 指向函数入口地址的指针

int listDestory(listNode *);

#endif
