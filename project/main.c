#include <stdio.h>
#include <stdlib.h>
#include "��������.h"
#include "����������.h"
#include "��С�༭����.h"

int main()
{
    printf("��������:\n");
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    LGraph* pG;
    pG = create_example_lgraph();
    topological_sort(*pG);

 	hufmtree tree[9];
 	codetype code[5];
 	int i,j;//ѭ������
 	huffman(tree);//������������
 	huffmancode(code,tree);//���ݹ��������������������
 	printf("\n\n\nÿ���ַ��Ĺ���������:\n");
 	for(i=0;i<5;i++)
 	{
	  	printf("%c: ",code[i].ch);
	  	for(j=code[i].start;j<5;j++)
	   	printf("%c ",code[i].bits[j]);
	  	printf("\n");
 	}

 	printf("\n\n\n��С�༭����:\n");
	EditDis();
	for(i = 0; i < 3; i++){
		for(j = 0; j <3; j++){
			printf("%d	",dp[i][j]);
		}
		printf("\n");
	}
}
