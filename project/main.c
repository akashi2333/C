#include <stdio.h>
#include <stdlib.h>
#include "拓扑排序.h"
#include "哈夫曼编码.h"
#include "最小编辑距离.h"

int main()
{
    printf("拓扑排序:\n");
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    LGraph* pG;
    pG = create_example_lgraph();
    topological_sort(*pG);

 	hufmtree tree[9];
 	codetype code[5];
 	int i,j;//循环变量
 	huffman(tree);//建立哈夫曼树
 	huffmancode(code,tree);//根据哈夫曼树求出哈夫曼编码
 	printf("\n\n\n每个字符的哈夫曼编码:\n");
 	for(i=0;i<5;i++)
 	{
	  	printf("%c: ",code[i].ch);
	  	for(j=code[i].start;j<5;j++)
	   	printf("%c ",code[i].bits[j]);
	  	printf("\n");
 	}

 	printf("\n\n\n最小编辑距离:\n");
	EditDis();
	for(i = 0; i < 3; i++){
		for(j = 0; j <3; j++){
			printf("%d	",dp[i][j]);
		}
		printf("\n");
	}
}
