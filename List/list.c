#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node
{
    DataType data;
    struct node *next;
    struct node *last;
};

Node* Position(List *list, int index);
void LinkNodeToList(List *list, Node *node, Node *next_node);
int RemoveNode(List *list, Node *node);

int InitList(List *list, void (*InitData)(DataType*))
{
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
    Node *node = (Node*)malloc(sizeof(Node));
    Iterator it;
    it.addr = node;
    if(node == NULL)
        return it;
    node->data = *data;
    node->next = NULL;
    node->last = NULL;

    LinkNodeToList(list, node, list->head);
    return it;
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
    Node *node_a = it_a.addr;
    Node *node_b = it_b_before.addr;

    RemoveNode(A, it_a.addr);
    LinkNodeToList(B, node_a, node_b);
    it_b_before.addr = node_a;
    return it_b_before;
}

int Remove(List *list, Iterator it)
{
    Node *node = it.addr;
    int n = RemoveNode(list, node);
    if(n != -1)
        free(node);
    return n;
}

int RemoveFirst(List *list)
{
    return Remove(list, Begin(list));
}

int RemoveLast(List *list)
{
    Node *node = list->head->last;
    int n = RemoveNode(list, node);
    if(n != -1)
        free(node);
    return n;
}

DataType* At(List *list, int index)
{
    Node *node = Position(list, index);
    if(node != list->head)
        return &(node->data);
    return NULL;
}

Iterator Find(List *list, int(*condition)(const DataType*))
{
    Node *node = list->head->next;
    Iterator it;
    it.addr = list->head;
    while(node != list->head)
    {
        if(condition(node))
        {
            it.addr = node;
            break;
        }
        node = node->next;
    }
    return it;
}
Iterator FindFirstEqual(List *list, DataType *data,
                        int (*equal)(const DataType*,const DataType*))
{
    Node *node = list->head->next;
    Iterator it;
    it.addr = list->head;

    while(node != list->head)
    {
        if(equal(data, &node->data))
        {
            it.addr = node;
            break;
        }
        node = node->next;
    }
    return it;
}
int IndexOf(List *list, DataType *data,
            int (*equal)(const DataType*,const DataType*))
{
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

Iterator GetMin(List *list, int (*less)(const DataType*, const DataType*))
{
    Node *min = list->head->next;
    Iterator it;
    it.addr = min;
    if(min == list->head)
        return it;

    Node *node = min->next;
    while(node != list->head)
    {
        if(less(&node->data, &min->data))
            min = node;
        node = node->next;
    }
    it.addr = min;
    return it;
}

Iterator GetMax(List *list, int (*large)(const DataType*, const DataType*))
{
    Node *max = list->head->next;
    Iterator it;
    it.addr = max;
    if(max == list->head)
        return it;

    Node *node = max->next;
    while(node != list->head)
    {
        if(large(&node->data, &max->data))
            max = node;
        node = node->next;
    }
    it.addr = max;
    return it;
}

int GetLength(List *list)
{
    return list->length;
}

int IsEmpty(List *list)
{
    return !(list->length);
}

void DestoryList(List *list)
{
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
    Iterator it;
    it.addr = list->head->next;
    return it;
}

Iterator End(List *list)
{
    Iterator it;
    it.addr = list->head;
    return it;
}

Iterator Next(Iterator *it)
{
    it->addr = it->addr->next;
    return *it;
}

Iterator Last(Iterator *it)
{
    it->addr = it->addr->last;
    return *it;
}

DataType* GetData(Iterator it)
{
    return &(it.addr->data);
}

int IsEqual(Iterator it_a, Iterator it_b)
{
    if(it_a.addr == it_b.addr)
        return 1;
    return 0;
}
