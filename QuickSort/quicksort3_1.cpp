#include <iostream>

using namespace std;

/*******
ʹ��������ֵ����ѡȡ��Ŧֵ��
������Сֵ���ڵ�0��λ��
���ֵ��������λ�ã�
����ֵ��Ϊ��Ŧ�����뵹���ڶ������ݽ���λ��
��������ݴ�С����
*******/
typedef int DataType;
void QuickSort(DataType *data, int data_size);
void QSort(DataType *data, int left, int right);
DataType Median3(DataType *data, int left, int right);
void Swap(DataType &x, DataType &y);
void BubbleSort(DataType *data, int data_size);

int main()
{
    DataType data[12]= {3,2,1,4,6,5,9,8,7,10,12,11};
    QuickSort(data, 12);
    for(int i = 0; i < 12; ++i)
        cout<<data[i]<<endl;
    return 0;
}

void QuickSort(DataType *data, int data_size)
{
    //������������
    QSort(data, 0, data_size - 1);
}

DataType Median3(DataType *data, int left, int right)
{
    //ȡ���ݵ�ͷ��β���м����������������ǽ�������
    //������ֱ�ӱ�����������
    int centre = (left + right)/2;
    if(data[left] > data[centre])
        Swap(data[left], data[centre]);
    if(data[left] > data[right])
        Swap(data[left], data[right]);
    if(data[centre] > data[right])
        Swap(data[centre], data[right]);
    //����ֵ������Ŧ�����鵹���ڶ���Ԫ�ؽ���
    swap(data[centre], data[right - 1]);
    return data[right - 1];//������Ŧ

}

void QSort(DataType *data, int left, int right)
{
    //�����Ҫ��������ݴ���3����ʹ�ÿ�������
    if(right - left >= 3)
    {
        //ȡ����Ŧ��ֵ
        DataType centre = Median3(data, left, right);
        int begin = left;
        int end = right - 1;
        while(true)
        {
            //���ɨ������
            //������ѡ����Ŧʱ���Ѿ��ѱ���Ŧֵ������ݷ���rightλ��
            //���Բ���Խ��
            while(data[++begin] < centre);
            //��ǰɨ������
            //������ѡ����Ŧʱ���Ѿ��ѱ���ŦֵС�����ݷ���leftλ��
            //���Բ���Խ��
            while(data[--end] > centre);
            //�ѱ���ŦС�����ݷ���ǰ������ķŵ���
            if(begin < end)
                Swap(data[begin], data[end]);
            else
            {
                //�Ѿ���Ҫ��������ݶ�����Ŧ�Ƚ���һ��
                //������Ŧ�������ʵ���λ�ã���Ϊbegin����һ������Ŧ��
                //���԰�����������������
                Swap(data[begin], data[right - 1]);
                break;
            }
        }

        QSort(data, left, begin - 1);
        QSort(data, begin + 1, right);
    }
    else //���Ҫ��������ݺ��٣����ڵ���3������ֱ��ʹ��ð������
    {
        BubbleSort(data+left, right - left + 1);
    }
}

void Swap(DataType &x, DataType &y)
{
    //�����������ݵ�ֵ
    DataType tmp = x;
    x = y;
    y = tmp;
}

void BubbleSort(DataType *data, int data_size)
{
    //ð�������㷨
    bool hasSwap = true;//����ָʾ��һ�˱Ƚ��У��Ƿ���ڽ���
    for(int i = 0; i < data_size-1; ++i)
    {
        //����һ�˵ıȽ��У����������ݽ����������������˳�ѭ��
        if(hasSwap == false)
            break;
        hasSwap = false;

        for(int j = 0; j < data_size - i - 1; ++j)
        {
            if(data[j] > data[j+1])
            {
                Swap(data[j], data[j+1]);
                hasSwap = true;
            }
        }
    }
}

