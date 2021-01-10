#include "Slist.h"
#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    char sFieldName[10]; //字段名
    char sType[8];       //字段类型
    int iSize;           //字长
    char bKey;           //该字段是否为KEY键
    char bNullFlag;      //该字段是否允许为空
    char bValidFlag;     //该字段是否有效，可用于以后对表中该字段的删除
} TableMode, *PTableMode;//（属性）

typedef struct
{
    char tableName[1000]; //表名
    int TableModecount;   //总字段数；（属性个数）
    TableMode modeinsert[100];
} Tableset;//表

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
    printf("请输入表名：\n");
    scanf("%s",newTable->tableName);
    printf("请输入字段总数：\n");
    scanf("%d",&newTable->TableModecount);
    printf("请依次输入字段名，字段类型，字长，该字段是否为KEY键，该字段是否允许为空，该字段是否有效，可用于以后对表中该字段的删除：\n");
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
    printf("请输入元组总行数\n");
    scanf("%d", &datalinecount);
    SList *s = (SList *)calloc(100, sizeof(SList));
    printf("=====================================================================\n");
    printf("请依次输入数据\n");
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
    //找链表最后一个节点
    assert(s);
    PNode pNewNode = BuySListNode(data);
    if (s->_pHead == NULL)
    { //链表没有节点的情况
        s->_pHead = pNewNode;
    }
    else
    {
        PNode pCur = s->_pHead;
        while (pCur->_PNext)
        {
            pCur = pCur->_PNext;
        }
        //让最后一个节点指向新节点
        pCur->_PNext = pNewNode;
    }
}

void SListPopBack(SList *s)
{
    assert(s);
    if (s->_pHead == NULL)
    { //链表中没有节点
        return;
    }
    else if (s->_pHead->_PNext == NULL)
    { //只有一个节点
        free(s->_pHead);
        s->_pHead = NULL;
    }
    else
    { //多个节点
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
    { //链表为空
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
    { //链表为空
        return;
    }
    else if (s->_pHead->_PNext == NULL)
    { //只有一个节点
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
            { //要删除的是第一个位置的节点
                s->_pHead = pCur->_PNext;
            }
            else
            {
                pPre->_PNext = pCur->_PNext; //其它位置的情况，让前一个节点指向其后一个节点
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
{ //获取链表有效节点的个数
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
{ //检测链表是否为空
    assert(s);
    if (s->_pHead == NULL)
    {
        return -1;
    }
    return 0;
}

void SListClear(SList *s)
{ //清空链表
    assert(s);
    if (s->_pHead == NULL)
    {
        return;
    }
    PNode pCur = s->_pHead;
    while (pCur->_PNext)
    { //循环清空链表中的节点
        PNode Tmp = pCur->_PNext;
        free(pCur);
        pCur = Tmp;
    }
    if (pCur)
    { //清空最后一个节点
        free(pCur);
        pCur = NULL;
    }
}

void SListDestroy(SList *s)
{ //销毁链表
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
{ //打印链表
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
