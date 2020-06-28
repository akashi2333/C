#include <stdio.h>
#include <stdlib.h>
#define INF (~(0x1 << 31)) // ���ֵ(��0X7FFFFFFF)
#define NUM(N) N * 2 + 1
#define runN 3

int num = runN;
void DiskMerge();
void swapArray();
// ��������
//����ʹ�����������ԭ���Ĺ����ѣ���Ŀ�Ķ����ҳ���С��Ԫ�أ��������ΪЧ����һ�µģ�����Ϊ�˷�����ѡ��ʹ�ò�������
void insertSort(int A[], int length)
{
    // �����������Ҫ˼�����Ź����ǰһ��������Զ����ģ�ֻ��Ҫ����ǰԪ�ط��õ���ȷλ�þͺ�
    int temp = 0;
    int j = 0;
    int i; 
    for (i = 1; i < length; i++) //����ѡ��ֱ�Ӵӵ�һ��Ԫ�ؿ�ʼ
    {
        temp = A[i];
        for (j = i; j > 0 && A[j - 1] > temp; j--) // ��һ��j=i��Ԫ���ǻ�û�б�����Ĵ���Ԫ�أ�����Ҫ�ӵ�i-1��Ԫ�ؿ�ʼ����
        {
            A[j] = A[j - 1];
        }
        // �˳���һ��ѭ����ԭ��Ҫô���ҵ��˸÷ŵ���ȷλ�ã�Ҫô�ǵ�������ĵ�һλ��
        // ���ǲ����������������ʱj������ȷλ�õ��±꣡
        A[j] = temp;
    }
}

/**
 * fa1 fa2������Ŵ�
 * fb1 fb2������Ŵ�
 * */
void DiskMergeSort(FILE *fa_1, FILE *fa_2, FILE *fb_1, FILE *fb_2)
{

    //���建����
    int tempBuff[runN] = {INF, INF, INF};
    // ��������Ų�����Ҫ���Ԫ��
    int deadSpace[runN] = {INF, INF, INF};
    //���ݻ���
    int dataCache[1] = {0};
    int index = 0;
    int j = 0;
    int flag = 0;
    // ����������ʼ����
    while (!feof(fa_1) && j < 3)
    {
        fscanf(fa_1, "%d", tempBuff + j);
        ++j;
    }
    //����
    insertSort(tempBuff, runN);

    while (1)
    {
        // ѭ��������������������̵�ָ��û�дﵽĩβ�����ҵ�ǰ˳��û�����,��������û�з���
        // ��tempBuff�ĵ�һ��Ԫ�ض���INFʱ��˵�������Ѿ�����ˡ�
        while (!feof(fa_1) && tempBuff[0] != INF && index != 3)
        {
            /*  ����С�ļ�¼д����������ϣ��ٴ�������̶�����һ����¼��������ȸո�д�ļ�¼Ҫ����ô�Ͱ������뵽�����У�����ͷ���������
         *
         * */
            insertSort(tempBuff, runN);
            fprintf(fb_1, "%d ", tempBuff[0]);
            fscanf(fa_1, "%d", dataCache);
            // ��������ֵ�ȸոմ�ӡ���Ǹ�ֵҪ����ô�ͽ�������ݷ��뵽������
            if (dataCache[0] > tempBuff[0])
            {
                tempBuff[0] = dataCache[0];
                insertSort(tempBuff, runN);
            }
            else
            {
                //����ӡ�˵��Ǹ�λ����Ϊ�������
                tempBuff[0] = INF;
                insertSort(tempBuff, runN);
                //�����������ֵ�ȴ�ӡ��ֵ��ҪС����ô�ͽ�������ݷ���������
                deadSpace[index++] = dataCache[0];
            }
        }
        //�����ʱ��������Ѿ���ȡ���ˣ���ô�ͽ���ǰ�����е��������ݵ��뵽�ô�����
        if (feof(fa_1))
        {
            index = 0;
            while (tempBuff[index] != INF && index < 3)
            {
                fprintf(fb_1, "%d ", tempBuff[index]);
                index++;
            }
            //���д�ӡ���֮�󣬽�������Ԫ�ط��뵽��һ�����������
            FILE *tempFp = fb_1;
            fb_1 = fb_2;
            fb_2 = tempFp;
            index = 0;
            //���¹������У�Ȼ��������뵽���������ȥ
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
        // �������ڴ洢������ת�Ƶ�������
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
    // ��a1 a2�е��ļ��ϲ�����b1��b2��
    fa_1 = fopen("SortSource\\TA1.txt", "a+");
    fa_2 = fopen("SortSource\\TA2.txt", "a+");
    fb_1 = fopen("SortSource\\TB1.txt", "a+");
    fb_2 = fopen("SortSource\\TB2.txt", "a+");
    //������кϲ�����
    DiskMerge(fb_1, fb_2, fa_1, fa_2);
}
/**
 * �ϲ�����
 * fa1 fa2������Ŵ�
 * fb1 fb2������Ŵ�
 * */
void DiskMerge(FILE *fa1, FILE *fa2, FILE *fb1, FILE *fb2)
{
    int temp1 = 0;
    int temp2 = 0;

    // Ĩȥ��������ϵ�ȫ������
    fb1 = fopen("SortSource\\TA1.txt", "w");
    fb2 = fopen("SortSource\\TA2.txt", "w");
    // ���´��������
    fb1 = fopen("SortSource\\TA1.txt", "a+");
    fb2 = fopen("SortSource\\TA2.txt", "a+");
    // ѡ��ǰҪ����Ĵ���
    FILE *outp = fb1;
    //���ڽ�������ʱ����
    FILE *tempPoint;
    // ����������̵ı�־
    //1 - TB��Ӧ����  -1 - TA��Ӧ����
    int flag = 1;
    // ��ȡԪ��
    fscanf(fa1, "%d", &temp1);
    fscanf(fa2, "%d", &temp2);
    while (1)
    {
        // �������������̶�û�ж����ļ�ĩβ��ô��һֱ���У�ֱ��ȫ�����ݶ����ϲ����
        while (!feof(fa1) || !feof(fa2))
        {
            //����ȡ���ָ����ʱ�������Ƕ�ȡ���ļ�ĩβ���ͽ���һ���������˳��ȫ����������������
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
            // ����С���Ǹ����ŵ���ǰ���������ȥ��Ȼ���ȡ��һ��Ԫ��
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
        // �������ļ�����ȡ����ˣ���ô�͹ر��ļ�������ļ���д�����
        fclose(fb1);
        fclose(fb2);
        //�������������´��ⲿ�ļ������Ҵ�ʱҪ��ԭ����������̺�������̽�����Ҳ�����������������������������
        //������һ���ǽ�ԭ���������ȫ��Ĩȥ����Ϊ���ǽ�Ҫ�������������ʹ��

        // ����������̵ı�־
        //1 - TB��Ӧ����  -1 - TA��Ӧ����
        if (flag == 1)
        {
            //�����ǰ��������̣������������������ָ��
            fb1 = fopen("SortSource\\TB1.txt", "w");
            fb2 = fopen("SortSource\\TB2.txt", "w");
            fb1 = fopen("SortSource\\TB1.txt", "a+");
            fb2 = fopen("SortSource\\TB2.txt", "a+");

            // �������ļ�������ָ�븳ֵ������ָ��
            fa1 = fopen("SortSource\\TA1.txt", "r");
            fa2 = fopen("SortSource\\TA2.txt", "r");
        }
        else if (flag == -1)
        {
            // ����������
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
    //�ر��ļ���
    fclose(fa_1);
    fclose(fa_2);
    fclose(fb_1);
    fclose(fb_2);
    return 0;
}
