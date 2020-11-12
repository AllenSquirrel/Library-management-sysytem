#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<iomanip>
#include"CBook.h"

#define CMD_COLS 80
#define CMD_LINES 25

using namespace std;

void SetScreenGrid();//设置屏幕显示行数和列数
void ClearSreen();//清除屏幕信息
void SetSysCaption(const char*pText);//设置窗体标题栏
void ShowWelcom();//显示欢迎信息
void ShowRootMenu();//显示开始菜单
void WaitView(int iCurPage);//浏览数据时等待用户操作
void WaitUser();//等待用户操作
void GuideInput();//使用向导添加图书信息
int GetSelect();//获得用户菜单选择
long GetFileLength(ifstream &ifs);//获取文件长度
void ViewData(int iSelPage=1);//浏览所有书记录
void DeleteBookFromFile();//从文件中删除图书信息
void mainloop();//主循环

void SetScreenGrid()//设置屏幕显示行数和列数
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf,"mode cols=%d lines=%d",CMD_COLS,CMD_LINES);
	system(sysSetBuf);
}
void ClearSreen()//清除屏幕信息
{
	system("cls");
}
void SetSysCaption(const char*pText)//设置窗体标题栏
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
void ShowWelcom()//显示欢迎信息
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "***********************" << endl;
	cout << setw(35);
	cout << "图书管理系统" << endl;
	cout << setw(40);
	cout << "***********************" << endl;
}
void ShowRootMenu()//显示开始菜单
{
	cout << setw(40);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(40);
	cout << "1  添加图书" << endl;
	cout << endl;
	cout << setw(40);
	cout << "2  浏览全部" << endl;
	cout << endl;
	cout << setw(40);
	cout << "3  删除图书" << endl;
}
void WaitView(int iCurPage)//浏览数据时等待用户操作
{
	char buff[256];
	gets_s(buff);
	if (buff[0] == 'q')
		system("exit");
	if (buff[0] == 'm')
		mainloop();
	if (buff[0] == 'n')
		ViewData(iCurPage);
}
void WaitUser()//等待用户操作
{
	int iInputPage = 0;
	cout << "enter返回主菜单，按q退出" << endl;
	char buff[256];
	gets_s(buff);//通过gets接受输入字符  如果为‘q’则退出
	if (buff[0] == 'q')
		system("exit");
}
void GuideInput()//使用向导添加图书信息
{
	char inName[num1];
	char inIsbn[num1];
	char inPrice[num2];
	char inAuthor[num2];

	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入ISDN" << endl;
	cin >> inIsbn;
	cout << "输入价格" << endl;
	cin >> inPrice;
	cout << "输入作者" << endl;
	cin >> inAuthor;
	CBook book(inName,inIsbn,inPrice,inAuthor);
	book.WriteData();//将输入的图书信息写入文件
	cout << "write finish" << endl;
	WaitUser();//等待用户退出返回上一级
}
int GetSelect()//获得用户菜单选择
{
	char buff[256];
	gets_s(buff);
	return atoi(buff);//gets接受用户输入字符  atoi将字符转换为int类型
}
long GetFileLength(ifstream &ifs)//获取文件长度
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();//获得当前位置
	ifs.seekg(0,ios::end);//输入流指针指向文件末尾
	respos = ifs.tellg();//获取整个文件长度大小
	ifs.seekg(tmppos, ios::beg);//恢复当前位置
	return respos;
}
void ViewData(int iSelPage)//浏览所有书记录
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[num1];
	char inIsbn[num1];
	char inPrice[num2];
	char inAuthor[num2];
	bool bindex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat",ios::binary);
	iFileLength = GetFileLength(ifile);//获取文件长度大小
	iDataCount = iFileLength / (num1 + num1 + num2 + num2);//图书条目序号 可以根据文件长度 和固定大小的存储单元计算得到
	if (iDataCount >= 1)
		bindex = true;//说明存在图书信息可以浏览
	iPage = iDataCount / 20 + 1;//每一页存储20条图书记录

	ClearSreen();
	cout << "共有记录" << iDataCount << " ";
	cout << "共有页数" << iPage << " ";
	cout << "当前页数" << iCurPage << " ";
	cout << "n显示下一页，m返回" << endl ;
	cout << setw(5) << "Index";//setw设置字段宽度
	cout << setw(22) << "Name" << setw(22) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (num1 + num1 + num2 + num2), ios::beg);//可以定位到当前索引图书信息目录
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, num1);//初始化为空 即0
				memset(inIsbn, 0, num1);
				memset(inPrice, 0, num2);
				memset(inAuthor, 0, num2);
				if (bindex)//图书信息不为空
				{
					cout << setw(5) << (iCurPage - 1) * 20 + 1;//打印图书索引信息
					ifile.read(inName,num1);
					cout << setw(24) << inName;//d文件读取并打印图书名
					ifile.read(inIsbn, num1);
					cout << setw(24) << inIsbn;//d文件读取并打印isbn
					ifile.read(inPrice, num2);
					cout << setw(12) << inPrice;//d文件读取并打印价格
					ifile.read(inAuthor, num2);
					cout << setw(12) << inAuthor;//d文件读取并打印作者名
					cout << endl;
					if (ifile.tellg() < 0)//判断是否到文件末尾
					{
						bindex = false;
					}
					else
					{
						bindex = true;
					}

				}
			}
		}
	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw"file error occured";
		ifile.close();
	}
	if (iCurPage < iPage)//多于1页
	{
		iCurPage++;
		WaitView(iCurPage);//通过waitview中接受‘n’字符进行换页
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}
void DeleteBookFromFile()//从文件中删除图书信息
{
	int iDelcount;
	cout << "input delete index" << endl;
	cin >> iDelcount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelcount);
	cout << "delete finish" << endl;
	WaitUser();
}
void mainloop()//主循环
{
	ShowWelcom();
	while (1)
	{
		ClearSreen();
		ShowWelcom();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearSreen();
			GuideInput();
			break;
		case 2:
			ClearSreen();
			ViewData();
			break;
		case 3:
			ClearSreen();
			DeleteBookFromFile();
			break;
		}
	}

}
int main()
{
	SetScreenGrid();//屏幕设置
	SetSysCaption("图书管理系统");//设置标题栏
	mainloop();//主循环
	return 0;
}