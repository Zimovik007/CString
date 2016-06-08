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
}

CString::CString(char Data)
{
	Str_len = 1;
	Str_data = new char [Str_len];
	Str_data = &Data;
}

CString::CString(char* Data)
{
	Str_len = strlen(Data);
	Str_data = new char [Str_len];
	Str_data = Data;
}

CString::CString(const CString& Data)
{
	Str_len = strlen(Data.get_str());
	Str_data = new char [Str_len];
	Str_data = Data.get_str();
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
    return CString(temp);
}
//CString + char*
const CString operator+(const CString& Left, const char* Right)
{
	char* temp = new char [Left.str_len() + strlen(Right)];
	strncat(temp, Left.get_str(), Left.str_len());
	strncat(temp, Right, strlen(Right));
    return CString(temp);
}
//CString + char
const CString operator+(const CString& Left, const char Right)
{
	char* temp = new char [Left.str_len() + 1];
	strncat(temp, Left.get_str(), Left.str_len());
	strncat(temp, &Right, 1);
    return CString(temp);
}
//CString == CString
bool operator==(const CString& Left, const CString& Right)
{
	if (!strcmp(Left.get_str(), Right.get_str()))
		return true;
	else
		return false;
}
//CString == char*
bool operator==(const CString& Left, const char* Right)
{
	if (!strcmp(Left.get_str(), Right))
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
	if (!strcmp(Left.get_str(), Right.get_str()))
		return false;
	else
		return true;
}
//CString != char*
bool operator!=(const CString& Left, const char* Right)
{
	if (!strcmp(Left.get_str(), Right))
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
int operator/=(const CString& Source, char* Pattern)
{
	CString Temp = Pattern;
	return kmp(Source, Temp);
}
//CString /= char
int operator/=(const CString& Source, char Pattern)
{
	CString Temp(&Pattern);
	return kmp(Source, Temp);
}

