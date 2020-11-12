#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<iomanip>
#include"CBook.h"

#define CMD_COLS 80
#define CMD_LINES 25

using namespace std;

void SetScreenGrid();//������Ļ��ʾ����������
void ClearSreen();//�����Ļ��Ϣ
void SetSysCaption(const char*pText);//���ô��������
void ShowWelcom();//��ʾ��ӭ��Ϣ
void ShowRootMenu();//��ʾ��ʼ�˵�
void WaitView(int iCurPage);//�������ʱ�ȴ��û�����
void WaitUser();//�ȴ��û�����
void GuideInput();//ʹ�������ͼ����Ϣ
int GetSelect();//����û��˵�ѡ��
long GetFileLength(ifstream &ifs);//��ȡ�ļ�����
void ViewData(int iSelPage=1);//����������¼
void DeleteBookFromFile();//���ļ���ɾ��ͼ����Ϣ
void mainloop();//��ѭ��

void SetScreenGrid()//������Ļ��ʾ����������
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf,"mode cols=%d lines=%d",CMD_COLS,CMD_LINES);
	system(sysSetBuf);
}
void ClearSreen()//�����Ļ��Ϣ
{
	system("cls");
}
void SetSysCaption(const char*pText)//���ô��������
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
void ShowWelcom()//��ʾ��ӭ��Ϣ
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "***********************" << endl;
	cout << setw(35);
	cout << "ͼ�����ϵͳ" << endl;
	cout << setw(40);
	cout << "***********************" << endl;
}
void ShowRootMenu()//��ʾ��ʼ�˵�
{
	cout << setw(40);
	cout << "��ѡ����" << endl;
	cout << endl;
	cout << setw(40);
	cout << "1  ���ͼ��" << endl;
	cout << endl;
	cout << setw(40);
	cout << "2  ���ȫ��" << endl;
	cout << endl;
	cout << setw(40);
	cout << "3  ɾ��ͼ��" << endl;
}
void WaitView(int iCurPage)//�������ʱ�ȴ��û�����
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
void WaitUser()//�ȴ��û�����
{
	int iInputPage = 0;
	cout << "enter�������˵�����q�˳�" << endl;
	char buff[256];
	gets_s(buff);//ͨ��gets���������ַ�  ���Ϊ��q�����˳�
	if (buff[0] == 'q')
		system("exit");
}
void GuideInput()//ʹ�������ͼ����Ϣ
{
	char inName[num1];
	char inIsbn[num1];
	char inPrice[num2];
	char inAuthor[num2];

	cout << "��������" << endl;
	cin >> inName;
	cout << "����ISDN" << endl;
	cin >> inIsbn;
	cout << "����۸�" << endl;
	cin >> inPrice;
	cout << "��������" << endl;
	cin >> inAuthor;
	CBook book(inName,inIsbn,inPrice,inAuthor);
	book.WriteData();//�������ͼ����Ϣд���ļ�
	cout << "write finish" << endl;
	WaitUser();//�ȴ��û��˳�������һ��
}
int GetSelect()//����û��˵�ѡ��
{
	char buff[256];
	gets_s(buff);
	return atoi(buff);//gets�����û������ַ�  atoi���ַ�ת��Ϊint����
}
long GetFileLength(ifstream &ifs)//��ȡ�ļ�����
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();//��õ�ǰλ��
	ifs.seekg(0,ios::end);//������ָ��ָ���ļ�ĩβ
	respos = ifs.tellg();//��ȡ�����ļ����ȴ�С
	ifs.seekg(tmppos, ios::beg);//�ָ���ǰλ��
	return respos;
}
void ViewData(int iSelPage)//����������¼
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
	iFileLength = GetFileLength(ifile);//��ȡ�ļ����ȴ�С
	iDataCount = iFileLength / (num1 + num1 + num2 + num2);//ͼ����Ŀ��� ���Ը����ļ����� �͹̶���С�Ĵ洢��Ԫ����õ�
	if (iDataCount >= 1)
		bindex = true;//˵������ͼ����Ϣ�������
	iPage = iDataCount / 20 + 1;//ÿһҳ�洢20��ͼ���¼

	ClearSreen();
	cout << "���м�¼" << iDataCount << " ";
	cout << "����ҳ��" << iPage << " ";
	cout << "��ǰҳ��" << iCurPage << " ";
	cout << "n��ʾ��һҳ��m����" << endl ;
	cout << setw(5) << "Index";//setw�����ֶο��
	cout << setw(22) << "Name" << setw(22) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (num1 + num1 + num2 + num2), ios::beg);//���Զ�λ����ǰ����ͼ����ϢĿ¼
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, num1);//��ʼ��Ϊ�� ��0
				memset(inIsbn, 0, num1);
				memset(inPrice, 0, num2);
				memset(inAuthor, 0, num2);
				if (bindex)//ͼ����Ϣ��Ϊ��
				{
					cout << setw(5) << (iCurPage - 1) * 20 + 1;//��ӡͼ��������Ϣ
					ifile.read(inName,num1);
					cout << setw(24) << inName;//d�ļ���ȡ����ӡͼ����
					ifile.read(inIsbn, num1);
					cout << setw(24) << inIsbn;//d�ļ���ȡ����ӡisbn
					ifile.read(inPrice, num2);
					cout << setw(12) << inPrice;//d�ļ���ȡ����ӡ�۸�
					ifile.read(inAuthor, num2);
					cout << setw(12) << inAuthor;//d�ļ���ȡ����ӡ������
					cout << endl;
					if (ifile.tellg() < 0)//�ж��Ƿ��ļ�ĩβ
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
	if (iCurPage < iPage)//����1ҳ
	{
		iCurPage++;
		WaitView(iCurPage);//ͨ��waitview�н��ܡ�n���ַ����л�ҳ
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}
void DeleteBookFromFile()//���ļ���ɾ��ͼ����Ϣ
{
	int iDelcount;
	cout << "input delete index" << endl;
	cin >> iDelcount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelcount);
	cout << "delete finish" << endl;
	WaitUser();
}
void mainloop()//��ѭ��
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
	SetScreenGrid();//��Ļ����
	SetSysCaption("ͼ�����ϵͳ");//���ñ�����
	mainloop();//��ѭ��
	return 0;
}