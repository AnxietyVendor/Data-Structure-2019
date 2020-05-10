#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

template<class T>
class LinkedList{
private:
	//���ݳ�Ա
	Node<T>* front,* rear;//��ͷ���βָ��
	Node<T>* prevPtr, *currPtr;//��¼��ǰ����λ�õ�ָ�룬�������ɾ���������±��е�Ԫ�ظ���
	int size;//���е�Ԫ�ظ���
	int position;//��ǰԪ���ڱ��е�λ����ţ��ɺ���resetʹ��
	
	//������Ա��
	//�����½�㣬������Ϊitem��ָ����ΪptrNext
	Node<T>* newNode(const T& item,Node<T>* ptrNext=NULL);
	
	//�ͷŽ��
	void freeNode(Node<T>* p);
	//������L���Ƶ���ǰ�����赱ǰ��Ϊ�գ�
	//�����ƹ��캯���͡�operator=������
	void copy(const LinkedList<T>& L);
	
public:
	LinkedList();//���캯�� 
	LinkedList(const LinkedList<T>& L);//���ƹ��캯�� 
	~LinkedList();//�������� 
	LinkedList<T>& operator= (const LinkedList<T>& L);//���ظ�ֵ����� 
	
	int getSize() const;//����������Ԫ�صĸ��� 
	bool isEmpty() const;//��������Ƿ�Ϊ�� 
	
	void reset(int pos=0);//��ʼ���α��λ�� 
	void next();//ʹ�α��ƶ�����һ�ڵ� 
	bool endOfList() const;//�α��Ƿ񵽴�����β 
	int currentPosition(void) const;//�����α굱ǰ��λ�� 
	
	void insertFront(const T& item);//�ڱ�ͷ����ڵ� 
	void insertRear(const T& item);//�ڱ�β����ڵ� 
	
	void insertBefore(const T& item);//�ڵ�ǰ�ڵ�֮ǰ������ 
	void insertAfter(const T& item);//�ڵ�ǰ�ڵ�֮������� 
	
	T deleteFront();//ɾ��ͷ���
	void deleteCurrent();//ɾ����ǰ���
	
	T& data();//���ضԵ�ǰ����Ա���ݵ�����
	const T& data() const//���ضԵ�ǰ����Ա���ݵĳ�����
	
	//��������ͷ����н����ڴ�ռ䣬�����������͡�operator=������
	void clear(); 
}; 

#endif //LINKEDLIST_H 
