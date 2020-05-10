//Array.h
#ifndef ARRAY_H
#define ARRAY_H
#include<cassert>

//������ģ�嶨��
template<class T>
class Array{
private:
	T* list;//T����ָ�룬��Ŷ�̬����������ڴ��׵�ַ 
	int size;//����Ԫ�ظ��� 
public:
	Array(int sz = 500);//���캯�� 
	Array(const Array<T> &a);//���ƹ��캯��
	~Array();
	Array<T>& operator=(const Array<T> &rhs);//���ء�=��ʹ������������帳ֵ
	T& operator [] (int i);//���ء�[]����ʹArray�����������ͨC++���������
	const T& operator [] (int i)const;//"[]" �������const��������
	operator T*() const;//��T*���͵�ת����ʹArray�����������ͨC++��������� 
	operator const T*() const;//��T*����ת�����������const������
	int getSize() const;//ȡ����Ĵ�С
	void resize(int sz);//�޸������С
};

//���캯��
template<class T>
Array<T>::Array(int sz){
	assert(sz>=0);//�쳣���� 
	size = sz;
	list=new T [size]; 
} 

//��������
template<class T>
Array<T>::~Array(){
	delete list [];
} 

//���ƹ��캯��
template<class T>
Array<T>::Array(const Array<T> &a){
	size = a.size;
	list = new T[size];
	for(i = 0;i<size;i++){
		list[i] = a.list[i];
	} 
	
//����"=���������������rhs��ֵ��������ʵ�ֶ���֮������帳ֵ
template<class T>
Array<T>& Array<T>::operator=(const Array<T> &rhs){
	if(&rhs != s){
		if(size!= rhs.size){
			delete [] list;
			size = rhs.size;
			list = new T [size];
		}
		for(int i = 0;i<size;i++){
			list[i]=rhs.list[i];
		}
	}
	return *this;
} 

//�����±��������ʵ������ͨ����һ��ͨ���±����Ԫ�أ����Ҿ���Խ���鹦��
template<class T>
T& Array<T>::operator[] (int n){
	assert(n>=0 && n<=size);
	return list[n];
} 

template<class T>
const T& Array<T>::operator[](int n) const{
	assert(n>=0 && n<=size);
	return list[n];
}

//����ָ��ת�����������Array��Ķ�����ת��ΪT���͵�ָ��
//ָ��ǰ�����˽������
//���������ʹ����ͨ�����׵�ַһ��ʹ��Array��Ķ�����
template<class T>
Array<T>::operator const T*() const{
	return list;
} 

//ȡ��ǰ����Ĵ�С
template<class T>
int Array<T>::getSize() const{
	return size;
} 

//�������С�޸�Ϊsz
template<class T>
void Array<T>::resize(int sz){
	assert(sz>=0);
	if(sz==size)
		return;
	T* newList = new T [sz];


	int n = (sz<size?)sz:size;
	for(int i = 0;i<n;i++){
		newList[i] = list[i];
	delete [] list;
	list = newList;
	size = sz;
	}
} 
#endif //ARRAY_H
