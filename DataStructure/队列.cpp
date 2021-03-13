//������ By @ligongzzz
//����ʱ�䣺2019��2��15��


#include "iostream"
#include "queue"
using namespace std;

template <class T>
class mQueue {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node *head = nullptr,
		*rear = nullptr;
	size_t _size = 0;

public:
	//���캯��
	mQueue() {
		head = new node;
		rear = head;
	}
	//�ж��Ƿ�Ϊ��
	bool empty() {
		return head->next == nullptr;
	}
	//����
	void push(const T& val) {
		rear->next = new node;
		rear = rear->next;
		rear->data = val;
		++_size;
	}
	//ɾ��
	void pop() {
		//��ȫ��ʩ
		if (head->next == nullptr)
			return;
		auto temp = head->next;
		delete head;
		head = temp;
		--_size;
	}
	//��С
	size_t size() {
		return _size;
	}
	//��ǰ
	T& front() {
		//��ȫ��ʩ
		if (head->next == nullptr)
			return;
		return head->next->data;
	}
	//���
	T& back() {
		//��ȫ��ʩ
		if (head->next == nullptr)
			return;
		return rear->data;
	}
	//������
	class iterator {
		node* val = nullptr;
		friend iterator mQueue<T>::begin();
		friend iterator mQueue<T>::end();
	public:
		iterator() = default;
		iterator(const iterator& other) {
			val = other.val;
		}

		iterator& operator++() {
			//��ȫ��ʩ
			if (val == nullptr)
				return *this;
			val = val->next;
			return *this;
		}
		iterator operator++(int) {
			//��ȫ��ʩ
			if (val == nullptr)
				return *this;
			auto temp = *this;
			val = val->next;
			return temp;
		}
		bool operator==(const iterator& other) const{
			return val == other.val;
		}
		bool operator!=(const iterator& other) const {
			return val != other.val;
		}
		T& operator*() {
			return val->data;
		}
	};
	iterator begin() {
		iterator temp;
		temp.val = head->next;
		return temp;
	}
	iterator end() {
		iterator temp;
		temp.val = nullptr;
		return temp;
	}
};