#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define MAX         100
#define INF         (~(0x1<<31))        // ���ֵ(��0X7FFFFFFF)
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

// �ڽӱ��ж���Ķ���
typedef struct _ENode
{
    int ivex;                   // �ñߵĶ����λ��
    struct _ENode *next_edge;   // ָ����һ������ָ��
}ENode, *PENode;

// ͷ��Ԫ�Ķ���
typedef struct _VNode
{
    int data;              // ������Ϣ
    ENode *first_edge;      // ָ���һ�������ö���Ļ�
}VNode;


// �ڽӱ�
typedef struct _LGraph
{
    int vexnum;             // ͼ�Ķ������Ŀ
    int edgnum;             // ͼ�ıߵ���Ŀ
    VNode vexs[MAX];
}LGraph;


//��
typedef struct _edata
{
    int start; // �ߵ����
    int end;   // �ߵ��յ�
}EData;

// ����
static char  gVexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
// ��
static EData gEdges[] = {
  // ��� �յ� Ȩ
    {'A', 'G'},
    {'B', 'C'},
    {'B', 'D'},
    {'C', 'F'},
    {'C', 'G'},
    {'D', 'E'},
    {'D', 'F'}
};

/*
 * �����ڽӱ��Ӧ��ͼ
 */
LGraph* create_example_lgraph()
{
    int c1, c2;
    int vlen = LENGTH(gVexs);
    int elen = LENGTH(gEdges);
    int i, p1, p2;
    ENode *node1, *node2, *tmpnode;
    LGraph* pG;
    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // ��ʼ��"������"��"����"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // ��ʼ��"�ڽӱ�"�Ķ���,ÿһ�����㶼����һ���ڽӱ�
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = gVexs[i];
        pG->vexs[i].first_edge = NULL;
    }
    // ��ʼ��"�ڽӱ�"�ı�
    for(i=0; i<pG->edgnum; i++)
    {
        // ��ȡ�ߵ���ʼ����,��������,Ȩ
        c1 = gEdges[i].start;
        c2 = gEdges[i].end;

        p1 = c1-1;
        p2 = c2-1;

        // ��ʼ��node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        node1->next_edge=NULL;
        // ��node1���ӵ�"p1���������ĩβ"

        if(pG->vexs[p1].first_edge == NULL){
        	pG->vexs[p1].first_edge = node1;
		}
        else{
        	tmpnode=pG->vexs[p1].first_edge;
        	while(tmpnode->next_edge!=NULL)
        	{
        		tmpnode=tmpnode->next_edge;
			}
			tmpnode->next_edge=node1;
		}


    }
    return pG;
}

int topological_sort(LGraph G)
{
    int i,j;
    int index = 0;
    int head = 0;           // �������е�ͷ
    int rear = 0;           // �������е�β
    int *queue;             // �������
    int *ins;               // �������
    char *tops;             // �������������飬��¼ÿ���ڵ����������š�
    int num = G.vexnum;
    ENode *node;

    ins  = (int *)malloc(num*sizeof(int));  // �������
    tops = (char *)malloc(num*sizeof(char));// ��������������
    queue = (int *)malloc(num*sizeof(int)); // ��������
    assert(ins!=NULL && tops!=NULL && queue!=NULL);
    memset(ins, 0, num*sizeof(int));
    memset(tops, 0, num*sizeof(char));
    memset(queue, 0, num*sizeof(int));

    // ͳ��ÿ������������
    for(i = 0; i < num; i++)
    {
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            ins[node->ivex]++;
            node = node->next_edge;
        }
    }

    // ���������Ϊ0�Ķ��������
    for(i = 0; i < num; i ++)
        if(ins[i] == 0)
            queue[rear++] = i;          // �����

    while (head != rear)                // ���зǿ�
    {
        j = queue[head++];              // �����С�j�Ƕ�������
        tops[index++] = G.vexs[j].data; // ���ö�����ӵ�tops�У�tops��������
        node = G.vexs[j].first_edge;    // ��ȡ�Ըö���Ϊ���ĳ��߶���

        // ����"node"�����Ľڵ����ȼ�1��
        // ����1֮�󣬸ýڵ�����Ϊ0���򽫸ýڵ���ӵ������С�
        while(node != NULL)
        {
            // ���ڵ�(���Ϊnode->ivex)����ȼ�1��
            ins[node->ivex]--;
            // ���ڵ�����Ϊ0������"�����"
            if( ins[node->ivex] == 0)
                queue[rear++] = node->ivex;  // �����

            node = node->next_edge;
        }
    }

    if(index != G.vexnum)
    {
        printf("Graph has a cycle\n");
        free(queue);
        free(ins);
        free(tops);
        return 1;
    }

    // ��ӡ����������
    for(i = 0; i < num; i ++)
        printf("%c ", tops[i]);
    printf("\n");

    free(queue);
    free(ins);
    free(tops);
    return 0;
}
