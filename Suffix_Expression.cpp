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
typedef double NumType;//后缀表达式求值类型
typedef char OperatorType;//操作符类型
typedef struct
{
	NumType *Data;
	int Max_Len;
	int top;
}NumStack;//求值结构体
NumStack Stack1;
/******************************************************************************************************/
typedef char Array[32];
typedef Array ElemType;
typedef struct NodeType
{
	ElemType Data;//32字节字符数组
	NodeType *next;
}NodeType, *LinkType;
typedef struct
{
	LinkType top;
	int size;
}Stack;
/******************************************************************************************************/
bool InitiateStack(NumStack &Stack);//后缀表达式求值：堆栈初始化
bool Push(NumStack &Stack, double Num);//后缀表达式求值：入栈
double Pop(NumStack &Stack);//后缀表达式求值：出栈
double Calculator(double Num1, char Operator, double Num2);//根据操作符计算栈顶两元素的值
bool IsOperator(char ch);//判断当前字符是否是运算符
double Calculate(char *s);//计算整个后缀表达式的值
void Initiate(Stack &s);//后缀表达式改前缀表达式：堆栈初始化
bool Push(Stack &s, ElemType e);//后缀表达式改前缀表达式：入栈函数重载
bool Pop(Stack &s, ElemType e);//后缀表达式改前缀表达式：出栈函数重载
bool CheckStackisEmpty(Stack &s);//后缀表达式改前缀表达式：检查当前是否栈空
bool CheckStackisEmpty(NumStack &Stack);//后缀表达式求值：检查当前是否栈空函数重载
bool TransToFrontPoland(char *a);//后缀表达式改前缀表达式：主转换函数
/***********************************************后缀表达式求值部分*******************************************************/
bool InitiateStack(NumStack &Stack)
{
	Stack.Data = new NumType[MAX_N];
	if (!Stack.Data)
	{
		cout << "内存分配失败" << endl;
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
		cout << endl << "堆栈已满" << endl;
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
		cout << endl << "堆栈空" << endl;
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

bool IsOperator(char ch)//判断当前字符是否是运算符
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
		/*以下注释段落去注释可执行多位数的后缀表达式值计算，例如：567 + 952等
		注意：执行多位数后缀表达式计算时，输入各数据之间需要用空格隔开，且需
		要注释下半部分代码，两功能不能同时执行，转前缀表达式暂不支持多位数*/
		/*******************************执行支持多位数的后缀表达式值计算片段*********************************
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
		/*******************************执行支持多位数的后缀表达式值计算片段*********************************/
		/*******************该部分只能执行个位数的后缀表达式计算任务，如需使用多位数计算，请注释此段*******************/
		if (*s >= '0' && *s <= '9')
		{
			if (*(s + 1) == 'N' || *(s + 1) == 'n')
			/*判断下一个字符是否为N，若为N则执行值求反，(*(++s) == 'N')
			与(*(s++) == 'N')皆会引起指针移动导致求值错误                     */
			{
				Num = -(*s - '0');
				s++; s++;/*此处指针移动两次，否则会停留在N or n导致后续错误*/
			}
			else
			{
				Num = *s - '0';
				s++;
			}
			Push(Stack1, Num);
		}
		/*******************该部分只能执行个位数的后缀表达式计算任务，如需使用多位数计算，请注释此段*******************/
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
				Num2 = Pop(Stack1);//出栈顺序不可变，否则导致值错误
				if (!CheckStackisEmpty(Stack1))
				{
					Num1 = Pop(Stack1);
					Answer = Calculator(Num1, *s, Num2);
				}
				else 
					return 0xFFFFFF0;//表达式不合法
			}
			else 
				return 0xFFFFFF0;//表达式不合法
			if (Answer == 0xFFFFFFF)
			{
				cout << "发生异常，可能是-NAN(IND)引起的" << endl;
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
/***********************************************后缀表达式求值部分*******************************************************/
/***********************************************后缀表达式改前缀表达式部分*******************************************************/
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
		cout << "内存分配失败" << endl;
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
		cout << "堆栈空" << endl;
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
		if (!IsOperator(a[i]))//不是操作符
		{
			if (a[i] >= '0' && a[i] <= '9')//仅支持个位数
			{
				if (a[i + 1] == 'N' || a[i + 1] == 'n')
				{
					ch[0] = '(';//括号内'-'号仅表示负数
					ch[1] = '-';
					ch[2] = a[i];
					ch[3] = ')';
					ch[4] = '\0';
					i++;//取反运算符多占一个字节，所以移动一次
				}
				else
				{
					ch[0] = a[i];
					ch[1] = '\0';
				}
				Push(s, ch);//是数字，直接进栈
			}
			else		
				return false;//不是操作符也不是数字，表达式不合法
		}
		else
		{
			ch[0] = a[i];//是操作符
			ch[1] = '\0';//字符串处理
			if (!CheckStackisEmpty(s))//检查是否栈空，若栈空说明有多余符号，即表达式不合法
			{
				Pop(s, ch2);//出栈
				if (!CheckStackisEmpty(s))//二次检查是否栈空，若栈空说明双目运算符只有一个操作数，即表达式不合法
				{
					Pop(s, ch1);
					strcat(ch, ch1);//字符串对接，顺序不可乱，否则出错
					strcat(ch, ch2);
					Push(s, ch);//对接好的字符串入栈
				}
				else		
					return false;//二次检查是否栈空，是，异常退出
			}
			else		
				return false;//第一次检查是否栈空，是，异常退出
		}
		i++;//角标移动
	}
	if (!CheckStackisEmpty(s))
	{
		Pop(s, ch2);
		strcpy(a, ch2);//结果拷贝给形参
	}
	else		return false;
	if (!CheckStackisEmpty(s))		return false;
	return true;
}
/***********************************************后缀表达式改前缀表达式部分*******************************************************/

int main()
{
	system("color F0");
	char str[MAX_N];
	int t = 5;
	while (t--)
	{
		double Answer = 0;
		InitiateStack(Stack1);
		cout << "输入后缀表达式:" << endl;
		cin.get(str, sizeof(str));//不跳过空格读取字符串，否则会出现字符串中断现象
		cin.get();                     //读取其他无用字符，否则引起崩溃
		Answer = Calculate(str);
		if (TransToFrontPoland(str))
		{
			cout << "转化后的前缀表达式为：" << endl;
			cout << str << endl;
			if (Answer != 0xFFFFFF0)
			{
				cout << "上述后缀表达式值为：" << Answer << endl;
			}
			else
				cout << "表达式不合法" << endl;
		}
		else
			cout << "表达式不合法" << endl;
	}
	system("pause");
	return 0;
}