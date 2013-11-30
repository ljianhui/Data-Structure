#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//循环双链表，带头结点，结点下标从0开始，头结点不计入下标值
//声明类型类型，用于测试，使用时，定义为需要的类型
typedef int DataType;
typedef struct node Node;
//List类型的迭代器，与指针类似
typedef struct iterator
{
    struct node *addr;
}Iterator;
//List类型的定义
typedef struct list
{
    struct node *head;
    int length;
}List;
//初始化链表
int InitList(List *list, void (*InitData)(DataType*));

//把data的内容插入到链表list的末尾
Iterator Append(List *list, DataType *data);
//把data的内容插入到链表的迭代器it_before的前面
Iterator Insert(List *list, DataType *data, Iterator it_before);
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
DataType* At(List *list, int index);
//查找符合condition的list中的第一个结点，
//condition函数，符合返回1，否则返回0
Iterator Find(List *list, int(*condition)(const DataType*));
//查找list中第一个与data相等的元素，
//equal函数，当第一个参数与第二个参数的值相等时，返回1，否则返回0
Iterator FindFirstEqual(List *list, DataType *data,
                        int (*equal)(const DataType*,const DataType*));
//查找list中第一个与data相等的元素的下标，
//equal函数，当第一个参数与第二个参数的值相等时，返回1，否则返回0
int IndexOf(List *list, DataType *data,
            int (*equal)(const DataType*,const DataType*));
//查找list中的最小值，比较函数由less指向
//当第一个参数的值小于第二个参数的值时，返回1，否则返回0
Iterator GetMin(List *list, int (*less)(const DataType*, const DataType*));
//查找list中的最大值，比较函数由less指向
//当第一个参数的值大于第二个参数的值时，返回1，否则返回0
Iterator GetMax(List *list, int (*large)(const DataType*, const DataType*));

//获取list的长度
int GetLength(List *list);
//若list为空链表，则返回1，否则返回0
int IsEmpty(List *list);
//销毁list
void DestoryList(List *list);

//获得list的首迭代器
Iterator Begin(List *list);
//获得list的尾迭代器
Iterator End(List *list);
//使it指向下一个位置，并返回指向下一个位置后的迭代器
Iterator Next(Iterator *it);
//使it指向上一个位置，并返回指向上一个位置后的迭代器
Iterator Last(Iterator *it);
//通过迭代器it获得数据，相当于*p
DataType* GetData(Iterator it);
//判断两个迭代器是否相等，是返回1，否返回0
int IsEqual(Iterator it_a, Iterator it_b);

#endif // LIST_H_INCLUDED
