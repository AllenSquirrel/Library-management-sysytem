#include "CBook.h"
#include<string>
#include<fstream>
#include<iostream>

using namespace std;


CBook::CBook()
{
}
CBook::CBook(char* cName, char* cIsbn, char* cPrice, char* cAuthor)
{
	strcpy_s(m_cName,cName);
	strcpy_s(m_cIsbn, cIsbn);
	strcpy_s(m_cPrice, cPrice);
	strcpy_s(m_cAuthor, cAuthor);
}

CBook::~CBook()
{
}

char* CBook::GetName()
{
	return m_cName;
}
void CBook::SetName(char* cName)
{
	strcpy_s(m_cName,cName);
}
char* CBook::GetIsbn()
{
	return m_cIsbn;
}
void CBook::SetIsbn(char* cIsbn)
{
	strcpy_s(m_cIsbn,cIsbn);
}
char* CBook::GetPrice()
{
	return m_cPrice;
}
void CBook::SetPrice(char* cPrice)
{
	strcpy_s(m_cPrice,cPrice);
}
char* CBook::GetAuthor()
{
	return m_cAuthor;
}
void CBook::SetAuthor(char* cAuthor)
{
	strcpy_s(m_cAuthor,cAuthor);
}
void CBook::WriteData()//数据写入文件
{
	ofstream ofile;// 文件输出流  写操作
	ofile.open("book.dat",ios::binary|ios::app);//二进制存储  且以结尾追加方式写入
	try
	{
		ofile.write(m_cName,num1);
		ofile.write(m_cIsbn, num1);
		ofile.write(m_cPrice, num2);
		ofile.write(m_cAuthor, num2);
	}
	catch(...)
	{
		throw"file error occurred";
		ofile.close();
	}
	ofile.close();
}
void CBook::DeleteData(int iCount)
{   
	//主要原理：
		//seekg找到文件中需要删除的位置 将其需要删除的整个（num1+num2+num1+num2）后的信息写入临时文件
		//seekg找到删除信息的位置，将临时文件写回覆盖
	long respos;
	int iDataCount = 0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[num1+num2+num1+num2];
	file.open("book.dat",ios::binary|ios::in|ios::out);
	tmpfile.open("temp.dat", ios::binary | ios::in|ios::out|ios::trunc);
	file.seekg(0,ios::end);
	respos = file.tellg();
	iDataCount = respos / (num1 + num1 + num2 + num2);
	if (iCount<0 && iCount>iDataCount)
	{
		throw"input number error";
	}
	else
	{
		//seekg设置输入文件流的文件流指针位置  表示从文件输入流获取数据  新位置确定：  由ios::beg表示从起始位置开始  偏移iCount*(num1+num1+num2+num2)个字节
		file.seekg(iCount*(num1+num1+num2+num2),ios::beg);
		for (int j = 0; j < (iDataCount - iCount); j++)
		{
			memset(cTempBuf,0,num1+num1+num2+num2);
			file.read(cTempBuf,num1+num1+num2+num2);
			tmpfile.write(cTempBuf,num1+num1+num2+num2);
		}
		file.close();
		tmpfile.seekg(0, ios::beg);
		ofile.open("book.dat");
		//seekp设置输出文件流的文件流指针位置  表示从文件输出流获取数据  新位置确定：  由ios::beg表示从起始位置开始  偏移iCount*(num1+num1+num2+num2)个字节
		ofile.seekp((iCount-1)*(num1 + num1 + num2 + num2), ios::beg);
		for (int i = 0; i < (iDataCount - iCount); i++)
		{
			memset(cTempBuf, 0, num1 + num1 + num2 + num2);
			tmpfile.read(cTempBuf, num1 + num1 + num2 + num2);
			file.write(cTempBuf, num1 + num1 + num2 + num2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}
void CBook::GetBookFromFile(int iCount)
{
	char cName[num1];
	char cIsbn[num1];
	char cPrice[num2];
	char cAuthor[num2];
	ifstream ifile;// 文件输入流 读操作
	ifile.open("book.dat", ios::binary);
	try
	{
		ifile.seekg(iCount*(num1+num1+num2+num2),ios::beg); 
		ifile.read(cName,num1);
		if (ifile.tellg() > 0)//tellg获取文件流读指针的位置 即文件长度
		{
			strcpy_s(m_cName,cName);
		}
		ifile.read(cIsbn, num1);
		if (ifile.tellg() > 0)
		{
			strcpy_s(m_cIsbn, cIsbn);
		}
		ifile.read(cPrice, num1);
		if (ifile.tellg() > 0)
		{
			strcpy_s(m_cPrice, cPrice);
		}
		ifile.read(cAuthor, num1);
		if (ifile.tellg() > 0)
		{
			strcpy_s(m_cAuthor, cAuthor);
		}
	}
	catch (...)
	{
		throw"file error occurred";
		ifile.close();
	}
	ifile.close();
}