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
}//判断字符之前是否被读到


int readFromTxt(char ch[max],int count[max]) {
	int number=0;
	const char* fileName = "wenben.txt";
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		exit(0);
	}
	char c;
	ifs >> noskipws;//强制读取每个字符
	while ((c = ifs.get()) != EOF) {
		
			if (charIsRead(c, ch) == -1) {//如果之前没有读到过该字符
				ch[number] = c;
				count[number]++;
				number++;
			}
			else {
				count[charIsRead(c, ch)]++;//如果读到过该字符，直接+1
			}
		
	}
	ifs.close();
	return number;
}//读取文本，记录出现的字符和出现次数


void InitHT(HuffmanT T,int n) {
	for (int i = 0; i < (2 * n - 1); i++)
	{
		T[i].lchild = -1;
		T[i].rchild = -1;
		T[i].parent = -1;
	}
}//初始化哈夫曼树，用来赋-1

void InputW(HuffmanT T, int n,int count[max]) {
	for (int i = 0; i < n; i++) {
		T[i].weight = (double)count[i];
	}//前n个有权值的根据权值赋值
	for (int i = n; i < 2 * n - 1; i++) {
		T[i].weight = 0;
	}//后n-1个先赋值为0
}//输入权值

void SelectMin(HuffmanT T, int j, int* p1, int* p2) {
	
	int min_temp1 = 0;
	int min_temp2 = 0;
	//先找到一个未被排过序的
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
	}//循环结束后我们将找到最小的权重值，下标为min_temp1

	//下面来寻找第二小的
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
	}//循环结束后找到第二小的

	*p1 = min_temp1;
	*p2 = min_temp2;

}//寻找两个权值最小的结点

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
}//构造哈夫曼树

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

}//哈夫曼编码的算法实现

string findCode(HuffmanCode Hcode, char c) {
	string rs = "";
	int i = 0;
	while (Hcode[i].ch != c) {
		i++;
	}
	rs = Hcode[i].bits;
	return rs;
}//得到字符c对应的哈夫曼编码

void WriteCodeToFile(HuffmanCode Hcode) {
	const string fileName = "wenben.txt";
	const string newFileName = "codeFile.txt";
	string rs;
	ifstream ifs;
	ofstream ofs;
	ifs.open(fileName, ios::in);
	ofs.open(newFileName, ios::out);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		exit(0);
	}
	char c;
	ifs >> noskipws;//强制读取每个字符
	while ((c = ifs.get()) != EOF) {//未读到文件末
		rs = findCode(Hcode, c);
		ofs << rs;
	}
	ifs.close();
	ofs.close();
}//将文本对应的01编码存入文件codeFile.txt中


//将01码补全，凑成8的倍数，返回增加的0的个数
int completeCode() {
	const string file = "codeFile.txt";
	const string newfile = "newCodeFile.txt";
	ifstream ifs;
	ifs.open(file, ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
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
}//添0操作，返回增添的个数


void compressCodeTxt() {
	FILE* fp_r, * fp_w;
	fopen_s(&fp_r,"newCodeFile.txt", "rb");
	fopen_s(&fp_w,"compressCode.txt", "wb");
	if (fp_r == NULL)
	{
		cout << "读入文件read_to_compress.txt失败！" << endl;
		exit(0);
	}
	if (fp_w == NULL)
	{
		cout << "写入文件write_in_hufmancode.txt失败!" << endl;
		exit(0);
	}
	int count = 0;
	char c = '\0';
	while (!feof(fp_r)) {
		count++;
		if (count != 8) {
			if (fgetc(fp_r) == '1') {
				c = (c << 1) | 1;//如果读到的是1，左移一位，与1进行或操作
			}
			else {
				c = c << 1;//如果读到的是0，左移一位
			}
		}
		else {
			if (fgetc(fp_r) == '1') {
				c = (c << 1) | 1;//如果读到的是1，左移一位，与1进行或操作
			}
			else {
				c = c << 1;//如果读到的是0，左移一位
			}
			fputc(c, fp_w);
			c = '\0';
			count = 0;
		}
	}
	fclose(fp_r);
	fclose(fp_w);
}//将01码8个一组以二进制形式存入文件中

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
}//读取二进制文件


void ReadCodeToTxt(HuffmanT T, int n, char ch[max]) {
	const string fileName = "codeFile.txt";
	const string newTxt = "codeToTxt.txt";

	int flag = 2 * n - 2;

	ifstream ifs;
	ofstream ofs;
	ifs.open(fileName, ios::in);
	ofs.open(newTxt, ios::out);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
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
}//从存01码的文件中得到原文本


//将char c转化为二进制形式
string change(char c)
{
	string data;
	for (int i = 0; i < 8; i++)
	{
		//  data+=c&(0x01<<i);
		if ((c >> (i - 1)) & 0x01 == 1)//按位与操作
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
		cout << "文件打开失败" << endl;
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

	for (int i = 0; i < result.length(); i++) {//解码的过程
		
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
}//从二进制文件得到原文本

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
	cout << "原文本的大小为：" << oldSize << " 字节" << endl;
	
	return oldSize;
	
}//计算原文本大小


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
	cout << "压缩后的文本大小为：" << newSize << " 字节" << endl;
	return newSize;
}//计算压缩后文本大小

