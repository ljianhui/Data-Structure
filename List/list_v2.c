#include <stdio.h>
#include <stdlib.h>
#include "list_v2.h"

typedef struct node
{
    //ѭ��˫����Ľ��ṹ
    void* data;//������ָ��
    struct node *next;//ָ��ǰ������һ���
    struct node *last;//ָ��ǰ������һ���
}Node;

struct list
{
    struct node *head;//ͷָ�룬ָ��ͷ���
    int data_size;//�����Ӧ��������ռ�ڴ�Ĵ�С
    int length;//����list�ĳ���
};

Node* Position(List list, int index);
Node* NewNode(int data_size);
void LinkNodeToList(List list, Node *node, Node *next_node);
int RemoveNode(List list, Node *node);

int InitList(List *list_ptr, int data_size)
{
    /***
    �������ܣ���ʼ������,��������ռ�ڴ�Ĵ�С��data_size����
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
    //��ͷ����������ָ����Ϊ��
    node->data = NULL;
    //ʹ��ָ��ָ������
    node->next = node;
    node->last = node;
    //����list��ͷָ�롢������ռ�ڴ�Ĵ�С�ͳ���
    (*list_ptr)->head = node;
    (*list_ptr)->data_size = data_size;
    (*list_ptr)->length = 0;
    return 0;
}

Iterator Append(List list, void *data,
                void (*assign)(void*, const void*))
{
    /***
    �������ܣ���data�����ݲ��뵽����list��ĩβ
        assignָ������data��ĸ�ֵ����
    ***/

    //����Insert����ʵ�֣�����λ��Ϊend
    return Insert(list, data, End(list), assign);
}

void LinkNodeToList(List list, Node *node, Node *next_node)
{
    /***
    �������ܣ���node���ӵ�next_node֮ǰ
    ***/
    Node *last_node = next_node->last;
    //��node������list��
    //������صĽ���nextָ��
    last_node->next = node;
    node->next = next_node;
    //������ؽ���lastָ��
    next_node->last = node;
    node->last = last_node;
    //��node��ֵ����list��list�ĳ��ȼ�1
    ++list->length;
}

int RemoveNode(List list, Node *node)
{
    /***
    �������ܣ���list�У��Ƴ�node��㣬������free
        ע�⣬����free��㣬ֻ�ǰѽ������з���
    ***/
    if(node == list->head)
        return -1;//���Ƴ�ͷ���
    Node *next_node = node->next;
    Node *last_node = node->last;
    //ʹ���node��list�з���
    next_node->last = last_node;
    last_node->next = next_node;
    //�����list�ĳ��ȼ�1
    --list->length;
    return 0;
}

Node* Position(List list, int index)
{
    /***
    �������ܣ����ص�index������ָ��
    ***/
    Node *node = NULL;
    int i = 0;
    //���index�ȳ��ȵ�һ��С�����ǰ������
    if(index <= list->length/2)
    {
        //����node��ֵ
        node = list->head->next;
        for(i = 0; i < index; ++i)
        {
            node = node->next;//�����һ�����
        }
    }
    //����Ӻ���ǰ��
    else
    {
        node = list->head;//����node��ֵ
        for(i = list->length; i > index; --i)
        {
            node = node->last;//��ǰ��һ�����
        }
    }
    return node;
}

Node* NewNode(int data_size)
{
    /***
    �������ܣ��½�һ����㣬�����ؽ���ָ�룬
        �������������ɣ�һ�����ǽ�㱾��
        һ����Ϊdataָ��ָ���������ռ�
        ������ռ���ڴ�ռ��ɲ���data_size����
    ***/

    //������㣬������ʧ�ܣ�����NULL
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
        return NULL;
    //����������������ʧ�ܣ�����NULL
    void *data = malloc(data_size);
    if(data == NULL)
    {
        free(node);
        return NULL;
    }
    //ʹ����������ָ��ָ��������ռ䣬�����ؽ���ָ��
    node->data = data;
    return node;
}

Iterator Insert(List list, void *data, Iterator it_before,
                void (*assign)(void*, const void*))
{
    /***
    �������ܣ���data�����ݲ��뵽����list�ĵ�����it_before��ǰ��
        assignָ������data��ĸ�ֵ����
    ***/

    //���ڴ��п���һ�����Ŀռ�
    Node *node = NewNode(list->data_size);
    if(node == NULL)
    {
        //�������ڴ�ʧ�ܣ��򷵻�β������
        it_before = list->head;
        return it_before;
    }
    //���ý���ֵ
    assign(node->data, data);
    node->next = NULL;
    node->last = NULL;
    //�ѽ������������
    LinkNodeToList(list, node, it_before);
    //������ƪ����Ľ��ĵ�����
    return node;
}

Iterator MoveFromAtoB(List A, Iterator it_a,
                      List B, Iterator it_b_before)
{
    /***
    �������ܣ�������A�е�����it_aָ��Ľ���ƶ���
              ����B�е�����it_b_befroe��ǰ��
    ***/

    //�ѽ��a��A���з���
    RemoveNode(A, it_a);
    //�ѽ��a������B���еĽ��b��ǰ��
    LinkNodeToList(B, it_a, it_b_before);
    //����������B�Ľ���ָ��
    return it_a;
}

int Remove(List list, Iterator it)
{
    /***
    �������ܣ�ɾ������list�е�����itָ��Ľ��
    ***/

    //�ѽ��it��list�з���
    int n = RemoveNode(list, it);
    if(n != -1)
    {
        free(it->data);
        free(it);//free��node���
    }
    return n;
}

int RemoveFirst(List list)
{
    /***
    �������ܣ�ɾ������list�ĵ�0����㣬�±��0��ʼ
    ***/
    return Remove(list, Begin(list));
}

int RemoveLast(List list)
{
    /***
    �������ܣ�ɾ������list�����һ�����
    ***/
    return Remove(list, End(list));
}

void* At(List list, int index)
{
    /***
    �������ܣ�����list�е�index�����ݵ�ָ��
    ***/

    //��õ�index������ָ��
    Node *node = Position(list, index);
    if(node != list->head)
        return node->data;//�����������ָ��
    return NULL;//��Ϊͷ��㣬�򷵻�NULL
}

Iterator FindFirst(Iterator begin, Iterator end, void *data,
                       int (*condition)(const void*, const void*))
{
    /***
    �������ܣ���begin��end֮����ҷ���condition�ĵ�һ��Ԫ�أ�
      �ȽϺ�����conditionָ��,�Ƚϵ�ֵ��dataָ��
      ����һ��������ֵС�ڵڶ���������ֵʱ������1�����򷵻�0
      ����condition�����Ĳ�ͬ�����Բ��ҵ�һ����ȡ����ڻ�С��data��ֵ
    ***/
    while(begin != end)
    {
        //�ӿ�ʼ����������
        if(condition(GetData(begin), data))
        {
            //�ҵ��������ݵ�Ԫ�أ��˳�ѭ��
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
    �������ܣ�����list�е�һ����data��ȵ�Ԫ�ص��±꣬
        equal����������һ��������ڶ���������ֵ���ʱ������1�����򷵻�0
    ***/
    Node *node = list->head->next;//ָ���0�����
    int i = 0;
    while(node != list->head)
    {
        //������ͷ������β���ң�����ȣ��򷵻�
        if(equal(data, node->data))
            return i;
        ++i;
        node = node->next;
    }
    //û���ҵ��򷵻�-1
    return -1;
}

Iterator GetMin(Iterator begin, Iterator end,
                int (*less)(const void*, const void*))
{
    /***
    �������ܣ�������begin��end֮�����Сֵ���ȽϺ�����lessָ��
        ����һ��������ֵС�ڵڶ���������ֵʱ������1�����򷵻�0
    ***/
    Iterator min = begin; //���ڼ�¼��С��Ԫ�صĵ�����
    Next(&begin);
    while(begin != end)
    {
        //�ҵ���С��Ԫ�أ���minָ���С��Ԫ��
        if(less(GetData(begin), GetData(min)))
            min = begin;
        Next(&begin);
    }
    //������С��Ԫ��
    return min;
}

Iterator GetMax(Iterator begin, Iterator end,
                int (*large)(const void*, const void*))

{
    /***
    �������ܣ�������begin��end֮������ֵ���ȽϺ�����largeָ��
        ����һ��������ֵ���ڵڶ���������ֵʱ������1�����򷵻�0
    ***/
    Iterator max = begin;//���ڼ�¼����Ԫ�صĵ�����
    Next(&begin);
    while(begin != end)
    {
        //�ҵ������Ԫ�أ���maxָ���С��Ԫ��
        if( large(GetData(begin), GetData(max)) )
            max = begin;
        Next(&begin);
    }
    //�������Ԫ��
    return max;
}

int GetLength(List list)
{
    /***
    �������ܣ���ȡlist�ĳ���
    ***/
    return list->length;
}

int IsEmpty(List list)
{
    /***
    �������ܣ���listΪ�������򷵻�1�����򷵻�0
    ***/
    return !(list->length);
}

void DestroyList(List *list_ptr)
{
    /***
    �������ܣ���������list
    ***/
    Node *node = (*list_ptr)->head->next;//ָ���0�����
    Node *end = (*list_ptr)->head;//ָ��β���
    Node *tmp = NULL;//���ڱ��汻free�Ľ�����һ�����
    while(node != end)
    {
        //ѭ��ɾ�����
        tmp = node->next;
        free(node->data);
        free(node);
        node = tmp;
    }
    //ɾ��ͷ���
    free(end);
    free(*list_ptr);
    *list_ptr = NULL;
}

Iterator Begin(List list)
{
    /***
    �������ܣ����list���׵�����
    ***/
    return list->head->next;
}

Iterator End(List list)
{
    /***
    �������ܣ����list��β��������ָ�����һ��Ԫ�ص���һ��λ��
    ***/
    return list->head;
}

Iterator Next(Iterator *it)
{
    /***
    �������ܣ�ʹitָ����һ��λ�ã�������ָ����һ��λ�ú�ĵ�����
    ***/
    (*it) = (*it)->next;
    return *it;
}

Iterator Last(Iterator *it)
{
    /***
    �������ܣ�ʹitָ����һ��λ�ã�������ָ����һ��λ�ú�ĵ�����
    ***/
    (*it) = (*it)->last;
    return *it;
}

void* GetData(Iterator it)
{
    /***
    �������ܣ�ͨ��������it������ݣ��൱��*p
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

