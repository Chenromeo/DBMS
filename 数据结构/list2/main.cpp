#include "Slist.h"
#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    char sFieldName[10]; //�ֶ���
    char sType[8];       //�ֶ�����
    int iSize;           //�ֳ�
    char bKey;           //���ֶ��Ƿ�ΪKEY��
    char bNullFlag;      //���ֶ��Ƿ�����Ϊ��
    char bValidFlag;     //���ֶ��Ƿ���Ч���������Ժ�Ա��и��ֶε�ɾ��
} TableMode, *PTableMode;//�����ԣ�

typedef struct
{
    char tableName[1000]; //����
    int TableModecount;   //���ֶ����������Ը�����
    TableMode modeinsert[100];
} Tableset;//��

void dataInsert(Tableset *newTable, SList *s)
{
    assert(s);

    SListInit(s);
    int i = 0;
    for (; i < newTable->TableModecount; i++)
    {
        printf("1");
        char l_data[newTable->modeinsert[i].iSize];
        scanf("%s", l_data);
        SListPushBack(s, l_data);
    }
}
void createTable()
{
    Tableset *newTable = (Tableset *)malloc(sizeof(Tableset));
    printf("�����������\n");
    scanf("%s",newTable->tableName);
    printf("�������ֶ�������\n");
    scanf("%d",&newTable->TableModecount);
    printf("�����������ֶ������ֶ����ͣ��ֳ������ֶ��Ƿ�ΪKEY�������ֶ��Ƿ�����Ϊ�գ����ֶ��Ƿ���Ч���������Ժ�Ա��и��ֶε�ɾ����\n");
    int i = 0;
    for (; i < newTable->TableModecount; i++)
    {
        scanf("%s", newTable->modeinsert[i].sFieldName);
        scanf("%s", newTable->modeinsert[i].sType);
        scanf("%d", &newTable->modeinsert[i].iSize);
        scanf("%c", &newTable->modeinsert[i].bKey);
        scanf("%c", &newTable->modeinsert[i].bNullFlag);
        scanf("%c", &newTable->modeinsert[i].bValidFlag);
    }
    printf("=====================================================================\n");
    int datalinecount;
    printf("������Ԫ��������\n");
    scanf("%d", &datalinecount);
    SList *s = (SList *)calloc(100, sizeof(SList));
    printf("=====================================================================\n");
    printf("��������������\n");
    for (int t = 0; t < datalinecount; t++)
        dataInsert(newTable, s + t);
}

struct SListNode *BuySListNode(SDataType data)
{
    struct SListNode *p;
    p = (struct SListNode *)malloc(sizeof(struct SListNode));
    p->_data = data;
    p->_PNext = NULL;
}

void SListInit(SList *s)
{
    assert(s);
    s->_pHead = NULL;
}

void SListPushBack(SList *s, SDataType data)
{
    //���������һ���ڵ�
    assert(s);
    PNode pNewNode = BuySListNode(data);
    if (s->_pHead == NULL)
    { //����û�нڵ�����
        s->_pHead = pNewNode;
    }
    else
    {
        PNode pCur = s->_pHead;
        while (pCur->_PNext)
        {
            pCur = pCur->_PNext;
        }
        //�����һ���ڵ�ָ���½ڵ�
        pCur->_PNext = pNewNode;
    }
}

void SListPopBack(SList *s)
{
    assert(s);
    if (s->_pHead == NULL)
    { //������û�нڵ�
        return;
    }
    else if (s->_pHead->_PNext == NULL)
    { //ֻ��һ���ڵ�
        free(s->_pHead);
        s->_pHead = NULL;
    }
    else
    { //����ڵ�
        PNode pCur = s->_pHead;
        PNode pPre = NULL;
        while (pCur->_PNext)
        {
            pPre = pCur;
            pCur = pCur->_PNext;
        }
        free(pCur);
        pPre->_PNext = NULL;
    }
}

void SListPushFront(SList *s, SDataType data)
{
    assert(s);
    PNode pNewNode = BuySListNode(data);
    if (s->_pHead == NULL)
    { //����Ϊ��
        s->_pHead = pNewNode;
    }
    else
    {
        pNewNode->_PNext = s->_pHead;
        s->_pHead = pNewNode;
    }
}

void SListPopFront(SList *s)
{
    assert(s);
    if (s->_pHead == NULL)
    { //����Ϊ��
        return;
    }
    else if (s->_pHead->_PNext == NULL)
    { //ֻ��һ���ڵ�
        free(s->_pHead);
        s->_pHead = NULL;
    }
    else
    {
        PNode pCur = s->_pHead;
        s->_pHead = pCur->_PNext;
        free(pCur);
    }
}

void SListInsert(PNode pos, SDataType data)
{
    PNode pNewNode = NULL;
    if (pos == NULL)
    {
        return;
    }
    pNewNode = BuySListNode(data);

    pNewNode->_PNext = pos->_PNext;
    pos->_PNext = pNewNode;
}

PNode SListFind(SList *s, SDataType data)
{
    assert(s);
    PNode pCur = s->_pHead;
    while (pCur)
    {
        if (pCur->_data == data)
        {
            return pCur;
        }
        pCur = pCur->_PNext;
    }
    return NULL;
}

void SListErase(SList *s, PNode pos)
{
    assert(s);
    if (pos == NULL || s->_pHead == NULL)
    {
        return;
    }
    if (pos == s->_pHead)
    {
        s->_pHead = pos->_PNext;
    }
    else
    {
        PNode pPrePos = s->_pHead;
        while (pPrePos && pPrePos->_PNext != pos)
        {
            pPrePos = pPrePos->_PNext;
        }
        pPrePos->_PNext = pos->_PNext;
    }
    free(pos);
}

void SListRemove(SList *s, SDataType data)
{
    assert(s);
    if (s->_pHead == NULL)
    {
        return;
    }
    PNode pPre = NULL;
    PNode pCur = s->_pHead;
    while (pCur)
    {
        if (pCur->_data == data)
        {
            if (pCur == s->_pHead)
            { //Ҫɾ�����ǵ�һ��λ�õĽڵ�
                s->_pHead = pCur->_PNext;
            }
            else
            {
                pPre->_PNext = pCur->_PNext; //����λ�õ��������ǰһ���ڵ�ָ�����һ���ڵ�
            }
            free(pCur);
            return;
        }
        else
        {
            pPre = pCur;
            pCur = pCur->_PNext;
        }
    }
}

int SListSize(SList *s)
{ //��ȡ������Ч�ڵ�ĸ���
    assert(s);
    int count = 0;
    PNode pCur = s->_pHead;
    while (pCur)
    {
        count++;
        pCur = pCur->_PNext;
    }
    return count;
}

int SListEmpty(SList *s)
{ //��������Ƿ�Ϊ��
    assert(s);
    if (s->_pHead == NULL)
    {
        return -1;
    }
    return 0;
}

void SListClear(SList *s)
{ //�������
    assert(s);
    if (s->_pHead == NULL)
    {
        return;
    }
    PNode pCur = s->_pHead;
    while (pCur->_PNext)
    { //ѭ����������еĽڵ�
        PNode Tmp = pCur->_PNext;
        free(pCur);
        pCur = Tmp;
    }
    if (pCur)
    { //������һ���ڵ�
        free(pCur);
        pCur = NULL;
    }
}

void SListDestroy(SList *s)
{ //��������
    assert(s);
    if (s->_pHead == NULL)
    {
        free(s->_pHead);
        return;
    }
    while (s->_pHead)
    {
        PNode Tmp = s->_pHead->_PNext;
        free(s->_pHead);
        s->_pHead = Tmp;
    }
}

void SListPrint(SList *s)
{ //��ӡ����
    assert(s);
    PNode pCur = s->_pHead;
    while (pCur)
    {
        printf("%s--->", pCur->_data);
        pCur = pCur->_PNext;
    }
    printf("\n");
}
int main()
{
    createTable();
    return 1;
}
