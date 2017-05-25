#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
const int MAXSIZE = 10000;
struct add
{
	int s[MAXSIZE];
	add() { memset(s, 0, sizeof(s)); }
	add(int number) { *this = number; }
	add(const char* number) { *this = number; }
	void put();
	add mul(int d);
	void del();
	void init() { memset(s, 0, sizeof(s)); }

	add operator =  (char *num);
	add operator =  (int num);

	bool operator <  (const add& b) const;
	bool operator >  (const add& b) const { return b < *this; }
	bool operator <= (const add& b) const { return !(b < *this); }
	bool operator >= (const add& b) const { return !(*this < b); }
	bool operator != (const add& b) const { return b < *this || *this < b; }
	bool operator == (const add& b) const { return !(b != *this); }

	add operator + (const add& c);
	add operator * (const add& c);
	add operator - (const add& c);
	int  operator / (const add& c);
	add operator / (int k);
	add operator % (const add &c);
	int  operator % (int k);
	void operator ++ ();
	bool operator -- ();
};
void calc();
int n, m;
add f[25][25];
int vertex[25][25];
int min(int a, int b)
{
	if (a < b) return a;
	else return b;
}
int max(int a, int b)
{
	if (a < b) return b;
	else return a;
}
add c(int n, int m)
{
	add x = 1;
	m = min(m, n - m);
	for (int i = 0; i < m; i++) {
		add t = (n - i);
		x = x * t / (i + 1);
	}
	return x;
}
void calc()
{	
	for (int i = 1; i <= 21; i++) {
		f[i][0] = 1; vertex[i][0] = 1;
		for (int j = 1; j <= 21 / i; j++) {
			f[i][j] = 1;
			for (int k = 0; k < i; k++) {
				vertex[i][j] = vertex[i][j - 1] * i + 1;
				f[i][j] = f[i][j] * c(vertex[i][j] - 1 - k * vertex[i][j - 1], vertex[i][j - 1]) * f[i][j - 1];
			}
		}
	}
}
int main()
{
	calc();
	while (~scanf("%d%d", &n, &m)) {
		printf("%d", f[n][m]);
		printf("\n");
	}
	return 0;
}