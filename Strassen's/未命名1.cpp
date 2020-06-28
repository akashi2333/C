#include<stdio.h>
#define N 8

void output(int n,int p[N][N])
{
	int i,j;
	for(i=0;i<n;i++)
	{
	printf("\n");
	for(j=0;j<n;j++)
	{
	 printf("%d  ",p[i][j]);
	}
}
	}
void MATRIX_ADD(int n,int X[][N],int Y[][N],int Z[][N])
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	Z[i][j]=X[i][j]+Y[i][j];
}
void MATRIX_SUB(int n,int X[][N],int Y[][N],int Z[][N])
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	Z[i][j]=X[i][j]-Y[i][j];
}
void MATRIX_MULTIPLY(int A[][N],int B[][N],int C[][N])
{
	int i,j,t;
	for(i=0;i<2;i++)
	for(j=0;j<2;j++)
	{
	 C[i][j]=0;
	 for(t=0;t<2;t++)
	 C[i][j]=C[i][j]+A[i][t]*B[t][j];
	}
}
void STRASSEN(int n,int A[][N],int B[][N],int C[][N])
{
	int i,j;
	int A11[N][N],A12[N][N],A21[N][N],A22[N][N];
	int B11[N][N],B12[N][N],B21[N][N],B22[N][N];
	int C11[N][N],C12[N][N],C21[N][N],C22[N][N];
	int M1[N][N],M2[N][N],M3[N][N],M4[N][N],M5[N][N],M6[N][N],M7[N][N];
	int AA[N][N],BB[N][N],MM1[N][N],MM2[N][N];
	if(n==2)
	MATRIX_MULTIPLY(A,B,C);
	else
	{
	 for(i=0;i<n/2;i++)
	 for(j=0;j<n/2;j++)
	 {
		 A11[i][j]=A[i][j];
		 A12[i][j]=A[i][j+n/2];
		 A21[i][j]=A[i+n/2][j];
		 A22[i][j]=A[i+n/2][j+n/2];
		 B11[i][j]=B[i][j];
		 B12[i][j]=B[i][j+n/2];
		 B21[i][j]=B[i+n/2][j];
		 B22[i][j]=B[i+n/2][j+n/2];

	 }
	 MATRIX_SUB(n/2,B12,B22,BB);
	 STRASSEN(n/2,A11,BB,M1);
	 MATRIX_ADD(n/2,A11,A12,AA);
	 STRASSEN(n/2,AA,B22,M2);
	 MATRIX_ADD(n/2,A21,A22,AA);
	 STRASSEN(n/2,AA,B11,M3);
	 MATRIX_SUB(n/2,B21,B11,BB);
	 STRASSEN(n/2,A22,BB,M4);
	 MATRIX_ADD(n/2,A11,A22,AA);
	 MATRIX_ADD(n/2,B11,B22,BB);
	 STRASSEN(n/2,AA,BB,M5);
	 MATRIX_SUB(n/2,A12,A22,AA);
	 MATRIX_ADD(n/2,B21,B22,BB);
	 STRASSEN(n/2,AA,BB,M6);
	 MATRIX_SUB(n/2,A11,A21,AA);
	 MATRIX_ADD(n/2,B11,B12,BB);
	 STRASSEN(n/2,AA,BB,M7);
	 MATRIX_ADD(n/2,M5,M4,MM1);
	 MATRIX_SUB(n/2,M6,M2,MM2);
	 MATRIX_ADD(n/2,MM1,MM2,C11);
	 MATRIX_ADD(n/2,M1,M2,C12);
	 MATRIX_ADD(n/2,M3,M4,C21);
	 MATRIX_ADD(n/2,M3,M7,MM2);
	 MATRIX_ADD(n/2,M5,M1,MM1);
	 MATRIX_SUB(n/2,MM1,MM2,C22);
	 for(i=0;i<n/2;i++)
	 for(j=0;j<n/2;j++)
	 {
		 C[i][j]=C11[i][j];
		 C[i][j+n/2]=C12[i][j];
		 C[i+n/2][j]=C21[i][j];
		 C[i+n/2][j+n/2]=C22[i][j];
	 }


	}
}
int main(void)
{
	int C[N][N];
	int A[N][N] = {
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1}
	};
	int	B[N][N] = {
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1}
	};
	
	STRASSEN(N,A,B,C);
	output(N,C);
}

