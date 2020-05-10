#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<math.h>
#include<sys/types.h>
#include<memory.h>
#include<Windows.h>
#include<vector>
#include<stack>
#include<iostream>
using namespace std;

//---------ͼ���ڽӾ����ʾ---------//
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 50
#define INITIAL_LENGTH 20
#define Width 100
#define MAX_DICT_SIZE 109749
#define MAX_Route 10

typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef struct PreType {//ǰ��Ԫ��
	int VexIndex;//ǰ���±�
	int PathNum;//���·�����
}PreType;

typedef struct VListCell {//�����Ϣ�б�
	int PathOrder;//·�����
	unsigned int PathLength;//·������
	int PreVertex;//ǰ�������
	int PrePathOrder;//ǰ��·���±�
}VListCell��VList[MAX_VERTEX_NUM];

typedef struct InfoType {//ͼ�Ļ��ϴ洢�ʺʹʳ�
	char Characters[INITIAL_LENGTH];
	int WordLength;
}InfoType;

typedef struct VertexType {
	int index;//�����±�
	VListCell table[MAX_VERTEX_NUM];//���ݱ�
}VertexType;

typedef struct ArcCell {//�ڽӾ����Ԫ��
	unsigned int adj;//Ȩֵ��>�洢��Ƶ
	//InfoType *info;//ָ��û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {//�����޻�ͼ
	VertexType vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;
	int vexnum, arcnum;//�������뻡��
	GraphKind kind;//ͼ�����ͱ����������޻�ͼ��
}MGraph;

typedef struct Character {
	char content[3];//���ֽṹ��
}Character;

typedef struct buff {//�������ṹ��
	char characters[50];//�ַ�����ʽ�洢���ֵ�
	char freq[10];//�ַ�����ʽ�洢��Ƶ
	char attr[5];//�ַ�����ʽ�洢����
	unsigned int frequency;
	double idf;
}buff;

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//·������ṹ��
typedef int ShortPathTable[MAX_VERTEX_NUM];//���·�����ṹ��
typedef bool Final[MAX_VERTEX_NUM];//�Ƿ������·��

typedef bool PreNode[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//��¼ÿ�������N���·����ֱ��ǰ��
typedef unsigned int CumulativeWeight[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//��¼��ÿ������N���·��Ȩֵ֮��

void Initialize_DN(MGraph &G,int vexnum, int arcnum) {//��ʼ�������޻�ͼ
	for (int i = 0; i <= vexnum; i++) {//��ʼ��n+1����������±�
		G.vexs[i].index = i;
	}

	for (int i = 0; i <= vexnum; i++) {//n+1�����
		for (int j = 0; j <= vexnum; j++) {//�������ڶ���֮�������
			if (i + 1 == j) {
				G.arcs[i][j].adj = 1;//Ȩֵ��������Ϊ1
			}
			else G.arcs[i][j] = { INFINITY};
		}
	}
	G.vexnum = vexnum;
	G.arcnum = arcnum;
	G.kind = DN;
}

//������·��
void ShortestPath(MGraph G, PathMatrix &P, ShortPathTable &D, Final &final, Character *p) {
	int i = 0, j, v, w, min;
	int v0 = 0;
	for (v = 0; v < G.vexnum; ++v) {
		final[v] = FALSE;
		D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; ++w)  P[v][w] = FALSE;  // ���·��
		if (D[v] < INFINITY) { P[v][v0] = TRUE;  P[v][v] = TRUE; }
	}
	D[v0] = 0;  final[v0] = TRUE;        // ��ʼ����v0��������S��
	//--- ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��������v��S�� ---
	for (i = 1; i < G.vexnum; ++i) {         // ����G.vexnum-1������
		min = INFINITY;                    // ��ǰ��֪��v0������������
		for (w = 0; w < G.vexnum; ++w)
			if (!final[w])                           // w������V-S��
				if (D[w] < min) { v = w;  min = D[w]; }  // w������v0�������
		final[v] = TRUE;                       // ��v0���������v����S��
		for (w = 0; w < G.vexnum; ++w)             // ���µ�ǰ���·��������
			if (!final[w] && (min + G.arcs[v][w].adj < D[w])) {
				// �޸�D[w]��P[w], w��V-S
				D[w] = min + G.arcs[v][w].adj;
				for (j = 0;j < G.vexnum;j++) P[w][j] = P[v][j]; //��v�и�ֵ�ڵ�w��
				P[w][w] = TRUE;   // P[w] = P[v]+[w]
			}
	}


	printf("1-���·���ִʽ����\n");
	for (int i = 0; i < G.vexnum - 1; i++) {
		if (P[G.vexnum - 1][i]) printf("/");
		printf("%s", (p + i)->content);
	}
	putchar('/');
	putchar('\n');
	putchar('\n');
	putchar('\n');
}



//���Ӳ�ͬ�Ļ�
void CreateArc(MGraph &G, buff *set, Character *p, char *sentence, int numOfcharacters) {
	int interval = 0;//��¼��������
	for (int i = 0; i < MAX_DICT_SIZE; ++i) {//�����ʵ�
		if (strstr(sentence, set[i].characters)) {//��������еĴʳ����������
			for (int j = 0; j <= numOfcharacters; ++j) {//��������
				if (strstr(set[i].characters, (p + j)->content)) {//���ڴʵ���Ŀ�У���¼λ��
						interval = strlen(set[i].characters) / 2;//���ָ���
						if (strlen(set[i].characters) >= 2) {

							if (strlen(set[i].characters) == 2) {//���ƥ��һ������
								G.arcs[j][j + interval].adj = set[i].frequency;
							}

							if (strlen(set[i].characters) > 2) {//���ƥ��һ������
								for (int k = j; k <= numOfcharacters - interval;k++) {//�ҵ��Ӵ������дʵ�λ��
									if (strstr(set[i].characters, (p + k)->content) && strstr(set[i].characters, (p + k + interval - 1)->content)) {
										G.arcs[k][k + interval].adj = set[i].frequency;//�Ƚ���β�����жϼӱ�λ��
									}
								}
							}
						}
				}
			}
		}
	}
}



//���N���·��������ҳ������޻�ͼ�е�����·����
void NShortestPath(MGraph &G, Character *p) {
	//�������N-���·��

	bool* is_in_stack = new bool[G.vexnum + 1]();//��ջ״̬����
	stack<int>vertex_stack;
	int current_position = 0;//�����ջ���
	vector<vector<int>>paths;//�洢����·��
	vector<int>path;//�洢����·��

	vertex_stack.push(0);//�����ջ
	is_in_stack[0] = 1;//�����������ջ��1��ʾ��ջ�У�0 ��ʾ����
	int top_element;//��¼ջ��Ԫ��
	int tmp;
	while (!vertex_stack.empty())//��ջ���ǿ�
	{
		top_element = vertex_stack.top();//�鿴ջ��Ԫ�أ��ж��Ƿ��Ѿ������յ�
		if (top_element == G.vexnum)//�������յ㣬���·��������ջ�������㣬���ó�ջ״̬
		{
			while (!vertex_stack.empty())
			{
				tmp = vertex_stack.top();//�洢������ջ��ջ��Ԫ��
				vertex_stack.pop();//��ջ
				path.push_back(tmp);//ѹ��·��
			}
			paths.push_back(path);//��·������·����

			for (vector<int>::reverse_iterator rit = path.rbegin(); rit != path.rend(); rit++)
			{//����һ�������������������path������path�н�㰴���������У�
				vertex_stack.push(*rit);
			}
			path.clear();//���·��

			vertex_stack.pop();//ջ�����֣�ĩ�˽ڵ㣩����ջ��
			is_in_stack[top_element] = 0;//ĩ�˽ڵ㲻��ջ��
			current_position = vertex_stack.top();//�ҵ���һ��·���ϵ����ڶ����ڵ��λ��

			top_element = vertex_stack.top();//��ȡ��Ϣ���õ����ڶ����ڵ��ջ
			vertex_stack.pop();//��ĳЩ����²���ջ�ᵼ����ѭ��
			is_in_stack[top_element] = 0;
		}
		else
		{
			int i = 0;//�����ڽӾ������õ��α�
			for (i = current_position + 1; i <= G.vexnum + 1; i++)//�ӵڶ����ڵ㿪ʼ
			{
				if (is_in_stack[i] == 0 && G.arcs[top_element][i].adj != INFINITY)//δ��ջ�����ҽڵ�֮���б�����
				{
					is_in_stack[i] = 1;//stack In
					vertex_stack.push(i);//��ջ
					current_position = 0;//λ������
										 //��ջ��Ԫ�ص�������������Ȼ���㿪ʼ������©���ڵ�
					break;
				}
			}

			if (i == G.vexnum + 2)//�ý�����յ㲻��ͨ
			{
				top_element = vertex_stack.top();
				is_in_stack[top_element] = 0;
				current_position = vertex_stack.top();//����·���ϵ�ǰһ���
				vertex_stack.pop();//��ջ
			}
		}
	}

	//�������������paths�����е�����(������)
	printf("N-���·���ִʽ����\n");
	for (int i = 0; i < paths.size(); i++)
	{
		unsigned int total = 0;//�����ܴ�Ƶ��·�����ȣ�
		bool PathVector[MAX_VERTEX_NUM];

		for (int j = paths[i].size() - 1; j >= 1; j--) {//����·������
			int x = paths[i][j];
			int y = paths[i][j - 1];
			total += G.arcs[x][y].adj;
		}
		printf("·�� %d:", paths.size() - i);

		for (int k = paths[i].size() - 1; k >= 1; k--) PathVector[paths[i][k]] = TRUE;//��¼�ָ������λ��
		for (int col = 0; col < G.vexnum - 1; col++) {//����ִʽ��
			if (PathVector[col]) printf("/");
			printf("%s", (p + col)->content);
		}
		putchar('/');
		
		putchar('\t');
		printf("�ܴ�Ƶ: %d", total - 1);
		putchar('\n');

		memset(PathVector, FALSE, sizeof(PathVector));//���÷ָ������λ��
	}

}