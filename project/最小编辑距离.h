#include <stdio.h>
#define MAX         100
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))
#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)

int dp[MAX][MAX];
char a[MAX],b[MAX];   //a,b字符串从下标1开始

int min(int a,int b,int c){
	if(a <= b && a <= c)
		return a;
	if(b <= a && b <= c)
		return b;
	if(c<=a && c <= b)
		return c;
}

int EditDis()
{
	a[1] = 'm';
	a[2] = 'e';
	b[1] = 'm';
	b[2] = 'y';
    int len1 = 2;
    int len2 = 2;
    int i,j;

    //初始化
    for(i = 1;i <= len1;i++)
        for(j = 1;j <= len2;j++)
            dp[i][j] = INF;

    for(i = 1;i <= len1;i++)
        dp[i][0] = i;
    for(j = 1;j <= len2;j++)
        dp[0][j] = j;
        
    for(i = 1;i <= len1;i++)
    {
        for(j = 1;j <= len2;j++)
        {
            int indicator;
            indicator = a[i] == b[j]? 0:1;
            dp[i][j] = min(dp[i-1][j]+1,dp[i][j-1]+1,dp[i-1][j-1]+indicator);
        }

    }

    return dp[len1][len2];
}
