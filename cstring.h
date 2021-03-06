#include <string.h>

class CString{
public:

	CString();
	CString(const char Data);
	CString(const char* Data);
	CString(const CString& Data);

	CString& insert(int Pos, const char* Right);
	CString& insert(int Pos, const CString& Right);

	friend std::ostream& operator<<(std::ostream&, const CString&);
	friend const CString operator+(const CString& Left, const CString& Right);
	friend const CString operator+(const CString& Left, const char* Right);
	friend const CString operator+(const CString& Left, const char Right);
	friend bool operator==(const CString& Left, const CString& Right);
	friend bool operator==(const CString& Left, const char* Right);
	friend bool operator==(const CString& Left, const char Right);
	friend bool operator!=(const CString& Left, const CString& Right);
	friend bool operator!=(const CString& Left, const char* Right);
	friend bool operator!=(const CString& Left, const char Right);
	friend int  operator/=(const CString& Left, const CString& Right);
	friend int  operator/=(const CString& Left, const char* Right);
	friend int  operator/=(const CString& Left, const char Right);
    
	int sub_str(const CString& Right);
	int sub_str(const char* Right);
	int sub_str(const char Right);

	char* get_str() const;
	int   str_len() const;
	char  get_char(int index) const;
	void  change_str_len(int cnt) const;
	
    CString& operator=(const CString& Right)
	{
		Str_len = Right.str_len();
		Str_data = new char [Str_len];
		Str_data = Right.get_str();
		return *this;
	}
	
	CString& operator=(char* Right)
	{
		Str_len = strlen(Right);
		Str_data = new char [Str_len];
		Str_data = Right;
		return *this;
	}
	
	CString& operator=(char Right)
	{
		Str_len = 1;
		Str_data = new char [Str_len];
		Str_data = &Right;
		return *this;
	}
private:
	char* Str_data;
	mutable int Str_len;
	int Buf_len;
};


int kmp(const CString& Source, const CString& Pattern);
int max(int Num1, int Num2);