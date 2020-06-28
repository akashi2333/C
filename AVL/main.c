#include <stdlib.h>
#include <stdio.h>

typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
struct AvlNode
{
    int Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};
//ÖÐÐò±éÀú 
void printAvl(AvlTree T) {
	if(T->Left!=NULL)
		printAvl(T->Left);
	printf("%d   ",T->Element);
	if(T->Right!=NULL)
		printAvl(T->Right);
}

static int Height( Position P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
//³õÊ¼»¯Ê÷ 
AvlTree MakeEmpty( AvlTree T ){
    if( T != NULL ){
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

static int Max( int Lhs, int Rhs ){
    return Lhs > Rhs ? Lhs : Rhs;
}
//×óÐý 
static Position SingleRotateWithLeft( Position K2 )
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  
}
//ÓÒÐý 
static Position SingleRotateWithRight( Position K1 ){
    Position K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  
}
//ÓÒ×óÐý 
static Position DoubleRotateWithLeft( Position K3 ){
  K3->Left = SingleRotateWithRight( K3->Left );
  return SingleRotateWithLeft( K3 );
}
// ×óÓÒÐý 
static Position DoubleRotateWithRight( Position K1 )
{
	K1->Right = SingleRotateWithLeft( K1->Right );
    return SingleRotateWithRight( K1 );
}
//²åÈëµ÷Õû 
AvlTree Insert( int X, AvlTree T )
{
    if( T == NULL ){
        T = (AvlTree)malloc( sizeof( struct AvlNode ) );
        T->Element = X; T->Height = 0;
        T->Left = T->Right = NULL;

    }
    else if( X < T->Element ){
        T->Left = Insert( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
        if( X < T->Left->Element )
            T = SingleRotateWithLeft( T );
        else
            T = DoubleRotateWithLeft( T );
        }
    else if( X > T->Element ){
        T->Right = Insert( X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
        	if( X > T->Right->Element )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}

int main( )
{
	int num[] = {2,4,18,3,31,6,7,32,16,15,23,13,54,11,10,9};
	int i;
	AvlTree T;

    T = MakeEmpty( NULL );
    for(i = 0;i < 16;i++)
    	T = Insert(num[i],T);
	printf("AVLÊ÷²åÈë:\n");
    printAvl(T);
    return 0;
}
