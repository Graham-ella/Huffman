#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>

int charIsRead(char c, char* ch) {
	int count = 0;
	while (*ch != '\0') {
		if (c == *ch) {
			return count;
		}
		ch++;
		count++;
	}
	return -1;
}//�ж��ַ�֮ǰ�Ƿ񱻶���


int readFromTxt(char ch[max],int count[max]) {
	int number=0;
	const char* fileName = "wenben.txt";
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	char c;
	ifs >> noskipws;//ǿ�ƶ�ȡÿ���ַ�
	while ((c = ifs.get()) != EOF) {
		
			if (charIsRead(c, ch) == -1) {//���֮ǰû�ж��������ַ�
				ch[number] = c;
				count[number]++;
				number++;
			}
			else {
				count[charIsRead(c, ch)]++;//������������ַ���ֱ��+1
			}
		
	}
	ifs.close();
	return number;
}//��ȡ�ı�����¼���ֵ��ַ��ͳ��ִ���


void InitHT(HuffmanT T,int n) {
	for (int i = 0; i < (2 * n - 1); i++)
	{
		T[i].lchild = -1;
		T[i].rchild = -1;
		T[i].parent = -1;
	}
}//��ʼ������������������-1

void InputW(HuffmanT T, int n,int count[max]) {
	for (int i = 0; i < n; i++) {
		T[i].weight = (double)count[i];
	}//ǰn����Ȩֵ�ĸ���Ȩֵ��ֵ
	for (int i = n; i < 2 * n - 1; i++) {
		T[i].weight = 0;
	}//��n-1���ȸ�ֵΪ0
}//����Ȩֵ

void SelectMin(HuffmanT T, int j, int* p1, int* p2) {
	
	int min_temp1 = 0;
	int min_temp2 = 0;
	//���ҵ�һ��δ���Ź����
	for (int k = 0; k <= j; k++) {
		if (T[k].parent == -1) {
			min_temp1 = k;
			break;
		}
	}
	
	int i = 0;
	while (i <= j) {
		if (T[i].parent == -1) {
			if (T[i].weight < T[min_temp1].weight) {
				min_temp1 = i;
			}
		}
		i++;
	}//ѭ�����������ǽ��ҵ���С��Ȩ��ֵ���±�Ϊmin_temp1

	//������Ѱ�ҵڶ�С��
	for (int k = 0; k <= j; k++) {
		if (T[k].parent == -1&&k!=min_temp1) {
			min_temp2 = k;
			break;
		}
	}
	i = 0;
	while (i <= j) {
		if (T[i].parent == -1 && i != min_temp1) {
			if (T[i].weight < T[min_temp2].weight) {
				min_temp2 = i;
			}
		}
		i++;
	}//ѭ���������ҵ��ڶ�С��

	*p1 = min_temp1;
	*p2 = min_temp2;

}//Ѱ������Ȩֵ��С�Ľ��

void CreateHT(HuffmanT T, int n,int count[max]) {
	int i, p1, p2;
	InitHT(T, n);
	InputW(T, n, count);
	for (int i = n; i < 2*n - 1; i++) {
		SelectMin(T, i - 1, &p1, &p2);
		T[p1].parent = i;
		T[p2].parent = i;
		T[i].lchild = p1;
		T[i].rchild = p2;
		T[i].weight = T[p1].weight + T[p2].weight;

	}
}//�����������

void CharSetHuffmanEncoding(HuffmanT T, HuffmanCode Hcode, int n,char ch[max]) {
	int c, p, i;
	char cd[max + 1];
	int start;
	cd[max] = '\0';
	for (i = 0; i < n; i++) {
		Hcode[i].ch = ch[i];
		start = max;
		c = i;
		while ((p = T[c].parent) >= 0) {
			cd[--start] = (T[p].lchild == c) ? '0' : '1';
			c = p;
		}
		strcpy_s(Hcode[i].bits, &cd[start]);
	}

}//������������㷨ʵ��

string findCode(HuffmanCode Hcode, char c) {
	string rs = "";
	int i = 0;
	while (Hcode[i].ch != c) {
		i++;
	}
	rs = Hcode[i].bits;
	return rs;
}//�õ��ַ�c��Ӧ�Ĺ���������

void WriteCodeToFile(HuffmanCode Hcode) {
	const string fileName = "wenben.txt";
	const string newFileName = "codeFile.txt";
	string rs;
	ifstream ifs;
	ofstream ofs;
	ifs.open(fileName, ios::in);
	ofs.open(newFileName, ios::out);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	char c;
	ifs >> noskipws;//ǿ�ƶ�ȡÿ���ַ�
	while ((c = ifs.get()) != EOF) {//δ�����ļ�ĩ
		rs = findCode(Hcode, c);
		ofs << rs;
	}
	ifs.close();
	ofs.close();
}//���ı���Ӧ��01��������ļ�codeFile.txt��


//��01�벹ȫ���ճ�8�ı������������ӵ�0�ĸ���
int completeCode() {
	const string file = "codeFile.txt";
	const string newfile = "newCodeFile.txt";
	ifstream ifs;
	ifs.open(file, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	char c;
	int number=0;
	int addzero = 0;
	ofstream ofs;
	ofs.open(newfile, ios::out);
	while ((c = ifs.get()) != EOF) {
		number++;
		ofs << c;
	}
	while (number % 8 != 0) {
		ofs << '0';
		addzero++;
		number++;
	}
	ifs.close();
	ofs.close();
	return addzero;
}//��0��������������ĸ���


void compressCodeTxt() {
	FILE* fp_r, * fp_w;
	fopen_s(&fp_r,"newCodeFile.txt", "rb");
	fopen_s(&fp_w,"compressCode.txt", "wb");
	if (fp_r == NULL)
	{
		cout << "�����ļ�read_to_compress.txtʧ�ܣ�" << endl;
		exit(0);
	}
	if (fp_w == NULL)
	{
		cout << "д���ļ�write_in_hufmancode.txtʧ��!" << endl;
		exit(0);
	}
	int count = 0;
	char c = '\0';
	while (!feof(fp_r)) {
		count++;
		if (count != 8) {
			if (fgetc(fp_r) == '1') {
				c = (c << 1) | 1;//�����������1������һλ����1���л����
			}
			else {
				c = c << 1;//�����������0������һλ
			}
		}
		else {
			if (fgetc(fp_r) == '1') {
				c = (c << 1) | 1;//�����������1������һλ����1���л����
			}
			else {
				c = c << 1;//�����������0������һλ
			}
			fputc(c, fp_w);
			c = '\0';
			count = 0;
		}
	}
	fclose(fp_r);
	fclose(fp_w);
}//��01��8��һ���Զ�������ʽ�����ļ���

void readBinaryTxt() {
	ifstream ifs;
	ifs.open("compressCode.txt", ios::in || ios::binary);
	ofstream ofs;
	ofs.open("binarycodeToNewTxt.txt",ios::out);
	char c;
	//ifs.read((char*)&c, sizeof(c));
	
	while (ifs.read((char*)&c, sizeof(c))) {
		ofs << change(c);
	}
	ifs.close();
	ofs.close();
}//��ȡ�������ļ�


void ReadCodeToTxt(HuffmanT T, int n, char ch[max]) {
	const string fileName = "codeFile.txt";
	const string newTxt = "codeToTxt.txt";

	int flag = 2 * n - 2;

	ifstream ifs;
	ofstream ofs;
	ifs.open(fileName, ios::in);
	ofs.open(newTxt, ios::out);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	char c;
	string rs;
	while ((c = ifs.get()) != EOF) {

		if (c == '0') {
			flag = T[flag].lchild;
			if (T[flag].lchild == -1 && T[flag].rchild == -1) {
				rs = ch[flag];
				ofs << rs;
				flag = 2 * n - 2;
				rs = "";
			}
		}
		else if (c == '1') {
			flag = T[flag].rchild;
			if (T[flag].lchild == -1 && T[flag].rchild == -1) {
				rs = ch[flag];
				ofs << rs;
				flag = 2 * n - 2;
				rs = "";
			}
		}

	}
	ifs.close();
	ofs.close();
}//�Ӵ�01����ļ��еõ�ԭ�ı�


//��char cת��Ϊ��������ʽ
string change(char c)
{
	string data;
	for (int i = 0; i < 8; i++)
	{
		//  data+=c&(0x01<<i);
		if ((c >> (i - 1)) & 0x01 == 1)//��λ�����
		{
			data += "1";
		}
		else
		{
			data += "0";
		}

	}
	for (int a = 1; a < 5; a++)
	{
		char x = data[a];
		data[a] = data[8 - a];
		data[8 - a] = x;

	}

	return data;
}


void Result(HuffmanT T, int n, char ch[max],int addzero) {
	const string fileName = "binarycodeToNewTxt.txt";
	const string newTxt = "result.txt";
	ifstream ifs;
	ofstream ofs;
	ifs.open(fileName, ios::in);
	ofs.open(newTxt, ios::out);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}
	string result = "";
	char c;
	while ((c = ifs.get()) != EOF) {
		result = result + c;
	}
	for (int i = 0; i < addzero; i++) {
		result = result.substr(0, result.length() - 1);
	}
	ifs.close();

	
	int flag = 2 * n - 2;
	string rs = "";

	for (int i = 0; i < result.length(); i++) {//����Ĺ���
		
		if (result[i] == '0') {
			flag = T[flag].lchild;
			if (T[flag].lchild == -1 && T[flag].rchild == -1) {
				rs = ch[flag];
				ofs << rs;
				flag = 2 * n - 2;
				rs = "";
			}
		}

		else if (result[i] == '1') {
			flag = T[flag].rchild;
			if (T[flag].lchild == -1 && T[flag].rchild == -1) {
				rs = ch[flag];
				ofs << rs;
				flag = 2 * n - 2;
				rs = "";
			}
		}

	}
	ofs.close();
}//�Ӷ������ļ��õ�ԭ�ı�

double calculateOld() {
	
	string oldwenben = "wenben.txt";
	ifstream ifs;
	ifs.open(oldwenben, ios::in);
	double oldSize = 0;
	char c;
	while ((c = ifs.get()) != EOF) {
		oldSize++;
	}
	ifs.close();
	cout << "ԭ�ı��Ĵ�СΪ��" << oldSize << " �ֽ�" << endl;
	
	return oldSize;
	
}//����ԭ�ı���С


double calculateNew() {
	string newwenben = "compressCode.txt";
	ifstream newifs;
	newifs.open(newwenben, ios::in);
	double newSize = 0;
	char ch;
	while ((ch = newifs.get()) != EOF) {
		newSize++;
	}
	newifs.close();
	cout << "ѹ������ı���СΪ��" << newSize << " �ֽ�" << endl;
	return newSize;
}//����ѹ�����ı���С

