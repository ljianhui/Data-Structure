#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

typedef int DataType;

inline int LeftChild(int i);
inline void Swap(DataType &x, DataType &y);
void BuildHeap(DataType *data, int begin, int end);
void HeapSort(DataType *data, int data_size);

inline int LeftChild(int i)
{
    return (i<<1)+1;
}

inline void Swap(DataType &x, DataType &y)
{
    DataType tmp(x);
    x = y;
    y = tmp;
}

void BuildHeap(DataType *data, int i, int N)
{
    if(data == NULL || i > N || i < 0)
        return;

    int child;
    DataType tmp = data[i];
    for(; LeftChild(i) < N; i = child)
    {
        child = LeftChild(i);
        if(child != N-1 && data[child+1] > data[child])
            ++child;
        if(tmp < data[child])
            data[i] = data[child];
        else
            break;
    }
    data[i] = tmp;
}

void HeapSort(DataType *data, int data_size)
{
    if(data == NULL || data_size < 1)
        return;
    int i;
    for(i = data_size>>1; i >=0; i--)
    {
        BuildHeap(data, i, data_size);
    }
    for(i = data_size-1; i > 0; i--)
    {
        Swap(data[0], data[i]);
        BuildHeap(data, 0, i);
    }
}

int main()
{
    srand(NULL);
    const int size =  128 * 1024 * 1024;
    DataType *data = new DataType[size];
    for(int i = 0; i < size; ++i)
    {
        data[i] = rand();
    }
    int begin = time(NULL);
    HeapSort(data, size);
    int end = time(NULL);
    cout << end - begin << endl;
//    for(int i = 0; i < size; ++i)
//        cout << data[i] << " ";

    delete[] data;
    return 0;
}
