#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define MAX         100
#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

// 邻接表中顶点的定义
typedef struct _ENode
{
    int ivex;                   // 该边的顶点的位置
    struct _ENode *next_edge;   // 指向下一条弧的指针
}ENode, *PENode;

// 头单元的顶点
typedef struct _VNode
{
    int data;              // 顶点信息
    ENode *first_edge;      // 指向第一条依附该顶点的弧
}VNode;


// 邻接表
typedef struct _LGraph
{
    int vexnum;             // 图的顶点的数目
    int edgnum;             // 图的边的数目
    VNode vexs[MAX];
}LGraph;


//边
typedef struct _edata
{
    int start; // 边的起点
    int end;   // 边的终点
}EData;

// 顶点
static char  gVexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
// 边
static EData gEdges[] = {
  // 起点 终点 权
    {'A', 'G'},
    {'B', 'C'},
    {'B', 'D'},
    {'C', 'F'},
    {'C', 'G'},
    {'D', 'E'},
    {'D', 'F'}
};

/*
 * 创建邻接表对应的图
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

    // 初始化"顶点数"和"边数"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // 初始化"邻接表"的顶点,每一个顶点都有以一个邻接表
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = gVexs[i];
        pG->vexs[i].first_edge = NULL;
    }
    // 初始化"邻接表"的边
    for(i=0; i<pG->edgnum; i++)
    {
        // 读取边的起始顶点,结束顶点,权
        c1 = gEdges[i].start;
        c2 = gEdges[i].end;

        p1 = c1-1;
        p2 = c2-1;

        // 初始化node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        node1->next_edge=NULL;
        // 将node1链接到"p1所在链表的末尾"

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
    int head = 0;           // 辅助队列的头
    int rear = 0;           // 辅助队列的尾
    int *queue;             // 辅组队列
    int *ins;               // 入度数组
    char *tops;             // 拓扑排序结果数组，记录每个节点的排序后的序号。
    int num = G.vexnum;
    ENode *node;

    ins  = (int *)malloc(num*sizeof(int));  // 入度数组
    tops = (char *)malloc(num*sizeof(char));// 拓扑排序结果数组
    queue = (int *)malloc(num*sizeof(int)); // 辅助队列
    assert(ins!=NULL && tops!=NULL && queue!=NULL);
    memset(ins, 0, num*sizeof(int));
    memset(tops, 0, num*sizeof(char));
    memset(queue, 0, num*sizeof(int));

    // 统计每个顶点的入度数
    for(i = 0; i < num; i++)
    {
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            ins[node->ivex]++;
            node = node->next_edge;
        }
    }

    // 将所有入度为0的顶点入队列
    for(i = 0; i < num; i ++)
        if(ins[i] == 0)
            queue[rear++] = i;          // 入队列

    while (head != rear)                // 队列非空
    {
        j = queue[head++];              // 出队列。j是顶点的序号
        tops[index++] = G.vexs[j].data; // 将该顶点添加到tops中，tops是排序结果
        node = G.vexs[j].first_edge;    // 获取以该顶点为起点的出边队列

        // 将与"node"关联的节点的入度减1；
        // 若减1之后，该节点的入度为0；则将该节点添加到队列中。
        while(node != NULL)
        {
            // 将节点(序号为node->ivex)的入度减1。
            ins[node->ivex]--;
            // 若节点的入度为0，则将其"入队列"
            if( ins[node->ivex] == 0)
                queue[rear++] = node->ivex;  // 入队列

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

    // 打印拓扑排序结果
    for(i = 0; i < num; i ++)
        printf("%c ", tops[i]);
    printf("\n");

    free(queue);
    free(ins);
    free(tops);
    return 0;
}
