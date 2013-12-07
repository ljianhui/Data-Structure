#ifndef LIST_V2_H_INCLUDED
#define LIST_V2_H_INCLUDED

//循环双链表，带头结点，结点下标从0开始，头结点不计入下标值

typedef struct node Node;

//定义结点指针Node*为List类型的迭代器
typedef struct node* Iterator;

//List类型的定义
typedef struct list
{
    struct node *head;//头指针，指向头结点
    int data_size;//链表对应的数据所占内存的大小
    int length;//链表list的长度
}List;
//初始化链表,数据域所占内存的大小由data_size给出
int InitList(List *list, int data_size);

//把data的内容插入到链表list的末尾
//assign指定数据data间的赋值方法
Iterator Append(List *list, void *data,
                void (*assign)(const void*, const void*));

//把data的内容插入到链表的迭代器it_before的前面
//assign指定数据data间的赋值方法
Iterator Insert(List *list, void *data, Iterator it_before,
                void (*assign)(const void*, const void*));

//把链表A中迭代器it_a指向的结点移动到链表B中迭代器it_b_befroe的前面
Iterator MoveFromAtoB(List *A, Iterator it_a,
                      List *B, Iterator it_b_before);

//删除链表list中迭代器it指向的结点
int Remove(List *list, Iterator it);

//删除链表list的第0个结点，下标从0开始
int RemoveFirst(List *list);

//删除链表list的最后一个结点
int RemoveLast(List *list);

//返回list中第index个数据的指针
void* At(List *list, int index);

//在begin和end之间查找符合condition的第一个元素，
//比较函数由condition指向,比较的值由data指向
//当第一个参数的值小于第二个参数的值时，返回1，否则返回0
//根据condition函数的不同，可以查找第一个相等、大于或小于data的值
Iterator FindFirst(Iterator begin, Iterator end, void *data,
                       int (*condition)(const void*, const void*));

//查找list中第一个与data相等的元素的下标，
//equal函数，当第一个参数与第二个参数的值相等时，返回1，否则返回0
int IndexOf(List *list, void *data,
            int (*equal)(const void*,const void*));

//查找在begin和end之间的最小值，比较函数由less指向
//当第一个参数的值小于第二个参数的值时，返回1，否则返回0
Iterator GetMin(Iterator begin, Iterator end,
                int (*less)(const void*, const void*));

//查找在begin和end之间的最大值，比较函数由large指向
//当第一个参数的值大于第二个参数的值时，返回1，否则返回0
Iterator GetMax(Iterator begin, Iterator end,
                int (*large)(const void*, const void*));

//获取list的长度
int GetLength(List *list);
//若list为空链表，则返回1，否则返回0
int IsEmpty(List *list);
//销毁list
void DestoryList(List *list);

//获得list的首迭代器
Iterator Begin(List *list);
//获得list的尾迭代器，指向最后一个元素的下一个位置
Iterator End(List *list);
//使it指向下一个位置，并返回指向下一个位置后的迭代器
Iterator Next(Iterator *it);
//使it指向上一个位置，并返回指向上一个位置后的迭代器
Iterator Last(Iterator *it);
//通过迭代器it获得数据，相当于*p
void* GetData(Iterator it);

#endif // LIST_H_INCLUDED
