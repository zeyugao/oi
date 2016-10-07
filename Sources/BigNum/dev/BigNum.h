#pragma once
#define MAXN 9999
#define DLEN 4

class BigNum
{
private:
	//在这个class中数据的储存方式：每len(MAXN+1)的数归为一个int，充分利用int的取值，避免了每个位都用一个int
	int s[500];
	int len;
public:
	BigNum() { len = 0; memset(s, 0, sizeof(s)); };
	BigNum(const int);
	BigNum(const char*);
	BigNum(const BigNum&);
	BigNum &operator=(const BigNum&);
	friend std::istream& operator >> (std::istream&, BigNum&);
	friend std::ostream& operator << (std::ostream&, BigNum&);

	BigNum operator+(const BigNum&)const;
	BigNum operator-(const BigNum &)const;
	BigNum operator*(const BigNum &)const;
	BigNum operator/(const BigNum &)const;

	BigNum operator^(const BigNum &)const;
	int operator%(const int &)const;
	bool operator>(const BigNum &)const;
	bool operator<(const BigNum &)const;

	~BigNum();
};

