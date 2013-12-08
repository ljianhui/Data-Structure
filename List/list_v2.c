#include <stdio.h>
#include <stdlib.h>
#include "list_v2.h"

typedef struct node
{
    //循环双链表的结点结构
    void* data;//数据域指针
    struct node *next;//指向当前结点的下一结点
    struct node *last;//指向当前结点的上一结点
}Node;

struct list
{
    struct node *head;//头指针，指向头结点
    int data_size;//链表对应的数据所占内存的大小
    int length;//链表list的长度
};

Node* Position(List list, int index);
Node* NewNode(int data_size);
void LinkNodeToList(List list, Node *node, Node *next_node);
int RemoveNode(List list, Node *node);

int InitList(List *list_ptr, int data_size)
{
    /***
    函数功能：初始化链表,数据域所占内存的大小由data_size给出
    ***/

    List new_list = (List)malloc(sizeof(struct list));
    *list_ptr = new_list;
    if(new_list == NULL)
        return -1;

    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
    {
        free(new_list);
        *list_ptr = NULL;
        return -1;
    }
    //把头结点的数据域指针置为空
    node->data = NULL;
    //使其指针指向自身
    node->next = node;
    node->last = node;
    //设置list的头指针、数据所占内存的大小和长度
    (*list_ptr)->head = node;
    (*list_ptr)->data_size = data_size;
    (*list_ptr)->length = 0;
    return 0;
}

Iterator Append(List list, void *data,
                void (*assign)(void*, const void*))
{
    /***
    函数功能：把data的内容插入到链表list的末尾
        assign指定数据data间的赋值方法
    ***/

    //调用Insert函数实现，插入位置为end
    return Insert(list, data, End(list), assign);
}

void LinkNodeToList(List list, Node *node, Node *next_node)
{
    /***
    函数功能：把node连接到next_node之前
    ***/
    Node *last_node = next_node->last;
    //把node连接入list中
    //设置相关的结点的next指针
    last_node->next = node;
    node->next = next_node;
    //设置相关结点的last指针
    next_node->last = node;
    node->last = last_node;
    //把node的值连入list后，list的长度加1
    ++list->length;
}

int RemoveNode(List list, Node *node)
{
    /***
    函数功能：从list中，移除node结点，但并不free
        注意，并不free结点，只是把结点从链中分离
    ***/
    if(node == list->head)
        return -1;//不移除头结点
    Node *next_node = node->next;
    Node *last_node = node->last;
    //使结点node从list中分离
    next_node->last = last_node;
    last_node->next = next_node;
    //分享后，list的长度减1
    --list->length;
    return 0;
}

Node* Position(List list, int index)
{
    /***
    函数功能：返回第index个结点的指针
    ***/
    Node *node = NULL;
    int i = 0;
    //如果index比长度的一半小，则从前往后找
    if(index <= list->length/2)
    {
        //设置node初值
        node = list->head->next;
        for(i = 0; i < index; ++i)
        {
            node = node->next;//向后移一个结点
        }
    }
    //否则从后往前找
    else
    {
        node = list->head;//设置node初值
        for(i = list->length; i > index; --i)
        {
            node = node->last;//向前移一个结点
        }
    }
    return node;
}

Node* NewNode(int data_size)
{
    /***
    函数功能：新建一个结点，并返回结点的指针，
        结点由两部分组成，一部分是结点本身，
        一部分为data指针指向的数据域空间
        数据所占的内存空间由参数data_size给出
    ***/

    //创建结点，若创建失败，返回NULL
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
        return NULL;
    //创建数据域，若创建失败，返回NULL
    void *data = malloc(data_size);
    if(data == NULL)
    {
        free(node);
        return NULL;
    }
    //使结点的数据域指针指向数据域空间，并返回结点的指针
    node->data = data;
    return node;
}

Iterator Insert(List list, void *data, Iterator it_before,
                void (*assign)(void*, const void*))
{
    /***
    函数功能：把data的内容插入到链表list的迭代器it_before的前面
        assign指定数据data间的赋值方法
    ***/

    //从内存中开辟一个结点的空间
    Node *node = NewNode(list->data_size);
    if(node == NULL)
    {
        //若申请内存失败，则返回尾迭代器
        it_before = list->head;
        return it_before;
    }
    //设置结点的值
    assign(node->data, data);
    node->next = NULL;
    node->last = NULL;
    //把结点连入链表中
    LinkNodeToList(list, node, it_before);
    //返回连篇链表的结点的迭代器
    return node;
}

Iterator MoveFromAtoB(List A, Iterator it_a,
                      List B, Iterator it_b_before)
{
    /***
    函数功能：把链表A中迭代器it_a指向的结点移动到
              链表B中迭代器it_b_befroe的前面
    ***/

    //把结点a从A链中分享
    RemoveNode(A, it_a);
    //把结点a连接入B链中的结点b的前面
    LinkNodeToList(B, it_a, it_b_before);
    //返回连入链B的结点的指针
    return it_a;
}

int Remove(List list, Iterator it)
{
    /***
    函数功能：删除链表list中迭代器it指向的结点
    ***/

    //把结点it从list中分离
    int n = RemoveNode(list, it);
    if(n != -1)
    {
        free(it->data);
        free(it);//free掉node结点
    }
    return n;
}

int RemoveFirst(List list)
{
    /***
    函数功能：删除链表list的第0个结点，下标从0开始
    ***/
    return Remove(list, Begin(list));
}

int RemoveLast(List list)
{
    /***
    函数功能：删除链表list的最后一个结点
    ***/
    return Remove(list, End(list));
}

void* At(List list, int index)
{
    /***
    函数功能：返回list中第index个数据的指针
    ***/

    //获得第index个结点的指针
    Node *node = Position(list, index);
    if(node != list->head)
        return node->data;//返回数据域的指针
    return NULL;//若为头结点，则返回NULL
}

Iterator FindFirst(Iterator begin, Iterator end, void *data,
                       int (*condition)(const void*, const void*))
{
    /***
    函数功能：在begin和end之间查找符合condition的第一个元素，
      比较函数由condition指向,比较的值由data指向
      当第一个参数的值小于第二个参数的值时，返回1，否则返回0
      根据condition函数的不同，可以查找第一个相等、大于或小于data的值
    ***/
    while(begin != end)
    {
        //从开始到结束搜索
        if(condition(GetData(begin), data))
        {
            //找到符合数据的元素，退出循环
            break;
        }
        Next(&begin);
    }
    return begin;
}

int IndexOf(List list, void *data,
            int (*equal)(const void*,const void*))
{
    /***
    函数功能：查找list中第一个与data相等的元素的下标，
        equal函数，当第一个参数与第二个参数的值相等时，返回1，否则返回0
    ***/
    Node *node = list->head->next;//指向第0个结点
    int i = 0;
    while(node != list->head)
    {
        //从链表头到链表尾查找，若相等，则返回
        if(equal(data, node->data))
            return i;
        ++i;
        node = node->next;
    }
    //没有找到则返回-1
    return -1;
}

Iterator GetMin(Iterator begin, Iterator end,
                int (*less)(const void*, const void*))
{
    /***
    函数功能：查找在begin和end之间的最小值，比较函数由less指向
        当第一个参数的值小于第二个参数的值时，返回1，否则返回0
    ***/
    Iterator min = begin; //用于记录最小的元素的迭代器
    Next(&begin);
    while(begin != end)
    {
        //找到更小的元素，让min指向更小的元素
        if(less(GetData(begin), GetData(min)))
            min = begin;
        Next(&begin);
    }
    //返回最小的元素
    return min;
}

Iterator GetMax(Iterator begin, Iterator end,
                int (*large)(const void*, const void*))

{
    /***
    函数功能：查找在begin和end之间的最大值，比较函数由large指向
        当第一个参数的值大于第二个参数的值时，返回1，否则返回0
    ***/
    Iterator max = begin;//用于记录最大的元素的迭代器
    Next(&begin);
    while(begin != end)
    {
        //找到更大的元素，让max指向更小的元素
        if( large(GetData(begin), GetData(max)) )
            max = begin;
        Next(&begin);
    }
    //返回最大元素
    return max;
}

int GetLength(List list)
{
    /***
    函数功能：获取list的长度
    ***/
    return list->length;
}

int IsEmpty(List list)
{
    /***
    函数功能：若list为空链表，则返回1，否则返回0
    ***/
    return !(list->length);
}

void DestroyList(List *list_ptr)
{
    /***
    函数功能：销毁链表list
    ***/
    Node *node = (*list_ptr)->head->next;//指向第0个结点
    Node *end = (*list_ptr)->head;//指向尾结点
    Node *tmp = NULL;//用于保存被free的结点的下一个结点
    while(node != end)
    {
        //循环删除结点
        tmp = node->next;
        free(node->data);
        free(node);
        node = tmp;
    }
    //删除头结点
    free(end);
    free(*list_ptr);
    *list_ptr = NULL;
}

Iterator Begin(List list)
{
    /***
    函数功能：获得list的首迭代器
    ***/
    return list->head->next;
}

Iterator End(List list)
{
    /***
    函数功能：获得list的尾迭代器，指向最后一个元素的下一个位置
    ***/
    return list->head;
}

Iterator Next(Iterator *it)
{
    /***
    函数功能：使it指向下一个位置，并返回指向下一个位置后的迭代器
    ***/
    (*it) = (*it)->next;
    return *it;
}

Iterator Last(Iterator *it)
{
    /***
    函数功能：使it指向上一个位置，并返回指向上一个位置后的迭代器
    ***/
    (*it) = (*it)->last;
    return *it;
}

void* GetData(Iterator it)
{
    /***
    函数功能：通过迭代器it获得数据，相当于*p
    ***/
    return it->data;
}

Iterator GetNext(Iterator it)
{
    return it->next;
}

Iterator GetLast(Iterator it)
{
    return it->last;
}

