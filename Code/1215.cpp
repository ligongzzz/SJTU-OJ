#include "iostream"
#include "cstdio"
#include "cstring"
using namespace std;

template <class T>
class mVector {
	T** vector_data = nullptr;
	unsigned int size = 0;
	unsigned int capacity = 0;

public:
	//���캯��
	mVector() = default;
	mVector(unsigned int _size) :size(_size) {
		capacity = _size * 2;
		vector_data = new T * [capacity] {nullptr};
	}
	mVector(unsigned int _size, const T& val) :size(_size) {
		capacity = _size * 2;
		vector_data = new T * [capacity] {nullptr};
		for (unsigned int i = 0; i < _size; ++i)
			vector_data[i] = new T(val);
	}
	mVector(const mVector<T> & _vector) :size(_vector.size), capacity(_vector.capacity) {
		vector_data = new T * [capacity] {nullptr};
		for (int i = 0; i < size; ++i)
			vector_data[i] = new T(*_vector.vector_data[i]);
	}
	//��������
	~mVector() {
		for (unsigned int i = 0; i < size; ++i)
			delete vector_data[i];
		delete[] vector_data;
	}

	//������
	class iterator {
		T** pos = nullptr;
		friend iterator mVector<T>::begin();
		friend iterator mVector<T>::end();
		friend void mVector<T>::erase(const iterator& val);
	public:
		iterator() = default;
		iterator(const iterator& other) {
			pos = other.pos;
		}
		iterator& operator++() {
			++pos;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++pos;
			return temp;
		}
		iterator& operator--() {
			--pos;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--pos;
			return temp;
		}
		bool operator==(const iterator& other) const {
			return pos == other.pos;
		}
		bool operator!=(const iterator& other) const {
			return pos != other.pos;
		}
		iterator& operator=(const iterator& other) {
			pos = other.pos;
			return *this;
		}
		T& operator*() const {
			return **pos;
		}
	};

	//���������
	template <class U>
	class reverse_iterator {
		U val;
		friend reverse_iterator<U> mVector<T>::rbegin();
		friend reverse_iterator<U> mVector<T>::rend();
	public:
		U& base() {
			return val;
		}
		reverse_iterator() = default;
		reverse_iterator(const reverse_iterator<U>& other) {
			val = other.val;
		}
		reverse_iterator(const U& other) {
			val = other;
		}
		reverse_iterator<U>& operator++() {
			--val;
			return *this;
		}
		reverse_iterator<U> operator++(int) {
			reverse_iterator<U> temp(*this);
			--val;
			return temp;
		}
		reverse_iterator<U>& operator--() {
			++val;
			return *this;
		}
		reverse_iterator<U> operator--(int) {
			reverse_iterator<U> temp(*this);
			++val;
			return temp;
		}
		bool operator==(const reverse_iterator<U>& other) const {
			return val == other.val;
		}
		bool operator!=(const reverse_iterator<U>& other) const {
			return val != other.val;
		}
		reverse_iterator<U>& operator=(const reverse_iterator<U>& other) {
			val = other.val;
			return *this;
		}
		T& operator*() const {
			return *val;
		}
	};

	reverse_iterator<iterator> rbegin() {
		auto temp = end();
		--temp;
		reverse_iterator<iterator> result;
		result.val = temp;
		return result;
	}

	reverse_iterator<iterator> rend() {
		auto temp = begin();
		--temp;
		reverse_iterator<iterator> result;
		result.val = temp;
		return result;
	}

	//����Ԫ��
	void push_back(const T & val) {
		if (size < capacity)
			vector_data[size++] = new T(val);
		else {
			T** temp_data = new T * [(capacity + 1) * 2]{ nullptr };
			for (unsigned int i = 0; i < size; ++i)
				temp_data[i] = vector_data[i];
			temp_data[size++] = new T(val);
			capacity = (capacity + 1) * 2;
			delete[] vector_data;
			vector_data = temp_data;
		}
	}

	//ɾ��ĩβ
	void pop_back() {
		delete vector_data[--size];
		vector_data[size] = nullptr;
	}

	//���
	void clear() {
		for (unsigned int i = 0; i < size; ++i) {
			delete vector_data[i];
			vector_data[i] = nullptr;
		}
		size = 0;
	}

	//ɾ��
	void erase(const iterator & val) {
		delete* val.pos;
		for (auto p = val.pos; p != vector_data + size - 1; ++p)
			* p = *(p + 1);
		--size;
		vector_data[size] = nullptr;
	}

	//���������
	T & operator[](const unsigned int& pos) {
		return *vector_data[pos];
	}

	iterator begin() {
		iterator temp;
		temp.pos = vector_data;
		return temp;
	}

	iterator end() {
		iterator temp;
		temp.pos = vector_data + size;
		return temp;
	}

};

template <class T>
class myPriorityQueue {
	mVector<T> queueData;
	unsigned int sizeOfQueue = 0;
	bool(*cmp)(T a, T b) = [](T a, T b) {return a < b; };

	//���¹���
	void percolateDown(unsigned int pos) {
		while (pos * 2 <= sizeOfQueue) {
			if (pos * 2 + 1 > sizeOfQueue) {
				//����
				if (cmp(queueData[pos * 2], queueData[pos])) {
					auto temp = queueData[pos * 2];
					queueData[pos * 2] = queueData[pos];
					queueData[pos] = temp;
				}
				break;
			}
			else {
				bool minNum = cmp(queueData[pos * 2 + 1], queueData[pos * 2]);
				if (cmp(queueData[pos * 2 + minNum], queueData[pos])) {
					auto temp = queueData[pos * 2 + minNum];
					queueData[pos * 2 + minNum] = queueData[pos];
					queueData[pos] = temp;
					pos = pos * 2 + minNum;
				}
				else break;
			}
		}
	}

public:
	//����
	myPriorityQueue() {
		queueData.clear();
		queueData.push_back((T)0);
		sizeOfQueue = 0;
	}

	//compare�������ظ����a�뺢�ӽ��b�Ĺ�ϵ��ȷ���
	myPriorityQueue(bool(*compare)(T a, T b)) :cmp(compare) {
		queueData.clear();
		queueData.push_back(*new T);
		sizeOfQueue = 0;
	}

	//�������齨����
	void buildHeap(T* eleData, unsigned int eleNum) {
		queueData.clear();
		sizeOfQueue = eleNum;
		queueData.push_back(*new T);
		for (unsigned int i = 1; i <= eleNum; i++)
			queueData.push_back(eleData[i - 1]);
		//���¹���
		for (unsigned int pos = eleNum / 2; pos > 0; pos--)
			percolateDown(pos);
	}

	//�ж��Ƿ��
	bool empty() {
		return sizeOfQueue == 0;
	}

	//���ض��д�С
	auto size() {
		return sizeOfQueue;
	}

	//���
	void push(const T & input) {
		sizeOfQueue++;
		queueData.push_back(input);

		//���Ϲ���
		for (auto i = sizeOfQueue; i > 1; i = i / 2) {
			//�ж��Ƿ�ȸ�����С
			if (cmp(queueData[i], queueData[i / 2])) {
				//����
				auto temp = queueData[i];
				queueData[i] = queueData[i / 2];
				queueData[i / 2] = temp;
			}
			else break;
		}
	}

	//������ǰ
	T top() {
		return queueData[1];
	}

	//����
	T pop() {
		auto temp = queueData[1];
		queueData[1] = queueData[sizeOfQueue--];
		queueData.pop_back();
		percolateDown(1);
		return temp;
	}
};

int main() {
	int M;
	cin >> M;
	myPriorityQueue<int> myQueue;

	for (; M > 0; M--) {
		char temp[100];
		scanf("%s", temp);
		if (strcmp(temp, "insert") == 0) {
			int tempNum;
			scanf("%d", &tempNum);
			myQueue.push(tempNum);
		}
		else if (strcmp(temp, "delete") == 0) {
			if (!myQueue.empty())
				myQueue.pop();
		}
		else {
			printf("%d\n", myQueue.top());
		}
	}

	return 0;
}