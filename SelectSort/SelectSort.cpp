#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

bool ReadFileToVector(const char *fileName, vector<int> &vecData);
//���ļ�fileName�������ļ��е��������ݶ���vector�����С�
void SelectSortDown(vector<int> &vecData);
//��ѡ�񷨰�vector�����е����ݰ���С������������
void SelectSortUp(vector<int> &vecData);
//��ѡ�񷨰�vector'�����е����ݰ��Ӵ�С����������
bool WriteVectorToFile(const char *fileName, const vector<int> &vecData);
//��vector�е�����д��fileName�У�ÿ�������Կո�ָ�

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        //����Ĳ�����������ȷ�����˳�����
        cerr<<"The count of parameters is ERROR!"<<endl;
        exit(EXIT_FAILURE);
    }

    vector<int> vecData;
    //��ָ���ļ������ݶ���vector��
    ReadFileToVector(argv[1], vecData);

    if(strcmp(argv[3], "1") == 0)
    {
        //�����롰1������Ӵ�С����
        SelectSortUp(vecData);
    }
    else
    {
        //���򣬴�С��������
        SelectSortDown(vecData);
    }
    //��vector�е����ݱ��浽ָ���ļ���
    WriteVectorToFile(argv[2], vecData);

    exit(EXIT_SUCCESS);
}

bool ReadFileToVector(const char *fileName, vector<int> &vecData)
{
    //��ֻ����ʽ�����ļ�fileName
    ifstream inputFile(fileName);
    if(!inputFile)
    {
        //���ļ�ʧ��
        cerr<<"error: unable to open input file: "
            <<fileName<<endl;
        return false;
    }

    int number = 0;
    while(!inputFile.eof())
    {
        //���ļ��е����ݸ��Ƶ�vector������
        inputFile >> number;
        vecData.push_back(number);
    }
    //�ر��ļ���
    inputFile.close();
    return true;
}

bool WriteVectorToFile(const char *fileName, const vector<int> &vecData)
{
    //��ֻд��ʽ�����ļ�fileName
    ofstream outputFile(fileName);
    if(!outputFile)
    {
        //���ļ�ʧ��
        cerr<<"error: unable to open input file: "
            <<fileName<<endl;
        return false;
    }
    //��vector�е�����д���ļ���
    vector<int>::const_iterator it(vecData.begin());
    for(;it != vecData.end(); ++it)
    {
        outputFile<<*it<<" ";
    }
    //�ر��ļ���
    outputFile.close();
    return true;
}

void SelectSortDown(vector<int> &vecData)
{
    int sizeOfVec = vecData.size();//���ڼ�¼����Ĵ�С
    for(int i = 0; i < sizeOfVec-1; ++i)
    {
        int minIndex = i;//���ڼ�¼��ǰ��СԪ�ص��±�
        for(int j = i+1; j < sizeOfVec; ++j)
        {
            if(vecData[minIndex] > vecData[j])
                minIndex = j;
        }
        if(minIndex != i)
        {
            //�����С��Ԫ�ز���Ҫ�����λ��i�ϣ��򽻻����ݡ�
            int tmp = vecData[i];
            vecData[i] = vecData[minIndex];
            vecData[minIndex] = tmp;
        }
    }
}

void SelectSortUp(vector<int> &vecData)
{
    int sizeOfVec = vecData.size();
    for(int i = 0; i < sizeOfVec-1; ++i)
    {
        int maxIndex = i;//���ڼ�¼��ǰ���Ԫ�ص��±�
        for(int j = i+1; j < sizeOfVec; ++j)
        {
            if(vecData[maxIndex] < vecData[j])
                maxIndex = j;
        }
        if(maxIndex != i)
        {
            int tmp = vecData[i];
            vecData[i] = vecData[maxIndex];
            vecData[maxIndex] = tmp;
        }
    }
}
