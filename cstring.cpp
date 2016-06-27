#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string.h>

#include "cstring.h"

using namespace std;

int kmp(const CString& Source, const CString& Pattern)
{
	//Алгоритм Кнута-Морриса-Пратта нахождения подстроки в строке 
	//(возвращает индекс элемента, с которого начинается подстрока)
	int k = 0;
	int Pref_array[Source.str_len()];
	for (int i = 0; i < Source.str_len(); i++)
		Pref_array[i] = 0;
	for (int i = 1; i < Source.str_len(); i++)
	{
		k = Pref_array[i-1];
		while ((k > 0) && (Source.get_char(k) != Source.get_char(i)))
			k = Pref_array[k-1];
		if (Source.get_char(k) == Source.get_char(i))
			k++;
		Pref_array[i] = k;
	}
	int index = -1; // в случае отсутсвия подстроки вернет "-1"
	k = 0;
	for (int i = 0; i < Source.str_len(); i++)
	{
		while ((k > 0) && (Pattern.get_char(k) != Source.get_char(i)))
			k = Pref_array[k-1];
		if (Pattern.get_char(k) == Source.get_char(i))
			k++;
		if (k == Pattern.str_len())
		{
			index = i - Pattern.str_len() + 1;
			break;
		}
	}
	return index;
}

CString::CString()
{
	Str_len = 0;
	Buf_len = 10;
	Str_data = new char[Buf_len];
}

CString::CString(const char Data)
{
	Buf_len = 10;
	Str_len = 1;
	Str_data = new char[Buf_len];
	Str_data = strncpy(Str_data, &Data, Str_len);
	Str_data = Str_data + '\0';
}

CString::CString(const char* Data)
{
	Str_len = strlen(Data);
	Buf_len = Str_len * 2;
	Str_data = new char [Buf_len];
	Str_data = strncpy(Str_data, Data, Str_len);
	Str_data = Str_data + '\0';
}

CString::CString(const CString& Data)
{
	Str_len = strlen(Data.get_str());
	Buf_len = Str_len * 2;
	Str_data = new char [Buf_len];
	Str_data = strncpy(Str_data, Data.get_str(), Str_len);
	Str_data = Str_data + '\0';
}

char* CString::get_str() const
{
	return Str_data;
}

int CString::str_len() const
{
	return Str_len;
}

char CString::get_char(int index) const
{
	return Str_data[index];
}

void CString::change_str_len(int cnt) const
{
	Str_len += cnt;
}

std::ostream& operator<<(std::ostream& out, const CString& Data)
{
    out << Data.get_str();
    return out;
}
//CString + CString
const CString operator+(const CString& Left, const CString& Right)
{
	char* temp = new char [Left.str_len() + Right.str_len()];
	strncat(temp, Left.get_str(), Left.str_len());
	strncat(temp, Right.get_str(), Right.str_len());
	Left.change_str_len(Right.str_len());
    return CString(temp);
}
//CString + char*
const CString operator+(const CString& Left, const char* Right)
{
	char* temp = new char [Left.str_len() + strlen(Right)];
	strncat(temp, Left.get_str(), Left.str_len());
	strncat(temp, Right, strlen(Right));
	Left.change_str_len(strlen(Right));
    return CString(temp);
}
//CString + char
const CString operator+(const CString& Left, const char Right)
{
	char* temp = new char [Left.str_len() + 1];
	strncat(temp, Left.get_str(), Left.str_len());
	strncat(temp, &Right, 1);
	Left.change_str_len(1);
    return CString(temp);
}
//CString == CString
bool operator==(const CString& Left, const CString& Right)
{
	if (strcmp(Left.get_str(), Right.get_str()) == 0)
		return true;
	else
		return false;
}
//CString == char*
bool operator==(const CString& Left, const char* Right)
{
	if (strcmp(Left.get_str(), Right) == 0)
		return true;
	else
		return false;
}
//CString == char
bool operator==(const CString& Left, const char Right)
{
	return ((Left.str_len() == 1) && (Left.get_char(0) == Right));	
}
//CString != CString
bool operator!=(const CString& Left, const CString& Right)
{
	if (strcmp(Left.get_str(), Right.get_str()) == 0)
		return false;
	else
		return true;
}
//CString != char*
bool operator!=(const CString& Left, const char* Right)
{
	if (strcmp(Left.get_str(), Right) == 0)
		return false;
	else
		return true;
}
//CString != char
bool operator!=(const CString& Left, const char Right)
{
	return !((Left.str_len() == 1) && (Left.get_char(0) == Right));	
}
//CString /= CString
int operator/=(const CString& Source, const CString& Pattern)
{
	return kmp(Source, Pattern);
}
//CString /= char*
int operator/=(const CString& Source, const char* Pattern)
{
	CString Temp = Pattern;
	return kmp(Source, Temp);
}
//CString /= char
int operator/=(const CString& Source, const char Pattern)
{
	char* Str = new char[1];
	Str[0] = Pattern;
	CString Temp = Str;
	return kmp(Source, Temp);
}
//CString /= CString
int CString::sub_str(const CString& Pattern)
{
	return kmp(Str_data, Pattern);
}
//CString /= char*
int CString::sub_str(const char* Pattern)
{
	CString Temp = Pattern;
	return kmp(Str_data, Temp);
}
//CString /= char
int CString::sub_str(const char Pattern)
{
	char* Str = new char[1];
	Str[0] = Pattern;
	CString Temp = Str;
	return kmp(Str_data, Temp);
}

CString& CString::insert(int Pos, const char* Right)
{
	return insert(Pos, CString(Right));
}

CString& CString::insert(int Pos, const CString& Right)
{
	if (Str_len + Right.str_len() > Buf_len)
	{
		Buf_len = max((Str_len + Right.str_len()) * 2, Buf_len * 2);
		char* Temp = new char[Buf_len];
		Temp = strncpy(Temp, Str_data, Str_len);
		swap(Temp, Str_data);
	}

	for (int i = Str_len; i > Pos + Right.str_len(); i--)
	{
		Str_data[i] = Str_data[i-1];
	}
	for (int i = Pos, j = 0; i < Pos + Right.str_len(); i++, j++)
	{
		Str_data[i] = Right.get_str()[j];
	}
	return *this;
}

int max(int num1, int num2)
{
	if (num1 > num2)
		return num1;
	return num2;
}