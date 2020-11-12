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
void CBook::WriteData()//����д���ļ�
{
	ofstream ofile;// �ļ������  д����
	ofile.open("book.dat",ios::binary|ios::app);//�����ƴ洢  ���Խ�β׷�ӷ�ʽд��
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
	//��Ҫԭ��
		//seekg�ҵ��ļ�����Ҫɾ����λ�� ������Ҫɾ����������num1+num2+num1+num2�������Ϣд����ʱ�ļ�
		//seekg�ҵ�ɾ����Ϣ��λ�ã�����ʱ�ļ�д�ظ���
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
		//seekg���������ļ������ļ���ָ��λ��  ��ʾ���ļ���������ȡ����  ��λ��ȷ����  ��ios::beg��ʾ����ʼλ�ÿ�ʼ  ƫ��iCount*(num1+num1+num2+num2)���ֽ�
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
		//seekp��������ļ������ļ���ָ��λ��  ��ʾ���ļ��������ȡ����  ��λ��ȷ����  ��ios::beg��ʾ����ʼλ�ÿ�ʼ  ƫ��iCount*(num1+num1+num2+num2)���ֽ�
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
	ifstream ifile;// �ļ������� ������
	ifile.open("book.dat", ios::binary);
	try
	{
		ifile.seekg(iCount*(num1+num1+num2+num2),ios::beg); 
		ifile.read(cName,num1);
		if (ifile.tellg() > 0)//tellg��ȡ�ļ�����ָ���λ�� ���ļ�����
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