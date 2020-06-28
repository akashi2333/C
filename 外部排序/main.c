#include <stdio.h>
#include <stdlib.h>
#define INF (~(0x1 << 31)) // 最大值(即0X7FFFFFFF)
#define NUM(N) N * 2 + 1
#define runN 3

int num = runN;
void DiskMerge();
void swapArray();
// 插入排序
//这里使用排序来替代原本的构建堆，其目的都是找出最小的元素，因此我认为效果是一致的，所以为了方便我选择使用插入排序。
void insertSort(int A[], int length)
{
    // 插入排序的主要思想是排过序的前一部分是永远有序的，只需要将当前元素放置到正确位置就好
    int temp = 0;
    int j = 0;
    int i; 
    for (i = 1; i < length; i++) //可以选择直接从第一个元素开始
    {
        temp = A[i];
        for (j = i; j > 0 && A[j - 1] > temp; j--) // 第一个j=i的元素是还没有被排序的待排元素！所以要从第i-1个元素开始排序
        {
            A[j] = A[j - 1];
        }
        // 退出上一个循环的原因要么是找到了该放的正确位置，要么是到了数组的第一位。
        // 但是不管是那种情况，此时j就是正确位置的下标！
        A[j] = temp;
    }
}

/**
 * fa1 fa2是输入磁带
 * fb1 fb2是输出磁带
 * */
void DiskMergeSort(FILE *fa_1, FILE *fa_2, FILE *fb_1, FILE *fb_2)
{

    //定义缓冲区
    int tempBuff[runN] = {INF, INF, INF};
    // 死区，存放不符合要求的元素
    int deadSpace[runN] = {INF, INF, INF};
    //数据缓存
    int dataCache[1] = {0};
    int index = 0;
    int j = 0;
    int flag = 0;
    // 读入三个初始数据
    while (!feof(fa_1) && j < 3)
    {
        fscanf(fa_1, "%d", tempBuff + j);
        ++j;
    }
    //排序
    insertSort(tempBuff, runN);

    while (1)
    {
        // 循环继续的条件是输入磁盘的指针没有达到末尾，并且当前顺串没有完结,并且死区没有放满
        // 当tempBuff的第一个元素都是INF时，说明队列已经清空了。
        while (!feof(fa_1) && tempBuff[0] != INF && index != 3)
        {
            /*  把最小的记录写道输出磁盘上，再从输入磁盘读入下一个记录，如果它比刚刚写的记录要大，那么就把他加入到数组中，否则就放入死区。
         *
         * */
            insertSort(tempBuff, runN);
            fprintf(fb_1, "%d ", tempBuff[0]);
            fscanf(fa_1, "%d", dataCache);
            // 如果读入的值比刚刚打印的那个值要大，那么就将这个数据放入到队列中
            if (dataCache[0] > tempBuff[0])
            {
                tempBuff[0] = dataCache[0];
                insertSort(tempBuff, runN);
            }
            else
            {
                //将打印了的那个位置置为最大正数
                tempBuff[0] = INF;
                insertSort(tempBuff, runN);
                //如果这个读入的值比打印的值还要小，那么就将这个数据放入死区中
                deadSpace[index++] = dataCache[0];
            }
        }
        //如果此时输入磁盘已经读取完了，那么就将当前队列中的所有数据导入到该磁盘中
        if (feof(fa_1))
        {
            index = 0;
            while (tempBuff[index] != INF && index < 3)
            {
                fprintf(fb_1, "%d ", tempBuff[index]);
                index++;
            }
            //队列打印完成之后，将死区的元素放入到另一个输出磁盘中
            FILE *tempFp = fb_1;
            fb_1 = fb_2;
            fb_2 = tempFp;
            index = 0;
            //重新构建队列，然后把它输入到输出磁盘中去
            insertSort(deadSpace, runN);
            while (deadSpace[index] != INF)
            {
                fprintf(fb_1, "%d ", deadSpace[index]);
                index++;
            }
            break;
        }
        // swapPoint(fb_1,fb_2);
        fprintf(fb_1, "%d ", INF);
        FILE *tempFp = fb_1;
        fb_1 = fb_2;
        fb_2 = tempFp;
        int i;
        // 将死区内存储的数据转移到队列中
        swapArray(tempBuff, deadSpace, runN);
        for (i = 0; i < runN; i++)
        {
            deadSpace[i] = INF;
        }
        index = 0;
    }
    fclose(fa_1);
    fclose(fa_2);
    fclose(fb_1);
    fclose(fb_2);
    // 将a1 a2中的文件合并排序到b1，b2中
    fa_1 = fopen("SortSource\\TA1.txt", "a+");
    fa_2 = fopen("SortSource\\TA2.txt", "a+");
    fb_1 = fopen("SortSource\\TB1.txt", "a+");
    fb_2 = fopen("SortSource\\TB2.txt", "a+");
    //下面进行合并排序
    DiskMerge(fb_1, fb_2, fa_1, fa_2);
}
/**
 * 合并部分
 * fa1 fa2是输入磁带
 * fb1 fb2是输出磁带
 * */
void DiskMerge(FILE *fa1, FILE *fa2, FILE *fb1, FILE *fb2)
{
    int temp1 = 0;
    int temp2 = 0;

    // 抹去输出磁盘上的全部内容
    fb1 = fopen("SortSource\\TA1.txt", "w");
    fb2 = fopen("SortSource\\TA2.txt", "w");
    // 重新打开输出磁盘
    fb1 = fopen("SortSource\\TA1.txt", "a+");
    fb2 = fopen("SortSource\\TA2.txt", "a+");
    // 选择当前要输出的磁盘
    FILE *outp = fb1;
    //用于交换的临时变量
    FILE *tempPoint;
    // 输入输出磁盘的标志
    //1 - TB对应输入  -1 - TA对应输入
    int flag = 1;
    // 读取元素
    fscanf(fa1, "%d", &temp1);
    fscanf(fa2, "%d", &temp2);
    while (1)
    {
        // 如果两个输入磁盘都没有读到文件末尾那么就一直进行，直到全部数据都被合并完成
        while (!feof(fa1) || !feof(fa2))
        {
            //当读取到分割符号时，或者是读取到文件末尾，就将另一个输入磁盘顺串全部输出到输出磁盘上
            if (temp1 == INF || feof(fa1))
            {
                if (!feof(fa1))
                {
                    fscanf(fa1, "%d", &temp1);
                }
                while (temp2 != INF && !feof(fa2))
                {
                    fprintf(outp, "%d ", temp2);
                    fscanf(fa2, "%d", &temp2);
                }
                outp = fb2;
                if (temp2 == INF && !feof(fa2))
                {
                    fprintf(outp,"%d ",INF);
                    fscanf(fa2, "%d", &temp2);
                }
                if (feof(fa1) && feof(fa2))
                {
                    break;
                }
                if (feof(fa1))
                {
                    temp1 = INF;
                }
            }
            if (temp2 == INF || feof(fa2))
            {
                if (!feof(fa2))
                {
                    fscanf(fa2, "%d", &temp2);
                }

                while (temp1 != INF && !feof(fa1))
                {
                    fprintf(outp, "%d ", temp1);
                    fscanf(fa1, "%d", &temp1);
                }
                outp = fb2;
                if (temp1 == INF && !feof(fa1))
                {
                    fprintf(outp,"%d ",INF);
                    fscanf(fa1, "%d", &temp1);
                }
                if (feof(fa1) && feof(fa2))
                {
                    break;
                }
                if (feof(fa2))
                {
                    temp2 = INF;
                }
            }
            // 将较小的那个数放到当前输出磁盘中去，然后读取下一个元素
            if (temp1 > temp2)
            {
                fprintf(outp, "%d ", temp2);
                fscanf(fa2, "%d", &temp2);
            }
            else if (temp1 < temp2)
            {
                fprintf(outp, "%d ", temp1);
                fscanf(fa1, "%d", &temp1);
            }
        }
        // 当两个文件都读取完成了，那么就关闭文件，完成文件的写入操作
        fclose(fb1);
        fclose(fb2);
        //接下来就是重新打开外部文件，并且此时要将原本的输入磁盘和输出磁盘交换。也就是输入变成了输出，输出变成了输入
        //下面这一段是将原本输入磁盘全部抹去，因为它们将要被当作输出磁盘使用

        // 输入输出磁盘的标志
        //1 - TB对应输入  -1 - TA对应输入
        if (flag == 1)
        {
            //清除当前的输入磁盘，并把它赋给输出磁盘指针
            fb1 = fopen("SortSource\\TB1.txt", "w");
            fb2 = fopen("SortSource\\TB2.txt", "w");
            fb1 = fopen("SortSource\\TB1.txt", "a+");
            fb2 = fopen("SortSource\\TB2.txt", "a+");

            // 打开输入文件，创建指针赋值给输入指针
            fa1 = fopen("SortSource\\TA1.txt", "r");
            fa2 = fopen("SortSource\\TA2.txt", "r");
        }
        else if (flag == -1)
        {
            // 与上面类似
            fb1 = fopen("SortSource\\TA1.txt", "w");
            fb2 = fopen("SortSource\\TA2.txt", "w");
            fb1 = fopen("SortSource\\TA1.txt", "a+");
            fb2 = fopen("SortSource\\TA2.txt", "a+");

            fa1 = fopen("SortSource\\TB1.txt", "r");
            fa2 = fopen("SortSource\\TB2.txt", "r");
        }
        flag *= -1;
        int temp3 = fscanf(fa1, "%d", &temp1);
        int temp4 = fscanf(fa2, "%d", &temp2);
        outp = fb1;
        if (fa1 != NULL && temp4 == -1)
        {
            break;
        }
        else if (temp3 == -1 && fa2 != NULL)
        {
            break;
        }
    }
}
void swapArray(int A[], int B[], int length)
{
	int i;
    for (i = 0; i < length; i++)
    {
        A[i] = B[i];
    }
}
int main(int argc, char const *argv[])
{
    FILE *fa_1, *fa_2, *fb_1, *fb_2;
    fa_1 = fopen("SortSource\\TA1.txt", "a+");
    fa_2 = fopen("SortSource\\TA2.txt", "a+");
    fb_1 = fopen("SortSource\\TB1.txt", "a+");
    fb_2 = fopen("SortSource\\TB2.txt", "a+");
    DiskMergeSort(fa_1, fa_2, fb_1, fb_2);
    //关闭文件流
    fclose(fa_1);
    fclose(fa_2);
    fclose(fb_1);
    fclose(fb_2);
    return 0;
}
