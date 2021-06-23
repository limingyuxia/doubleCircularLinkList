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

typedef int listOper(const void *);

typedef int listCmp(const void *, const void *);

typedef int listMod(void *, const void *);

// 创建链表
int listInsert(listNode **, const void *, int, int);

// 查找链表中的节点
int listSearch(listNode *, const void *, listCmp *, listNode **);

// 删除链表中的节点
int listDetele(listNode *, const void *, listCmp *);

// 修改链表中的节点
int listChange(listNode *, const void *, listCmp *, listMod *, const void *);

// 链表排序
int listSort(listNode *);

// 遍历链表
int listTravel(listNode *, listOper *); // 指向函数入口地址的指针

// 销毁链表
int listDestory(listNode *);

#endif
