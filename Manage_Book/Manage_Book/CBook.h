#pragma once
#define num1 128
#define num2 64
class CBook
{
public:
	CBook();//无参构造
	CBook(char* cName,char* cIsbn,char* cPrice,char* cAuthor);//有参构造
	~CBook();
	char* GetName();
	void SetName(char* cName);
	char* GetIsbn();
	void SetIsbn(char* cIsbn);
	char* GetPrice();
	void SetPrice(char* cPrice);
	char* GetAuthor();
	void SetAuthor(char* cAuthor);
	void WriteData();
	void DeleteData(int iCount);
	void GetBookFromFile(int iCount);

protected:
	char m_cName[num1];
	char m_cIsbn[num1];
	char m_cPrice[num2];
	char m_cAuthor[num2];
};

