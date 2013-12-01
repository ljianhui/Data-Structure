#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node
{
    //循环双链表的结点结构
    DataType data;
    struct node *next;
    struct node *last;
};

Node* Position(List *list, int index);
void LinkNodeToList(List *list, Node *node, Node *next_node);
int RemoveNode(List *list, Node *node);

int InitList(List *list, void (*InitData)(DataType*))
{
    //初始化链表,元素的初始化方式由InitData函数给出
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
        return -1;

    InitData(&node->data);
    node->next = node;
    node->last = node;

    list->head = node;
    list->length = 0;
    return 0;
}

Iterator Append(List *list, DataType *data)
{
    //把data的内容插入到链表list的末尾
    return Insert(list, data, End(list));
}

//把node连接到next_node之前
void LinkNodeToList(List *list, Node *node, Node *next_node)
{
    Node *last_node = next_node->last;

    last_node->next = node;
    node->next = next_node;

    next_node->last = node;
    node->last = last_node;

    ++list->length;
}
//从list中，移除node结点，但并不free
int RemoveNode(List *list, Node *node)
{
    //注意，并不free结点，只是把结点从链中分离
    if(node == list->head)
        return -1;
    Node *next_node = node->next;
    Node *last_node = node->last;

    next_node->last = last_node;
    last_node->next = next_node;

    --list->length;
    return 0;
}

Node* Position(List *list, int index)
{
    Node *node = NULL;
    int i = 0;
    if(index <= list->length/2)
    {
        node = list->head->next;
        for(i = 0; i < index; ++i)
        {
            node = node->next;
        }
    }
    else
    {
        node = list->head;
        for(i = list->length; i > index; --i)
        {
            node = node->last;
        }
    }
    return node;
}

Iterator Insert(List *list, DataType *data, Iterator it_before)
{
    //把data的内容插入到链表的迭代器it_before的前面
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
    {
        it_before.addr = list->head;
        return it_before;
    }
    node->data = *data;
    node->next = NULL;
    node->last = NULL;

    Node *next_node = it_before.addr;
    LinkNodeToList(list, node, next_node);
    it_before.addr = node;
    return it_before;
}

Iterator MoveFromAtoB(List *A, Iterator it_a,
                      List *B, Iterator it_b_before)
{
    //把链表A中迭代器it_a指向的结点移动到链表B中迭代器it_b_befroe的前面
    Node *node_a = it_a.addr;
    Node *node_b = it_b_before.addr;

    RemoveNode(A, it_a.addr);
    LinkNodeToList(B, node_a, node_b);
    it_b_before.addr = node_a;
    return it_b_before;
}

int Remove(List *list, Iterator it)
{
    //删除链表list中迭代器it指向的结点
    Node *node = it.addr;
    int n = RemoveNode(list, node);
    if(n != -1)
        free(node);
    return n;
}

int RemoveFirst(List *list)
{
    //删除链表list的第0个结点，下标从0开始
    return Remove(list, Begin(list));
}

int RemoveLast(List *list)
{
    //删除链表list的最后一个结点
    return Remove(list, End(list));
}

DataType* At(List *list, int index)
{
    //返回list中第index个数据的指针
    Node *node = Position(list, index);
    if(node != list->head)
        return &(node->data);
    return NULL;
}

Iterator FindFirst(Iterator begin, Iterator end, DataType *data,
                       int (*condition)(const DataType*, const DataType*))
{
    //在begin和end之间查找符合condition的第一个元素，
    //比较函数由condition指向,比较的值由data指向
    //当第一个参数的值小于第二个参数的值时，返回1，否则返回0
    //根据condition函数的不同，可以查找第一个相等、大于或小于data的值
    while(!IsEqual(begin, end))
    {
        if(condition(GetData(begin), data))
        {
            break;
        }
        Next(&begin);
    }
    return begin;
}

int IndexOf(List *list, DataType *data,
            int (*equal)(const DataType*,const DataType*))
{
    //查找list中第一个与data相等的元素的下标，
    //equal函数，当第一个参数与第二个参数的值相等时，返回1，否则返回0
    Node *node = list->head->next;
    int i = 0;
    while(node != list->head)
    {
        if(equal(data,&node->data))
            return i;
        ++i;
        node = node->next;
    }
    return -1;
}

Iterator GetMin(Iterator begin, Iterator end,
                int (*less)(const DataType*, const DataType*))
{
    //查找在begin和end之间的最小值，比较函数由less指向
    //当第一个参数的值小于第二个参数的值时，返回1，否则返回0
    Iterator min = begin;
    Next(&begin);
    while(!IsEqual(begin, end))
    {
        if(less(GetData(begin), GetData(min)))
            min = begin;
        Next(&begin);
    }
    return min;
}

Iterator GetMax(Iterator begin, Iterator end,
                int (*large)(const DataType*, const DataType*))

{
    //查找在begin和end之间的最大值，比较函数由large指向
    //当第一个参数的值大于第二个参数的值时，返回1，否则返回0
    Iterator max = begin;
    Next(&begin);
    while(!IsEqual(begin, end))
    {
        if( large(GetData(begin), GetData(max)) )
            max = begin;
        Next(&begin);
    }
    return max;
}

int GetLength(List *list)
{
    //获取list的长度
    return list->length;
}

int IsEmpty(List *list)
{
    //若list为空链表，则返回1，否则返回0
    return !(list->length);
}

void DestoryList(List *list)
{
    //销毁list
    Node *node = list->head;
    Node *end = list->head->last;
    Node *tmp = NULL;
    while(node != end)
    {
        tmp = node->next;
        free(node);
        node = tmp;
    }
    free(end);
    list->head = NULL;
    list->length = 0;
}

Iterator Begin(List *list)
{
    //获得list的首迭代器
    Iterator it;
    it.addr = list->head->next;
    return it;
}

Iterator End(List *list)
{
    //获得list的尾迭代器，指向最后一个元素的下一个位置
    Iterator it;
    it.addr = list->head;
    return it;
}

Iterator Next(Iterator *it)
{
    //使it指向下一个位置，并返回指向下一个位置后的迭代器
    it->addr = it->addr->next;
    return *it;
}

Iterator Last(Iterator *it)
{
    //使it指向上一个位置，并返回指向上一个位置后的迭代器
    it->addr = it->addr->last;
    return *it;
}

DataType* GetData(Iterator it)
{
    //通过迭代器it获得数据，相当于*p
    return &(it.addr->data);
}

int IsEqual(Iterator it_a, Iterator it_b)
{
    //判断两个迭代器是否相等，是返回1，否返回0
    if(it_a.addr == it_b.addr)
        return 1;
    return 0;
}
