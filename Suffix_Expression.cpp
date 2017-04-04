/********************************************************/
/*****************Author:Uranuslight****************/
/********************************************************/
#pragma warning(disable:4996) 
#include "iostream"
#include "cstdlib"
#include "conio.h"
#include "vector"
#include "map"
#include "deque"
#include "sstream"
#include "cstdio"
#include "cmath"
#include "cstring"
#include "ctime"
#include "fstream"
#include "iomanip"
#ifndef MAX_N
#define MAX_N 64
#endif // !MAX_N

using namespace std;
/******************************************************************************************************/
typedef double NumType;//��׺���ʽ��ֵ����
typedef char OperatorType;//����������
typedef struct
{
	NumType *Data;
	int Max_Len;
	int top;
}NumStack;//��ֵ�ṹ��
NumStack Stack1;
/******************************************************************************************************/
typedef char Array[32];
typedef Array ElemType;
typedef struct NodeType
{
	ElemType Data;//32�ֽ��ַ�����
	NodeType *next;
}NodeType, *LinkType;
typedef struct
{
	LinkType top;
	int size;
}Stack;
/******************************************************************************************************/
bool InitiateStack(NumStack &Stack);//��׺���ʽ��ֵ����ջ��ʼ��
bool Push(NumStack &Stack, double Num);//��׺���ʽ��ֵ����ջ
double Pop(NumStack &Stack);//��׺���ʽ��ֵ����ջ
double Calculator(double Num1, char Operator, double Num2);//���ݲ���������ջ����Ԫ�ص�ֵ
bool IsOperator(char ch);//�жϵ�ǰ�ַ��Ƿ��������
double Calculate(char *s);//����������׺���ʽ��ֵ
void Initiate(Stack &s);//��׺���ʽ��ǰ׺���ʽ����ջ��ʼ��
bool Push(Stack &s, ElemType e);//��׺���ʽ��ǰ׺���ʽ����ջ��������
bool Pop(Stack &s, ElemType e);//��׺���ʽ��ǰ׺���ʽ����ջ��������
bool CheckStackisEmpty(Stack &s);//��׺���ʽ��ǰ׺���ʽ����鵱ǰ�Ƿ�ջ��
bool CheckStackisEmpty(NumStack &Stack);//��׺���ʽ��ֵ����鵱ǰ�Ƿ�ջ�պ�������
bool TransToFrontPoland(char *a);//��׺���ʽ��ǰ׺���ʽ����ת������
/***********************************************��׺���ʽ��ֵ����*******************************************************/
bool InitiateStack(NumStack &Stack)
{
	Stack.Data = new NumType[MAX_N];
	if (!Stack.Data)
	{
		cout << "�ڴ����ʧ��" << endl;
		system("pause");
		return false;
	}
	Stack.Max_Len = MAX_N;
	Stack.top = -1;
	return true;
}

bool Push(NumStack &Stack, double Num)
{
	if (Stack.top >= Stack.Max_Len - 1)
	{
		cout << endl << "��ջ����" << endl;
		system("pause");
		return false;
	}
	Stack.Data[++Stack.top] = Num;
	return true;
}

double Pop(NumStack &Stack)
{
	if (Stack.top == -1)
	{
		cout << endl << "��ջ��" << endl;
		system("pause");
		return false;
	}
	return Stack.Data[Stack.top--];
}

double Calculator(double Num1, char Operator, double Num2)
{
	switch (Operator)
	{
	case '+':
		return Num1 + Num2;
		break;
	case '-':
		return Num1 - Num2;
		break;
	case '*':
		return Num1 * Num2;
		break;
	case '/':
		return Num1 / Num2;
		break;
	default:
		return -0xFFFFFFF;
		break;
	}
}

bool IsOperator(char ch)//�жϵ�ǰ�ַ��Ƿ��������
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}

bool CheckStackisEmpty(NumStack &Stack)
{
	if (Stack.top == -1)
		return true;
	else
	{
		return false;
	}
}

double Calculate(char *s)
{
	double Answer = 0;
	while (*s != '\0')
	{
		double Num = 0;
		/*����ע�Ͷ���ȥע�Ϳ�ִ�ж�λ���ĺ�׺���ʽֵ���㣬���磺567 + 952��
		ע�⣺ִ�ж�λ����׺���ʽ����ʱ�����������֮����Ҫ�ÿո����������
		Ҫע���°벿�ִ��룬�����ܲ���ͬʱִ�У�תǰ׺���ʽ�ݲ�֧�ֶ�λ��*/
		/*******************************ִ��֧�ֶ�λ���ĺ�׺���ʽֵ����Ƭ��*********************************
		int Flag = 0;
		while (*s >= '0' && *s <= '9' || *s == 'N' || *s == 'n')
		{
			if (*s != 'N' && *s != 'n')
			{
				Num = Num * 10.0 + *s - '0';
				s++;
			}
			else
			{
				Num = -Num;
				s++;
			}
			Flag = 1;
			if (*s == ' ')
			{
				s++;
				break;
			}
		}
		if (Flag == 1)
		{
			Push(Stack1, Num);
			Flag = 0;
		}
		/*******************************ִ��֧�ֶ�λ���ĺ�׺���ʽֵ����Ƭ��*********************************/
		/*******************�ò���ֻ��ִ�и�λ���ĺ�׺���ʽ������������ʹ�ö�λ�����㣬��ע�ʹ˶�*******************/
		if (*s >= '0' && *s <= '9')
		{
			if (*(s + 1) == 'N' || *(s + 1) == 'n')
			/*�ж���һ���ַ��Ƿ�ΪN����ΪN��ִ��ֵ�󷴣�(*(++s) == 'N')
			��(*(s++) == 'N')�Ի�����ָ���ƶ�������ֵ����                     */
			{
				Num = -(*s - '0');
				s++; s++;/*�˴�ָ���ƶ����Σ������ͣ����N or n���º�������*/
			}
			else
			{
				Num = *s - '0';
				s++;
			}
			Push(Stack1, Num);
		}
		/*******************�ò���ֻ��ִ�и�λ���ĺ�׺���ʽ������������ʹ�ö�λ�����㣬��ע�ʹ˶�*******************/
		if (*s == ' ')
		{
			s++;
			continue;
		}
		if (IsOperator(*s))
		{
			double Num1 = 0, Num2 = 0;
			if (!CheckStackisEmpty(Stack1))
			{
				Num2 = Pop(Stack1);//��ջ˳�򲻿ɱ䣬������ֵ����
				if (!CheckStackisEmpty(Stack1))
				{
					Num1 = Pop(Stack1);
					Answer = Calculator(Num1, *s, Num2);
				}
				else 
					return 0xFFFFFF0;//���ʽ���Ϸ�
			}
			else 
				return 0xFFFFFF0;//���ʽ���Ϸ�
			if (Answer == 0xFFFFFFF)
			{
				cout << "�����쳣��������-NAN(IND)�����" << endl;
				system("pause");
				exit(0);
			}
			else
			{
				Push(Stack1, Answer);
				s++;
			}
		}
	}
	return Stack1.Data[0];
}
/***********************************************��׺���ʽ��ֵ����*******************************************************/
/***********************************************��׺���ʽ��ǰ׺���ʽ����*******************************************************/
void Initiate(Stack &s)
{
	s.size = 0;
	s.top = NULL;
}

bool Push(Stack &s, ElemType e)
{
	LinkType p;
	p = new NodeType;
	if (!p)
	{
		cout << "�ڴ����ʧ��" << endl;
		system("pause");
		return false;
	}
	p->next = s.top;
	s.top = p;
	strcpy(p->Data, e);
	s.size++;
	return true;
}
bool Pop(Stack &s, ElemType e)
{
	LinkType p;
	if (s.top)
	{
		strcpy(e, s.top->Data);
		p = s.top;
		s.top = p->next;
		delete p;
		s.size--;
		return true;
	}
	else
	{
		cout << "��ջ��" << endl;
		system("pause");
		return false;
	}
}
bool CheckStackisEmpty(Stack &s)
{
	if (s.size == 0)	
		return true;
	else
	{
		return false;
	}
}

bool TransToFrontPoland(char *a)
{
	Stack s;
	Initiate(s);
	int i = 0;
	ElemType ch, ch1, ch2;
	while (a[i] != '\0')
	{
		if (!IsOperator(a[i]))//���ǲ�����
		{
			if (a[i] >= '0' && a[i] <= '9')//��֧�ָ�λ��
			{
				if (a[i + 1] == 'N' || a[i + 1] == 'n')
				{
					ch[0] = '(';//������'-'�Ž���ʾ����
					ch[1] = '-';
					ch[2] = a[i];
					ch[3] = ')';
					ch[4] = '\0';
					i++;//ȡ���������ռһ���ֽڣ������ƶ�һ��
				}
				else
				{
					ch[0] = a[i];
					ch[1] = '\0';
				}
				Push(s, ch);//�����֣�ֱ�ӽ�ջ
			}
			else		
				return false;//���ǲ�����Ҳ�������֣����ʽ���Ϸ�
		}
		else
		{
			ch[0] = a[i];//�ǲ�����
			ch[1] = '\0';//�ַ�������
			if (!CheckStackisEmpty(s))//����Ƿ�ջ�գ���ջ��˵���ж�����ţ������ʽ���Ϸ�
			{
				Pop(s, ch2);//��ջ
				if (!CheckStackisEmpty(s))//���μ���Ƿ�ջ�գ���ջ��˵��˫Ŀ�����ֻ��һ���������������ʽ���Ϸ�
				{
					Pop(s, ch1);
					strcat(ch, ch1);//�ַ����Խӣ�˳�򲻿��ң��������
					strcat(ch, ch2);
					Push(s, ch);//�ԽӺõ��ַ�����ջ
				}
				else		
					return false;//���μ���Ƿ�ջ�գ��ǣ��쳣�˳�
			}
			else		
				return false;//��һ�μ���Ƿ�ջ�գ��ǣ��쳣�˳�
		}
		i++;//�Ǳ��ƶ�
	}
	if (!CheckStackisEmpty(s))
	{
		Pop(s, ch2);
		strcpy(a, ch2);//����������β�
	}
	else		return false;
	if (!CheckStackisEmpty(s))		return false;
	return true;
}
/***********************************************��׺���ʽ��ǰ׺���ʽ����*******************************************************/

int main()
{
	system("color F0");
	char str[MAX_N];
	int t = 5;
	while (t--)
	{
		double Answer = 0;
		InitiateStack(Stack1);
		cout << "�����׺���ʽ:" << endl;
		cin.get(str, sizeof(str));//�������ո��ȡ�ַ��������������ַ����ж�����
		cin.get();                     //��ȡ���������ַ��������������
		Answer = Calculate(str);
		if (TransToFrontPoland(str))
		{
			cout << "ת�����ǰ׺���ʽΪ��" << endl;
			cout << str << endl;
			if (Answer != 0xFFFFFF0)
			{
				cout << "������׺���ʽֵΪ��" << Answer << endl;
			}
			else
				cout << "���ʽ���Ϸ�" << endl;
		}
		else
			cout << "���ʽ���Ϸ�" << endl;
	}
	system("pause");
	return 0;
}