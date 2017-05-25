#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
using std::cout;
using std::endl;
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
	while (~scanf("%d%d", &n, &m)) 
	{
		printf("%d", f[n][m]);
		cout << endl;
	}
	return 0;
}
add add::operator = (char *num) 
{
	init();
	s[0] = strlen(num);
	for (int i = 1; i <= s[0]; i++)
		s[i] = num[s[0] - i] - '0';
	return *this;
}

add add::operator = (int num) 
{
	char str[MAXSIZE];
	sprintf(str, "%d", num);
	return *this = str;
}

bool add::operator < (const add& b) const 
{
	if (s[0] != b.s[0])
		return s[0] < b.s[0];
	for (int i = s[0]; i; i--)
	if (s[i] != b.s[i])
		return s[i] < b.s[i];
	return false;
}
add add::operator + (const add& c) 
{
	int sum = 0;
	add ans;
	ans.s[0] = max(s[0], c.s[0]);

	for (int i = 1; i <= ans.s[0]; i++) 
	{
		if (i <= s[0]) sum += s[i];
		if (i <= c.s[0]) sum += c.s[i];
		ans.s[i] = sum % 10;
		sum /= 10;
	}
	return ans;
}

add add::operator * (const add& c) 
{
	add ans;
	ans.s[0] = 0;

	for (int i = 1; i <= c.s[0]; i++)
	{
		int g = 0;

		for (int j = 1; j <= s[0]; j++)
		{
			int x = s[j] * c.s[i] + g + ans.s[i + j - 1];
			ans.s[i + j - 1] = x % 10;
			g = x / 10;
		}
		int t = i + s[0] - 1;

		while (g)
		{
			++t;
			g += ans.s[t];
			ans.s[t] = g % 10;
			g = g / 10;
		}

		ans.s[0] = max(ans.s[0], t);
	}
	ans.del();
	return ans;
}

add add::operator - (const add& c) 
{
	add x = *this;
	int i;
	for (i = 1; i <= c.s[0]; i++) 
	{
		if (x.s[i] < c.s[i]) 
		{
			x.s[i] += 10;
			x.s[i + 1]--;;
		}
		x.s[i] -= c.s[i];
	}

	for (i = 1; i <= x.s[0]; i++) 
	{
		if (x.s[i] < 0) {
			x.s[i] += 10;
			x.s[i + 1]--;
		}
	}

	x.del();
	return x;
}

int add::operator / (const add& c) 
{
	int ans = 0;
	add d = *this;
	while (d >= c) 
	{
		d = d - c;
		ans++;
	}
	return ans;
}

add add::operator / (int k) 
{
	add ans;
	ans.s[0] = s[0];
	int num = 0;
	for (int i = s[0]; i; i--) 
	{
		num = num * 10 + s[i];
		ans.s[i] = num / k;
		num = num % k;
	}
	ans.del();
	return ans;
}

int add:: operator % (int k)
{
	int sum = 0;
	for (int i = s[0]; i; i--){
		sum = sum * 10 + s[i];
		sum = sum % k;
	}
	return sum;
}

add add::operator % (const add &c) 
{
	add now = *this;
	while (now >= c) {
		now = now - c;
		now.del();
	}
	return now;
}

void add::operator ++ () 
{
	s[1]++;
	for (int i = 1; s[i] == 10; i++) {
		s[i] = 0;
		s[i + 1]++;
		s[0] = max(s[0], i + 1);
	}
}

bool add::operator -- () 
{
	del();
	if (s[0] == 1 && s[1] == 0) return false;

	int i;
	for (i = 1; s[i] == 0; i++)
		s[i] = 9;
	s[i]--;
	del();
	return true;
}

void add::put() 
{
	if (s[0] == 0)
		cout << "0";
	else
	for (int i = s[0]; i; i--)
		printf("%d", s[i]);
}

add add::mul(int d) 
{
	s[0] += d;
	int i;
	for (i = s[0]; i > d; i--)
		s[i] = s[i - d];
	for (i = d; i; i--)
		s[i] = 0;
	return *this;
}

void add::del() 
{
	while (s[s[0]] == 0) {
		s[0]--;
		if (s[0] == 0) break;
	}
}

