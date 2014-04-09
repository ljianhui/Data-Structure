#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef int DataType;

void MSort(DataType *data, DataType *tmp, int left, int right);
void Merge(DataType *data, DataType *tmp, int left, int center, int right);
void MergeSort(DataType *data, int size);

void MergeSort(DataType *data, int size)
{
    if(data == NULL || size <= 1)
        return;

    DataType *tmp = new DataType[size];
    MSort(data, tmp, 0, size-1);

    delete[] tmp;
}

void MSort(DataType *data, DataType *tmp, int left, int right)
{
    if(data == NULL || tmp == NULL)
        return;

    if(left >= right || left < 0)
        return;

    int center = (left + right)>>1;
    MSort(data, tmp, left, center);
    MSort(data, tmp, center+1, right);
    Merge(data, tmp, left, center, right);
}

void Merge(DataType *data, DataType *tmp, int left, int center, int right)
{
    if(data == NULL || tmp == NULL)
        return;
    if(left > center || center > right)
        return;
    if(left < 0)
        return;

    int left_begin = left;
    int left_end = center;
    int right_begin = center + 1;
    int right_end = right;
    int index_tmp = left;

    while(left_begin <= left_end && right_begin <= right_end)
    {
        if(data[left_begin] < data[right_begin])
            tmp[index_tmp++] = data[left_begin++];
        else
            tmp[index_tmp++] = data[right_begin++];
    }

    while(left_begin <= left_end)
        tmp[index_tmp++] = data[left_begin++];
    while(right_begin <= right_end)
        tmp[index_tmp++] = data[right_begin++];

    for(int i = left; i <= right; ++i)
        data[i] = tmp[i];
}

int main()
{
    const int size = 10;
    DataType *data = new DataType[size];
    srand(NULL);
    for(int i = 0; i < size; ++i)
        data[i] = rand()%120;

    int begin = time(NULL);
    MergeSort(data, size);
    int end = time(NULL);
    cout << end - begin << endl;
    cout << endl;

    for(int i = 0; i < size; ++i)
        cout << data[i] << " ";
    delete[] data;
}
