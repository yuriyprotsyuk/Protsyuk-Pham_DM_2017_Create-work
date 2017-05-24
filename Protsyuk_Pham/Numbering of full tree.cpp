#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
void calc();
int n, m;
int f[25][25];
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
int c(int n, int m)
{
	int x = 1;
	m = min(m, n - m);
	for (int i = 0; i < m; i++) {
		int t = (n - i);
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