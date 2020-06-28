#include<stdio.h>
#define maxval 10000.0
#define maxsize 100   //哈夫曼编码的最大位数
typedef struct
{
 	char ch;
 	int weight;
 	int lchild,rchild,parent;
}hufmtree;
typedef struct
{
 	char bits[5];   //位串
 	int start;      //编码在位串中的起始位置
 	char ch;        //字符
}codetype;

void huffman(hufmtree tree[])//建立哈夫曼树
{
	int i,j,p1,p2;//p1,p2分别记住每次合并时权值最小和次小的两个根结点的下标
	float small1,small2,f;
	char c;
	for(i=0;i<9;i++)    //初始化
	{
		tree[i].parent=0;
		tree[i].lchild=-1;
		tree[i].rchild=-1;
		tree[i].weight=0.0;
	}
	tree[0].ch = 'w';
	tree[0].weight = 12;
	tree[1].ch = 'r';
	tree[1].weight = 22;
	tree[2].ch = 'a';
	tree[2].weight = 32;
	tree[3].ch = 'g';
	tree[3].weight = 42;
	tree[4].ch = 'q';
	tree[4].weight = 52;
	for(i=5;i<9;i++)      //进行n-1次合并，产生n-1个新结点
	{
	  	p1=0;p2=0;
	  	small1=maxval;small2=maxval;   //maxval是float类型的最大值
	  	for(j=0;j<i;j++)    //选出两个权值最小的根结点
	   		if(tree[j].parent==0)
	    		if(tree[j].weight<small1)
	    		{
	     			small2=small1;  //改变最小权、次小权及对应的位置
	     			small1=tree[j].weight;
	     			p2=p1;
	     			p1=j;
	    		}
	    		else if(tree[j].weight<small2)
	     		{
	      			small2=tree[j].weight;  //改变次小权及位置
	      			p2=j;
	     		}
	  	tree[p1].parent=i;
	  	tree[p2].parent=i;
	  	tree[i].lchild=p1;  //最小权根结点是新结点的左孩子
	 	tree[i].rchild=p2;  //次小权根结点是新结点的右孩子
	  	tree[i].weight=tree[p1].weight+tree[p2].weight;
	}
}//huffman

void huffmancode(codetype code[],hufmtree tree[])//根据哈夫曼树求出哈夫曼编码
{
 	int i,c,p;
 	codetype cd;   //缓冲变量
 	for(i=0;i<5;i++)
 	{
  		cd.start=5;
  		cd.ch=tree[i].ch;
  		c=i;       //从叶结点出发向上回溯
  		p=tree[i].parent;   //tree[p]是tree[i]的双亲
  		while(p!=0)
  		{
   			cd.start--;
   			if(tree[p].lchild==c)
    			cd.bits[cd.start]='0';   //tree[i]是左子树，生成代码'0'
   			else
    			cd.bits[cd.start]='1';   //tree[i]是右子树，生成代码'1'
   			c=p;
   			p=tree[p].parent;
  		}
  		code[i]=cd;    //第i+1个字符的编码存入code[i]
 	}
}//huffmancode

