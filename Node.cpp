//Node.h
#ifndef NODE_H
#define NODE_H

//��ģ��Ķ���
template<class T>
class Node{
private:
	Node<T>* next;//ָ���� 
public:
	T data;//������ 
	
	Node(const T& data,Node<T>* next = NULL);//���캯�� 
	void insertAfter(Node<T>* p);
	void insertBefore(Node<T>* q);
	Node<T>* deleteAfter();//ɾ����̽ڵ� 
	Node<T>* nextNode();//��ȡ��̽ڵ�ĵ�ַ
	const Node<T>* nextNode() const;//��ȡ�������ĵ�ַ 
}; 

//���ʵ�ֲ���
//���캯������ʼ�����ݺ�ָ���Ա
template<class T>
Node<T>::Node(const T& data, Node<T>* next/* = 0*/):data(data),next(next){}

//���غ�̽ڵ��ָ��
template<class T>
Node<T>* Node<T>::nextNode(){
	return next;
} 

//���غ�̽ڵ��ָ��
template<class T>
const Node<T>* Node<T>::nextNode() const{
	return next; 
}

//�ڵ�ǰ�ڵ�֮�����һ���ڵ�p
template<class T>
void insertAfter(Node<T>* p){
	this->next = p;
	p->next = next;
} 

//�ڵ�ǰ�ڵ�֮ǰ����һ���ڵ�p 

//ɾ����ǰ�ڵ�ĺ�̽ڵ㣬�����ص�ַ
template<class T>
Node<T>* Node<T>::deleteAfter(){
	Node<T>* tempPtr = next;//��ʱ����nextָ���ַ 
	if(next == 0)//����ýڵ���ĩβ 
		return 0;//����0 
	next = tempPtr->next; //��̽ڵ�Ϊ��β���򷵻�0��������º�̽�� 
	return tempPtr;
} 
