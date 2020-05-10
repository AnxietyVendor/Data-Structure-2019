#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct{
	unsigned int weight;//���Ȩ�� 
	unsigned int parent,lchild,rchild;//ָ����
	char data;
	char code[10000]; 
}HTNode, *HuffmanTree;

typedef char* *HuffmanCode;//��̬��������洢�շ�������� 

void Select(HuffmanTree &HT, int limit, int &index1, int &index2){
//ѡ��parentΪ0��weight��С��������㣬��ŷֱ���s1��s2
	int temp1 = 99998, temp2 = 99999;
	for(int i = 1;i <= limit;i++){
		if(HT[i].parent == 0){
			if(HT[i].weight < temp1){
				temp1 = HT[i].weight;
				index1 = i;				
			}
		}
	} 
			
	for(int i = 1;i <= limit;i++){
		if(HT[i].parent == 0 && i != index1){
			if(HT[i].weight < temp2){
				temp2 = HT[i].weight;
				index2 = i;				
			}
		}	
	}
}

//Huffman���뺯�� 
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
	if(n <= 1) return;
	int s1,s2;
	int m = 2*n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HTNode* p;
	int i;
	for(p = HT + 1, i = 1;i <= n;++i, ++p, ++w){
		p->weight = *w;
		p->lchild = 0;
		p->rchild = 0;
		p->parent = 0;
	}

	for(;i <= m;++i, ++p){
		p->weight = 0;
		p->lchild = 0;
		p->rchild = 0;
		p->parent = 0;		
	}	
		
	for(i = n + 1;i <= m;++i){//���շ����� 
		Select(HT, i-1, s1, s2);//ѡ��parentΪ0��weight��С��������㣬��ŷֱ���s1��s2
		HT[s1].parent = i;HT[s2].parent = i;
		HT[i].lchild = s1;HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//���Huffman���Ĵ洢 
	printf("�洢�ṹ���ݣ�\n");
	printf("weight parent lchild rchild\n");
	for(int j =1;j <= m;j++){
		printf("%d     %d     %d     %d\n",HT[j].weight,HT[j].parent,HT[j].lchild,HT[j].rchild);
	}
	
 	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));//����n���ַ������ͷָ������
	char* cd = (char*)malloc(n * sizeof(char));//���������Ĺ����ռ�
	cd[n - 1] = '\0';//���������
	int start;
	for(i = 1;i <= n;i++){
		start = n - 1;//ָ�����ռ�ĩ��
	for(int c = i,f = HT[i].parent;f != 0;c = f, f = HT[f].parent){//��Ҷ�ӵ����������
		if(HT[f].lchild == c) cd[--start] = '0';
		else cd[--start] = '1';
		}
	HC[i] = (char *)malloc((n - start) * sizeof(char));//Ϊ��i���ַ��������ռ�
	strcpy(HC[i], &cd[start]);//�������cd��ֵ��HC[i]
	}
	free(cd);
	putchar('\n'); 
	printf("ԭ��  ����\n");
 	for(int i = 1;i <= n;i++){
 		printf("%c      %s\n",HT[i].weight,HC[i]); 	
 		HT[i].data = (char)HT[i].weight;
 		strcpy(HT[i].code,HC[i]);
	} 
} 


//���Huffman����� 
void CodeTable_Printer(HuffmanTree &HT, int n){
	printf("in\n");
	for(int i =1;i <= n;i++){
		printf("%d %d %d %d\n",HT[i].weight,HT[i].lchild,HT[i].rchild,HT[i].parent);
	}
} 

//ȫ��Ȩֵ����
int global_weights[8] = {5,29,7,8,14,23,3,11}; 
int global_char[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}; 

void Encrypt(HuffmanTree HT){
	printf("����������ݣ�\n");
	char* raw;
	gets(raw);
	for(int i = 0;*(raw + i) != '\0';i++){
		for(int j = 1;j <= 52;j++){
			if(isalpha(*(raw + i)) && *(raw + i) == HT[j].data) {
				printf("%s",HT[j].code);	
			}
		}
	}
	putchar('\n');
}

void Decrypt(HuffmanTree HT){
	printf("�������볤�ȣ�\n");
	int length;
	scanf("%d",&length); 
	getchar();//����β���س� 
	char* secret = (char *)malloc(length * sizeof(char));
	printf("�����������(01����)��\n");
	gets(secret);
	
	int pos = 103;
	for(int i = 0;i < length;i++){
		if(secret[i] == '0'){//����
			pos = HT[pos].lchild;
			if(HT[pos].lchild == 0) {
				printf("%c",HT[pos].data); 
				pos = 103;
			}
		}
		if(secret[i] == '1'){//���� 
			pos = HT[pos].rchild;
			if(HT[pos].rchild == 0) {
				printf("%c",HT[pos].data); 
				pos = 103;
			}
		}
	}
	if(pos != 103) printf("Decrypting Failed!\n");
}


int main(){
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, global_char, 52);
	Encrypt(HT);
	Decrypt(HT);
	return 0;
}
