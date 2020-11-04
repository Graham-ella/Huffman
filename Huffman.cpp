#include "function.h"

//读取文件，获得文本的字符数和每个字符出现的次数

int main() {
	int n;
	int count[max] = { 0 };//记录每个字符出现的次数，max设为500
	char ch[max] = { ' ' };//记录出现的字符，max设为500
	n = readFromTxt(ch,count);//获得哈夫曼树的结点个数以及对应的权值
	for (int i = 0; ch[i] != '\0'; i++) {
		cout << ch[i] << "出现了" << count[i] << "次" << endl;
	}
	cout << endl;
	cout << endl;
	//创建哈夫曼树
    HuffmanT T = new HTNODE[2*n - 1];//创建2n-1大小的数组，用HuffmanT指向它
	
	CreateHT(T, n, count);//哈夫曼树创建完成
	
	cout << "哈夫曼树创建成功！" << endl;
	cout << endl;
	/*
	for (int i = 0; i < 2 * n - 1; i++) {
		cout << T[i].weight << " ";
	}
	*/

	//对字符进行编码
	HuffmanCode Hcode = new CodeNode[n];

	CharSetHuffmanEncoding(T, Hcode, n,ch);//对字符的编码已经完成

	cout << "字符编码完成！" << endl;
	cout << endl;

	
	for (int i = 0; i < n; i++) {
		cout <<Hcode[i].ch<<"的编码是："<<Hcode[i].bits << endl;
	}
	cout << endl;

	//开始对文件进行编码
	WriteCodeToFile(Hcode);//将编码写入"codeFile.txt"中

	ReadCodeToTxt(T, n,ch);//通过codeFile.txt打印原文本

	int addzero = completeCode();//记录添0的个数

	compressCodeTxt();//将01编码以8个一组以二进制形式压缩

	readBinaryTxt();//读取二进制文件，将其转化为01编码

	Result(T, n, ch,addzero);//将最终的文本存入result.txt中

	cout << "原文件压缩成功！" << endl;
	cout << endl;

	printf("压缩率为:%.2lf%%\n",calculateNew()/calculateOld()*100);//打印压缩率，保留小数点后两位
}
