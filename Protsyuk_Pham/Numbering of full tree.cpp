#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
void calc();
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
int n, m;
int f[25][25];  //не поміститься, потрібен структурований тип
int main()
{
	calc();
	while (~scanf("%d%d", &n, &m)) {
		printf("%d", f[n][m]);
		printf("\n");
	}
	return 0;
}