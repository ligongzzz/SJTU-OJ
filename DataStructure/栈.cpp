//ջ�� By @ligongzzz
//����ʱ�䣺2019��2��15��


#include "iostream"
using namespace std;

template <class T>
class mStack {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node* head = nullptr;
	size_t _size = 0;

public:
	//���캯��
	mStack() {
		head = new node;
	}
	//�ж��Ƿ�Ϊ��
	bool empty() {
		return head->next == nullptr;
	}
	//����
	void push(const T& val) {
		head->data = val;
		auto temp = new node;
		temp->next = head;
		head = temp;
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
	//��ǰ
	T & top() {
		//��ȫ��ʩ
		if (head->next == nullptr)
			return;
		return head->next->data;
	}
	//��С
	size_t size() {
		return _size;
	}

	//������
	class iterator {
		node* val = nullptr;
		friend iterator mStack<T>::begin();
		friend iterator mStack<T>::end();
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
		bool operator==(const iterator & other) const {
			return val == other.val;
		}
		bool operator!=(const iterator & other) const {
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