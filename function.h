#pragma once
#include <iostream>
using namespace std;
const int max = 500;

typedef struct node {
	double weight;
	int lchild;
	int rchild;
	int parent;
}HTNODE;//���

typedef struct codenode {
	char ch;//�洢��������ַ�
	char bits[max + 1];//�ַ���Ӧ�ı���
}CodeNode;


typedef HTNODE* HuffmanT;

typedef CodeNode* HuffmanCode;

int readFromTxt(char ch[max],int count[max]);//��ȡ�ı�����¼���ֵ��ַ��ͳ��ִ���

int charIsRead(char c, char* ch);//�ж��ַ�֮ǰ�Ƿ񱻶���

void InitHT(HuffmanT T,int n);//��ʼ����������

void InputW(HuffmanT T,int n,int count[max]);//����Ȩֵ

void SelectMin(HuffmanT T, int j, int* p1, int* p2);//Ѱ������Ȩֵ��С�Ľ��

void CreateHT(HuffmanT T,int n,int count[max]);//�����������

void CharSetHuffmanEncoding(HuffmanT T, HuffmanCode Hcode, int n,char ch[max]);//������������㷨ʵ��

string findCode(HuffmanCode Hcode, char c);//�õ��ַ�c��Ӧ�Ĺ���������

void WriteCodeToFile(HuffmanCode Hcode);//���ı���Ӧ��01��������ļ���

int completeCode();//��0��������������ĸ���

void compressCodeTxt();//��01��8��һ���Զ�������ʽ�����ļ���

string change(char c);//��ȡ������

void readBinaryTxt();//��ȡ�������ļ�

void ReadCodeToTxt(HuffmanT T,int n, char ch[max]);//�Ӵ�01����ļ��еõ�ԭ�ı�

void Result(HuffmanT T, int n, char ch[max],int addzero);//�Ӷ������ļ��õ�ԭ�ı�

double calculateOld();//����ԭ�ı���С

double calculateNew();//����ѹ����Ĵ�С
