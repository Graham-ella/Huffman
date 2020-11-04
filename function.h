#pragma once
#include <iostream>
using namespace std;
const int max = 500;

typedef struct node {
	double weight;
	int lchild;
	int rchild;
	int parent;
}HTNODE;//结点

typedef struct codenode {
	char ch;//存储被编码的字符
	char bits[max + 1];//字符对应的编码
}CodeNode;


typedef HTNODE* HuffmanT;

typedef CodeNode* HuffmanCode;

int readFromTxt(char ch[max],int count[max]);//读取文本，记录出现的字符和出现次数

int charIsRead(char c, char* ch);//判断字符之前是否被读到

void InitHT(HuffmanT T,int n);//初始化哈夫曼树

void InputW(HuffmanT T,int n,int count[max]);//输入权值

void SelectMin(HuffmanT T, int j, int* p1, int* p2);//寻找两个权值最小的结点

void CreateHT(HuffmanT T,int n,int count[max]);//构造哈夫曼树

void CharSetHuffmanEncoding(HuffmanT T, HuffmanCode Hcode, int n,char ch[max]);//哈夫曼编码的算法实现

string findCode(HuffmanCode Hcode, char c);//得到字符c对应的哈夫曼编码

void WriteCodeToFile(HuffmanCode Hcode);//将文本对应的01编码存入文件中

int completeCode();//添0操作，返回增添的个数

void compressCodeTxt();//将01码8个一组以二进制形式存入文件中

string change(char c);//读取二进制

void readBinaryTxt();//读取二进制文件

void ReadCodeToTxt(HuffmanT T,int n, char ch[max]);//从存01码的文件中得到原文本

void Result(HuffmanT T, int n, char ch[max],int addzero);//从二进制文件得到原文本

double calculateOld();//计算原文本大小

double calculateNew();//计算压缩后的大小
