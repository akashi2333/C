#include<stdio.h>
#define maxval 10000.0
#define maxsize 100   //��������������λ��
typedef struct
{
 	char ch;
 	int weight;
 	int lchild,rchild,parent;
}hufmtree;
typedef struct
{
 	char bits[5];   //λ��
 	int start;      //������λ���е���ʼλ��
 	char ch;        //�ַ�
}codetype;

void huffman(hufmtree tree[])//������������
{
	int i,j,p1,p2;//p1,p2�ֱ��סÿ�κϲ�ʱȨֵ��С�ʹ�С�������������±�
	float small1,small2,f;
	char c;
	for(i=0;i<9;i++)    //��ʼ��
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
	for(i=5;i<9;i++)      //����n-1�κϲ�������n-1���½��
	{
	  	p1=0;p2=0;
	  	small1=maxval;small2=maxval;   //maxval��float���͵����ֵ
	  	for(j=0;j<i;j++)    //ѡ������Ȩֵ��С�ĸ����
	   		if(tree[j].parent==0)
	    		if(tree[j].weight<small1)
	    		{
	     			small2=small1;  //�ı���СȨ����СȨ����Ӧ��λ��
	     			small1=tree[j].weight;
	     			p2=p1;
	     			p1=j;
	    		}
	    		else if(tree[j].weight<small2)
	     		{
	      			small2=tree[j].weight;  //�ı��СȨ��λ��
	      			p2=j;
	     		}
	  	tree[p1].parent=i;
	  	tree[p2].parent=i;
	  	tree[i].lchild=p1;  //��СȨ��������½�������
	 	tree[i].rchild=p2;  //��СȨ��������½����Һ���
	  	tree[i].weight=tree[p1].weight+tree[p2].weight;
	}
}//huffman

void huffmancode(codetype code[],hufmtree tree[])//���ݹ��������������������
{
 	int i,c,p;
 	codetype cd;   //�������
 	for(i=0;i<5;i++)
 	{
  		cd.start=5;
  		cd.ch=tree[i].ch;
  		c=i;       //��Ҷ���������ϻ���
  		p=tree[i].parent;   //tree[p]��tree[i]��˫��
  		while(p!=0)
  		{
   			cd.start--;
   			if(tree[p].lchild==c)
    			cd.bits[cd.start]='0';   //tree[i]�������������ɴ���'0'
   			else
    			cd.bits[cd.start]='1';   //tree[i]�������������ɴ���'1'
   			c=p;
   			p=tree[p].parent;
  		}
  		code[i]=cd;    //��i+1���ַ��ı������code[i]
 	}
}//huffmancode

