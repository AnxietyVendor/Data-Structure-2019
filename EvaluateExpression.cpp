#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1


//------------------------------------------------------------------------------------
#define STACK_INIT_SIZE 100//�洢�ռ��ʼ����
#define STACKINCREMENT 10//�洢�ռ��������
#define LENGTH 100//����ռ��ʼ������ 

//������ջ�Ľṹ�� 
typedef struct{
	char *base;
	char *top;
	int stacksize;
}OPTR_stack;

//������ջ�Ľṹ��
typedef struct{
	double *base;
	double *top;
	int stacksize;
}OPND_stack;

//������ջ�ĳ�ʼ�� 
void Init_OPTR_stack(OPTR_stack &s){
	s.base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if(!s.base) printf("OPTR_stack Initiation Failed\n");
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

//������ջ�ĳ�ʼ�� 
void Init_OPND_stack(OPND_stack &s){
	s.base = (double*)malloc(STACK_INIT_SIZE * sizeof(double));
	if(!s.base) printf("OPND_stack Initiation Failed\n");
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

//������ջ��ջ 
void OPTR_stack_Push(OPTR_stack &s, char elem){
	if(s.top - s.base >= s.stacksize){
		s.base = (char*)realloc(s.base, STACKINCREMENT * sizeof(char));
		if(!s.base) printf("OPTR_stack Increment Failed\n");
		
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	*s.top++ = elem;
}

//������ջ��ջ
void OPND_stack_Push(OPND_stack &s, double elem){
	if(s.top - s.base >= s.stacksize){
		s.base = (double*)realloc(s.base, STACKINCREMENT * sizeof(double));
		if(!s.base) printf("OPND_stack Increment Failed\n");
	
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;
	}
	*s.top++ = elem;
} 

//������ջ��ջ 
void OPTR_stack_Pop(OPTR_stack &s, char &elem){
	if(s.base == s.top) printf("OPTR_stack Empty\n");
	elem = *(--s.top);
} 

//������ջ��ջ 
void OPND_stack_Pop(OPND_stack &s, double &elem){
	if(s.base == s.top) printf("OPND_stack Empty\n");//
	elem = *(--s.top);
}

//ȡ������ջջ��Ԫ�� 
char OPTR_stack_Top(OPTR_stack &s){
	if(s.base == s.top) printf("OPTR_stack Empty\n");
	return *(s.top - 1);
} 

// ȡ������ջջ��Ԫ��
double OPND_stack_Top(OPND_stack &s){
	if(s.base == s.top) printf("OPND_stack Empty\n");
	return *(s.top - 1);
}

//���㺯��
double Operate(double operand1, char _operator, double operand2){
	switch(_operator){
		case'+':return operand1 + operand2;break;
		case'-':return operand1 - operand2;break;
		case'*':return operand1 * operand2;break;
		case'/':return operand1 / operand2;break;
		case'^':return pow(operand1, operand2);break;
		default:return 0;
	}
} 
 
//�������жϺ��� 
bool Ischar(char ch){
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#' || ch == '^')
	return 1;
	else return 0;
} 

bool Isnum(char num){
	if(num >= '0' && num <= '9') return 1;
	else return 0;
} 

//��������ȼ��� 
unsigned char prior_table[][8] ={
                {'>', '>', '<', '<', '<', '>', '>', '<'},
                {'>', '>', '<', '<', '<', '>', '>', '<'},
                {'>', '>', '>', '>', '<', '>', '>', '<'},
                {'>', '>', '>', '>', '<', '>', '>', '<'},
                {'<', '<', '<', '<', '<', '=', ' ', '<'},
                {'>', '>', '>', '>', ' ', '>', '>', '>'},
                {'<', '<', '<', '<', '<', ' ', '=', '<'},
                {'>', '>', '>', '>', '<', '>', '>', '>'}
               };

//���ȼ����� 
char Precede(char optr1, char optr2){
	int row;
	int col;
		
	switch(optr1){
		case '+':row = 0;break;
		case '-':row = 1;break;
		case '*':row = 2;break;
		case '/':row = 3;break;
		case '(':row = 4;break;
		case ')':row = 5;break;
		case '#':row = 6;break;
		case '^':row = 7;break;
	}
	
	switch(optr2){
		case '+':col = 0;break;
		case '-':col = 1;break;
		case '*':col = 2;break;
		case '/':col = 3;break;
		case '(':col = 4;break;
		case ')':col = 5;break;
		case '#':col = 6;break;
		case '^':col = 7;break;		
	}
	
	return prior_table[row][col];
}  

//�ַ����ṹ�� 
typedef struct string{
	char value[1000];
	int length;
}string;

//��ʷ�����洢ջ
typedef struct{
	string* base;
	string* top;
	int stacksize;
}function_stack; 

//����ջ��ʼ�� 
void Init_Function_stack(function_stack &s){
	s.base = (string*)malloc(STACK_INIT_SIZE * sizeof(string));
	if(!s.base) printf("Function_stack Initiation Failed\n");
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
}

//������ջ 
void Function_stack_Push(function_stack &s, string elem){
	if(s.top - s.base >= s.stacksize){
		s.base = (string*)realloc(s.base, STACKINCREMENT * sizeof(string));
		if(!s.base) printf("Function_stack Increment Failed\n");
		
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	*s.top++ = elem;	
} 

//������ջ
void Function_stack_Pop(function_stack &s, string &elem){
	if(s.base == s.top) printf("Function_stack Empty\n");
	elem = *(--s.top);
} 
 
//��ȡ����ջջ��Ԫ�� 
string Function_stack_Top(function_stack &s){
	if(s.base == s.top) printf("Function_stack Empty\n");
	return *(s.top - 1);
} 


//string�ṹ���ʼ�� 
void Init_string(string &s){
	//printf("�����ַ���\n");
	gets(s.value);
	s.length = strlen(s.value);	
} 

//����next���� 
void GetNext(string T, int next[]){
	int i,j;
	i = 0;//ָ���ַ���ÿ���ַ����±�
	j = -1;
	next[i] = j;//��next[0]��Ϊ0
	while(i < T.length){
		if(j == -1 || T.value[i] == T.value[j])
		{++i; ++j; next[i] = j;}
		else j = next[j];
	} 

}

//kmp����,����������ģʽ�������±� 
int KMP(string S, string T, int next[]){//����������ģʽ����next����
	int i,j;
	i = j = 0;
	while(i < S.length && j < T.length){//iΪ�����±꣬jΪģʽ���±� 
		if(j == -1 || S.value[i] == T.value[j])
		{++i; ++j;}
		else j = next[j];
	}
	if(j == T.length) return i - T.length;
	else return -1;
} 


//�ַ���������(�������ַ����еı������滻Ϊ������ֵ)
void VariableExchange(string variable, string &expression, string key, int index){//��expression�ַ��������ҵ�variable���飬���滻Ϊkey����  
	if(variable.length == key.length){//�������ͱ���ֵ�ȳ�ʱ 
		for(int i = 0;i < variable.length;i++){
			expression.value[i + index] = key.value[i];
		}
	}
	
	if(variable.length < key.length){//��������ֵ�̣���Ҫ��������֮��Ĳ��ֺ���
		expression.length = expression.length + key.length - variable.length;
		
		for(int i = expression.length;i >= index + variable.length;i--){
			expression.value[i + (key.length - variable.length)] = expression.value[i];
		}
		for(int j = 0;j < key.length;j++){//��� 
			expression.value[j + index] = key.value[j];
		} 
	}
	
	if(variable.length > key.length){//��������ֵ������Ҫ��������֮��Ĳ���ǰ��
		
		for(int i = index + variable.length;i < expression.length;i++){
			expression.value[i - (variable.length - key.length)] = expression.value[i];
		}
		for(int k = expression.length + key.length - variable.length;k < expression.length;k++) expression.value[k] = '\0';
		
		expression.length = expression.length + key.length - variable.length;
		
		
		
		for(int j = 0;j < key.length;j++){//��� 
			expression.value[j + index] = key.value[j];
		} 
	}
} 

void MonoVariableSwap(string &expression, string variable, string key){
	int *next = (int *)malloc(variable.length * sizeof(int));
	int index;
	GetNext(variable,next);
	index = KMP(expression,variable,next);
	VariableExchange(variable,expression,key,index);
}

//ϸ�ڴ���
void Detail(string &expression){
/*	putchar('!');
	string special1;
	special1.length = 2;
	special1.value[0] = '(';
	special1.value[1] = '-';	
	
	string key1;
	key1.length = 3;
	key1.value[0] = '(';
	key1.value[1] = '0';
	key1.value[1] = '-';	
	MonoVariableSwap(expression,special1,key1);

	string special2;
	special2.length = 2;
	special2.value[0] = '-';
	special2.value[1] = '-';
	
	string key2;
	key2.length = 1;
	key2.value[0] = '+';
	MonoVariableSwap(expression,special2,key2);

	string special3;
	special3.length = 2;
	special3.value[0] = '-';
	special3.value[1] = '-';
	
	string key3;
	key3.length = 1;
	key3.value[0] = '+';
	MonoVariableSwap(expression,special3,key3);
*/	
	string special4;
	special4.length = 2;
	special4.value[0] = '+';
	special4.value[1] = '-';
	
	string key4;
	key4.length = 1;
	key4.value[0] = '-';
	MonoVariableSwap(expression,special4,key4);
} 	
	
	




//�ַ�������
 

void EvalueExpression(char* expression){
	char Operator;
	int i = 0, precision = -1, head = 0;
	double combine, operand1, operand2, string_num;
	
	OPTR_stack OPTR;
	Init_OPTR_stack(OPTR);//��ʼ��������ջ 
	
	OPND_stack OPND;
	Init_OPND_stack(OPND);//��ʼ��������ջ 
	
	OPTR_stack_Push(OPTR,'#');//�������ջ��ѹ��'#' 
	puts(expression);

	while(expression[i] != '#' || OPTR_stack_Top(OPTR) != '#'){ 
		//putchar('!');
		if(Isnum(expression[i])){//�����ǰ�ַ������� 
			string_num = 0;//���յ���ջԪ��
			while(Isnum(expression[i])||expression[i] == '.'){//δ����whileѭ�� 
				if(expression[i] == '.')
				head = 1;//ʶ��С������ʼ��¼���� 
				else string_num = string_num * 10 + expression[i] - '0';//����ֵ�ַ�ת��Ϊ��Ӧ����
				
				if(head) precision++;//С��λ����һ 
				i++;//�α����						
			}//��ʱ��expression[i]�������� 
			if(precision != -1) string_num = string_num / pow(10,precision);//���ݼ�¼�ľ��Ƚ�������Ϊ������ 
			//printf("��ջ������OPND:%lf\n",string_num);
			OPND_stack_Push(OPND, string_num);
			precision = -1;head = 0;//�ָ����Ⱥ�ʶ���Ĭ��ֵ 
			}
		else{//�����ǰ�ַ��������� 
			switch(Precede(OPTR_stack_Top(OPTR), expression[i])){
				case'<'://printf("��ջ��������%c\n",expression[i]);
						OPTR_stack_Push(OPTR,expression[i]);i++;break;
				
				case'>':
						OPTR_stack_Pop(OPTR,Operator);
						//printf("��ջ��������%c\n", Operator);
						OPND_stack_Pop(OPND,operand1);
						//printf("��ջ������2��%lf\n",operand1);	
						OPND_stack_Pop(OPND,operand2);
						//printf("��ջ������2��%lf\n",operand2);
						combine = Operate(operand2, Operator, operand1);
						//printf("��ջ������:%lf\n",combine);
						OPND_stack_Push(OPND, combine); 
						break;
				
				case'=':OPTR_stack_Pop(OPTR,Operator);
						i++;
						break; 
			} 
		}
	}
	 
	printf("%.6lf\n",OPND_stack_Top(OPND));	
}
 

int main(){
	printf("����1���뵥������ֵģʽ\n");
	printf("����2������ʽ��ֵģʽ\n");
	printf("����3���뺯���Զ���ģʽ\n");
	printf("����4������ʷ����\n"); 	
	printf("����5�˳�������\n");

	//������ʷ����
	function_stack History;//������ʷ�洢ջ 
	//Init_Function_stack(History);//��ʼ��������ʷ�洢ջ 
	
	 
	string function_history;//��ʷ���� 
	string variable_history;//��ʷ������ 
	int count_history; 

	loop:int mode;
	printf("---------------------------------------------------------\n");
	scanf("%d",&mode);
	getchar();
	
	if(mode==1){
	//��������ֵģʽ 
	int count = 0;//��¼�������� 
	printf("�����������\n");
	
	string variable;
	Init_string(variable);
	
	printf("���뵥����������\n"); 
	scanf("%d",&count);	
	getchar(); 	
	
	printf("������ʽ��\n"); 
	string expression;
	Init_string(expression);
	
	printf("������ֵΪ��\n");
	string key;
	Init_string(key);

	for(int j = 0;j < count;j++) MonoVariableSwap(expression,variable,key);
	puts(expression.value);

	EvalueExpression(expression.value);
	
	goto loop;
	} 
	
	if(mode == 2){
	//���ʽ��ֵ 
	printf("������ʽ��\n"); 
	string expression;
	Init_string(expression);
	//puts(expression.value);
	Detail(expression);
	EvalueExpression(expression.value);	
	
	goto loop;
	}
	
	if(mode == 3){
	//��������ģʽ 
	
	
	//�����ʷ��¼
	//function_history.length;//��ʷ���� 
	//string variable_history;//��ʷ������ 
	count_history = 0; 
	int count = 0;//��¼�������� 
	printf("�����������\n");
	
	string variable;//��������ʼ�� 
	Init_string(variable);
	
	variable_history.length = variable.length;//������ʷ���� 
	strcpy(variable_history.value,variable.value);
	
	
	printf("���뵥����������\n"); 
	scanf("%d",&count);
	++count;
	count_history = count; 
	getchar(); 
	//printf("%d",count);	
	
	printf("���뺯�����ʽ��\n");
	printf("DEF "); 
	
	string function;//���溬�������ĺ������ʽ 
	Init_string(function);
	//puts(function.value);
	
	//��¼��ʷ���� 
	string history;
	function_history.length = function.length;
	strcpy(function_history.value,function.value);
	
	//Function_stack_Push(History, function_history);//��ʷ������ջ 
	
	
	printf("������ֵΪ��\n");
	string key;
	Init_string(key);
	
 
	//�滻�������ʽ�еı���ֵ 
	for(int j = 0;j < count;j++) {
		MonoVariableSwap(function,variable,key);
	}	
	puts(function.value);	
	
	printf("RUN ");
	string expression;
	
	int mark = 0;
	for(;function.value[mark] != '=';mark++) putchar(function.value[mark]);
	++mark;
	
	putchar('\n');
	
	for(int i = 0;mark < function.length;i++,mark++){
		expression.length++;
		expression.value[i] = function.value[mark];
	}
	puts(expression.value);
	
	Detail(expression);
	putchar('!');
	puts(expression.value);
	
	
	EvalueExpression(expression.value); 
	goto loop;
	} 
	
	if(mode == 4){
	
	char flag = 1;
	//puts(Function_stack_Top(History));//��ʾ��ʷ����
	puts(function_history.value);//��ʾ��ʷ����
	

	string neo_function;
	neo_function.length = function_history.length;
	strcpy(neo_function.value,function_history.value);

	/*
	puts(Function_stack_Top(History).value);//��ʾ��ʷ����
	string neo_function;//������ʷջ�еĺ��� 
	neo_function.length = Function_stack_Top(History).length;
	strcpy(neo_function.value,Function_stack_Top(History).value);
	
	printf("�Ƿ�Ϊ����Ȥ����ʷ����?����������1��������������0\n");
	flag = getchar();
	while(flag == '0'){
		Function_stack_Pop(History,neo_function);
		neo_function.length = Function_stack_Top(History).length;
		strcpy(neo_function.value,Function_stack_Top(History).value);
		puts(neo_function.value);
		printf("�Ƿ�Ϊ����Ȥ����ʷ����?����������1��������������0\n");
		flag = getchar();	
	}
	*/
	printf("������ֵΪ��\n");
	string neo_key;
	Init_string(neo_key);

	for(int j = 0;j < count_history;j++) MonoVariableSwap(neo_function,variable_history,neo_key);

	printf("RUN ");
	
	string expression;
	
	int mark = 0;
	for(;neo_function.value[mark] != '=';mark++) putchar(neo_function.value[mark]);
	++mark;
	
	putchar('\n');
	
	for(int i = 0;mark < neo_function.length;i++,mark++){
		expression.length++;
		expression.value[i] = neo_function.value[mark];
	}
	//puts(expression.value);
	
	EvalueExpression(expression.value);

	
	goto loop;
	}

	//�˳� 
	if(mode == 5) return 0;
	
	
} 
