#include<stdio.h>
#include<stdlib.h>


#define LIST_INIT_SIZE 100//���Ա���ռ�ĳ�ʼ���� 
#define LISTINCREMENT//���Ա���ռ�ķ�������
#define OVERFLOW 1
#define OK 0
#define INVALID 1
#define TRUE 1
#define FALSE 0
 
typedef ElemType int
typedef Status int
 

typedef struct{
	ElemType *elem;//�洢�ռ��ַ 
	int length;//��ǰ���ȣ�Ԫ�ظ����� 
	int listsize;//��ǰ����洢���� 
}SqList;

Status InitList_Sq(SqList& L);
void DestroyList(SqList& L);
void ClearList(SqList& L);
int ListEmpty(SqList L);
int ListLength(SqList L);
ElemType GetElem(SqList L,i,&e);
int LocateElem(SqList L,e,compare());
SqList* PriorElem(SqList L,ElemType cur_e,ElemType& pre_e);
SqList* NextElem(SqList L,ElemType cur_e,ElemType& next_e);
void ListInsert(SqList& L,int i,ElemType e);
ElemType(SqList &L,int i,ElemType& e);
void ListTraverse(SqList L,visit());

Status InitList_Sq(SqList& L){
//����һ���յ����Ա�L
L.elem = (ELemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if(!L.elem) exit(OVERFLOW);// �������ʧ��
L.length = 0;//�ձ�Ϊ0
L.listsize =  LIST_INIT_SIZE;
return OK;
} 

void DestroyList(SqList& L){
L.length = 0;
L.listsize = 0;
free(L.elem);
free(&L);
printf("List Destroyed/n");
}

void ClearList(SqList& L){
if(!L.elem) exit(INVALID);
if(!L.length) free(L.elem);
L.elem = (ELemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if(!L.elem) exit(OVERFLOW);// �������ʧ��
L.length = 0;//�ձ�Ϊ0
L.listsize =  LIST_INIT_SIZE;
}

int ListEmpty(SqList L){
if(!L.elem) exit(INVALID);
if(L.length) return TRUE;
else return FALSE;
}

int ListLength(SqList L){
if(!L.elem) exit(INVALID);
return L.length; 
} 
 
ElemType GetElem(SqList L,i,&e){
if(!Elem||i<0||i>L.length) exit(INVALID);
e = (L.elem + (i-1)*;
return e; 
}

int LocateElem(SqList L,e,compare()){
	
}

