#include "Structure.h"

int main() {
	
	//*****************************************************************************************
	//�����ļ�
	
	FILE *fp = NULL;

	buff set[MAX_DICT_SIZE];//�洢����
	unsigned long long int total = 1;//��¼����

	fp = fopen("C:/Users/mi/Desktop/dict.txt", "r");//��ֻ����ʽ��dict.txt
	if (fp == NULL) {
		perror("call to fopen!");
		exit(1);
	}
	for (int i = 0; i < MAX_DICT_SIZE; i++) {//�������
		fscanf(fp, "%s %s %s\n", set[i].characters, set[i].freq, set[i].attr);
		set[i].frequency = atoi(set[i].freq);
		total += set[i].frequency;
	}

	for (int i = 0; i < MAX_DICT_SIZE; i++) set[i].idf = log(total / set[i].frequency);

	fclose(fp);
	/*
	for (int i = 0; i < 50; i++) {//�������
		printf("%s %s %s\n", set[i].characters, set[i].freq, set[i].attr);
	}
	*/
	//**********************************************************************************************
	//�����ַ���
	char Sentence[Width];

	

	loop:printf("���뺺��\n");
	gets_s(Sentence);
	
	int numOfcharacter = strlen(Sentence)/2;
	int vexnum = numOfcharacter + 1;//n�����ֶ�Ӧn+1������
	int arcnum = vexnum + 1;

	//printf("%d\n",numOfcharacter);//���ֳ���Ϊ2byte

	//�������֣��ַ����飩�����Խṹ�洢��p��ָ�ռ���
	Character* p = (Character*)malloc(numOfcharacter * sizeof(Character));

	for (int i = 0;i < strlen(Sentence);i += 2) {//�Ӵ�ԭ�ӻ�
		(p + i/2)->content[0] = Sentence[i];
		(p + i/2)->content[1] = Sentence[i + 1];
		(p + i/2)->content[2] = '\0';
	}

	//�������1���·��
	MGraph G;
	Initialize_DN(G, vexnum, arcnum);//��ʼ��ͼ

	CreateArc(G, set, p, Sentence, numOfcharacter);
	
	PathMatrix P;
	ShortPathTable D;
	Final final;
	//���1-���·���ִʽ��
	ShortestPath(G, P, D, final,p);
	putchar('\n');
	
	//�������Ȩֵ
	/*
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			printf("%d\t", G.arcs[i][j].adj);
		}
		putchar('\n');
	}*/

	//���N-���·���ִʽ��
	NShortestPath(G, p);
	
	putchar('\n');

	printf("����س��������ִ�\n");
	if (getchar() == '\n') goto loop;

	//system("pause");
	return 0;
}

