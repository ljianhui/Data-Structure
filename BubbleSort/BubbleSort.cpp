#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

bool ReadFileToVector(const char *fileName, vector<int> &vecData);
//���ļ�fileName�������ļ��е��������ݶ���vector�����С�
void BubbleSortDown(vector<int> &vecData);
//��ð�ݷ���vector�����е����ݰ���С������������
void BubbleSortUp(vector<int> &vecData);
//��ð�ݷ���vector'�����е����ݰ��Ӵ�С����������
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
        BubbleSortUp(vecData);
    }
    else
    {
        //���򣬴�С��������
        BubbleSortDown(vecData);
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

void BubbleSortDown(vector<int> &vecData)
{
    bool hasSwap = true;//����ָʾ��һ�˱Ƚ��У��Ƿ���ڽ���
    int sizeOfVec = vecData.size();//���ڼ�¼����Ĵ�С
    for(int count = 0; count < sizeOfVec -1; ++count)
    {
        //����һ�˵ıȽ��У����������ݽ����������������˳�ѭ��
        if(hasSwap == false)
            break;
        hasSwap = false;
        for(int i = 0; i < sizeOfVec - count -1; ++i)
        {
            hasSwap = false;
            if(vecData[i] > vecData[i+1])
            {
                //��������
                int tmp = vecData[i];
                vecData[i] = vecData[i+1];
                vecData[i+1] = tmp;
                hasSwap = true;
            }
        }
    }
}

void BubbleSortUp(vector<int> &vecData)
{
    bool hasSwap = true;
    int sizeOfVec = vecData.size();
    for(int count = 0; count < sizeOfVec -1; ++count)
    {
        if(hasSwap == false)
            break;
        hasSwap = false;
        for(int i = 0; i < sizeOfVec - count -1; ++i)
        {
            if(vecData[i] < vecData[i+1])
            {
                int tmp = vecData[i];
                vecData[i] = vecData[i+1];
                vecData[i+1] = tmp;
                hasSwap = true;
            }
        }
    }
}
