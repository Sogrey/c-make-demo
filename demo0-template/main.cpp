#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    cout << argc << endl; // �����������
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }
    // ����0 argv[0] �� ��ִ���ļ����� ����Ϊ����
    int total = atoi(argv[1]); //���ַ���argv[1]ת��Ϊ���ͣ�����ֵ��i�� 
    int duration = atoi(argv[2]); // milliseconds
    //  atof(argv[1]); // ����תΪ float

    return 0;
}