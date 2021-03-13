#include "iostream"
#include "cstdio"
#include "cmath"
#include "cstring"
using namespace std;

template <class T>
class mQueue {
	class node {
	public:
		T data;
		node* next = nullptr;
	};
	node* head = nullptr,
		* rear = nullptr;
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
		return head->next->data;
	}
	//���
	T& back() {
		//��ȫ��ʩ
		return rear->data;
	}
};

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
		delete vector_data[size];
		vector_data[size--] = nullptr;
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

//��������
template <class T>
class myBinaryTree {
public:
	class node {
	public:
		T data;
		node *lchild = nullptr, *rchild = nullptr, *parent = nullptr;
	};
	node *root = nullptr;
	node **nodeList = nullptr;
	long long sizeOfTree = 0;

	//������
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}

	void creadNode(int nodeNum, int lchild, int rchild, int data) {
		if (nodeList[nodeNum] == nullptr)
			nodeList[nodeNum] = new node;

		nodeList[nodeNum]->data = data;

		if (lchild != 0) {
			if (nodeList[lchild] == nullptr)
				nodeList[lchild] = new node;
			nodeList[lchild]->parent = nodeList[nodeNum];
			nodeList[nodeNum]->lchild = nodeList[lchild];
		}

		if (rchild != 0) {
			if (nodeList[rchild] == nullptr)
				nodeList[rchild] = new node;
			nodeList[rchild]->parent = nodeList[nodeNum];
			nodeList[nodeNum]->rchild = nodeList[rchild];
		}
	}

	void checkRoot() {
		for (int i = 1; i <= sizeOfTree; i++) {
			if (nodeList[i]->parent == nullptr) {
				root = nodeList[i];
				break;
			}
		}
	}

	//���
	void clear() {
		clear(root);
	}

	void clear(node *p) {
		if (p == nullptr)
			return;
		clear(p->lchild);
		clear(p->rchild);
		delete p;
		p = nullptr;
	}

	//����
	myBinaryTree() {}

	//����
	~myBinaryTree() {
		clear(root);
	}

	//�ж��Ƿ�ǿ�
	bool empty() {
		return root == nullptr;
	}

	//�ж��Ƿ�Ϊ��ȫ������
	bool isCBT() {
		if (empty())
			return false;
		//��α���
		mQueue<node*> treeQueue;
		bool flag = false;
		//�����
		treeQueue.push(root);

		//����
		while (!treeQueue.empty()) {
			//�ȳ���һ��
			node* temp = treeQueue.front();
			treeQueue.pop();

			//�Һ���������û��
			if (temp->lchild == nullptr&&temp->rchild != nullptr)
				return false;

			if (!flag) {
				//�������Һ���û��
				if (temp->lchild != nullptr&&temp->rchild == nullptr) {
					flag = true;
					//�������
					treeQueue.push(temp->lchild);
				}
				//���Һ��Ӷ�û��
				else if (temp->lchild == nullptr&&temp->rchild == nullptr) {
					flag = true;
				}
				//���Ҷ��к���
				else {
					treeQueue.push(temp->lchild);
					treeQueue.push(temp->rchild);
				}
			}
			else {
				//�ж��Ƿ�ΪҶ��
				if (temp->lchild != nullptr || temp->rchild != nullptr)
					return false;
			}
		}

		return true;
	}

	//���ش�С
	long long size() {
		return sizeOfTree;
	}

	//��α���
	mVector<T> levelTraversal() {
		if (sizeOfTree == 0)
			return *new mVector<T>;

		mVector<T> result; 
		mQueue<node*> treeQueue;

		//��������
		treeQueue.push(root);

		//��α���
		while (!treeQueue.empty()) {
			//����
			node* temp = treeQueue.front();
			treeQueue.pop();

			//���
			if (temp->lchild != nullptr)
				treeQueue.push(temp->lchild);
			if (temp->rchild != nullptr)
				treeQueue.push(temp->rchild);

			//д��
			result.push_back(temp->data);
		}

		//����
		return result;
	}

	//ǰ�����
	mVector<T> preorderTraversal() {
		mVector<T> result;
		preorderTraversal(root, result);
		return result;
	}

	void preorderTraversal(node* treeRoot,mVector<T> &result) {
		//��ʾ��ǰ
		result.push_back(treeRoot->data);

		if (treeRoot->lchild != nullptr)
			preorderTraversal(treeRoot->lchild,result);
		if (treeRoot->rchild != nullptr)
			preorderTraversal(treeRoot->rchild,result);
	}

	//�������
	mVector<T> midorderTraversal() {
		mVector<T> result;
		midorderTraversal(root, result);
		return result;
	}

	void midorderTraversal(node* treeRoot, mVector<T> &result) {
		if (treeRoot->lchild != nullptr)
			midorderTraversal(treeRoot->lchild, result);
		//��ʾ��ǰ
		result.push_back(treeRoot->data);
		if (treeRoot->rchild != nullptr)
			midorderTraversal(treeRoot->rchild, result);
	}

	//�������
	mVector<T> lostorderTraversal() {
		mVector<T> result;
		lostorderTraversal(root, result);
		return result;
	}

	void lostorderTraversal(node* treeRoot, mVector<T> &result) {
		if (treeRoot->lchild != nullptr)
			lostorderTraversal(treeRoot->lchild, result);
		if (treeRoot->rchild != nullptr)
			lostorderTraversal(treeRoot->rchild, result);
		//��ʾ��ǰ
		result.push_back(treeRoot->data);
	}
};

//�������ֵܶ�������
template <class T>
class mySpecialBinaryTree {
public:
	class node {
	public:
		T data;
		node *lchild = nullptr, *rbrother = nullptr;
		bool isRoot = true;
	};
	node *root = nullptr;
	node **nodeList = nullptr;
	long long sizeOfTree = 0;

	//������
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}

	void creadNode(int nodeNum, int lchild, int rbrother, int data) {
		if (nodeList[nodeNum] == nullptr)
			nodeList[nodeNum] = new node;

		nodeList[nodeNum]->data = data;

		if (lchild != 0) {
			if (nodeList[lchild] == nullptr)
				nodeList[lchild] = new node;
			nodeList[lchild]->isRoot = false;
			nodeList[nodeNum]->lchild = nodeList[lchild];
		}

		if (rbrother != 0) {
			if (nodeList[rbrother] == nullptr)
				nodeList[rbrother] = new node;
			nodeList[rbrother]->isRoot = false;
			nodeList[nodeNum]->rbrother = nodeList[rbrother];
		}
	}

	void checkRoot() {
		for (int i = 1; i <= sizeOfTree; i++) {
			if (nodeList[i]->isRoot) {
				root = nodeList[i];
				break;
			}
		}
	}

	//���
	void clear() {
		clear(root);
	}

	void clear(node *p) {
		if (p == nullptr)
			return;
		clear(p->lchild);
		clear(p->rbrother);
		delete p;
		p = nullptr;
	}

	//����
	mySpecialBinaryTree() {}

	//����
	~mySpecialBinaryTree() {
		clear(root);
	}

	//�ж��Ƿ�ǿ�
	bool empty() {
		return root == nullptr;
	}

	//���ش�С
	long long size() {
		return sizeOfTree;
	}

	//��α���
	mVector<T> levelTraversal() {
		if (sizeOfTree == 0)
			return *new mVector<T>;

		mVector<T> result;
		mQueue<node*> treeQueue;

		//��������
		treeQueue.push(root);

		//��α���
		while (!treeQueue.empty()) {
			//����
			node* temp = treeQueue.front();
			treeQueue.pop();

			//���
			for (auto p = temp->lchild; p!= nullptr; p = p->rbrother)
				treeQueue.push(p);
		
			//д��
			result.push_back(temp->data);
		}

		//����
		return result;
	}

	//ǰ�����
	mVector<T> preorderTraversal() {
		mVector<T> result;
		preorderTraversal(root, result);
		return result;
	}

	void preorderTraversal(node* treeRoot, mVector<T> &result) {
		//��ʾ��ǰ
		result.push_back(treeRoot->data);

		if (treeRoot->lchild != nullptr)
			preorderTraversal(treeRoot->lchild, result);
		if (treeRoot->rbrother != nullptr)
			preorderTraversal(treeRoot->rbrother, result);
	}

	//�������
	mVector<T> lostorderTraversal() {
		mVector<T> result;
		lostorderTraversal(root, result);
		return result;
	}

	void lostorderTraversal(node* treeRoot, mVector<T> &result) {
		if (treeRoot->lchild != nullptr)
			lostorderTraversal(treeRoot->lchild, result);
		//��ʾ��ǰ
		result.push_back(treeRoot->data);
		if (treeRoot->rbrother != nullptr)
			lostorderTraversal(treeRoot->rbrother, result);
	}
};

int main() {
	int num;
	mySpecialBinaryTree<int> bTree;
	cin >> num;
	bTree.createTree(num);

	for (int i = 1; i <= num; i++) {
		int lchild, rchild, nodeData;
		scanf("%d %d %d", &lchild, &rchild, &nodeData);
		bTree.creadNode(i, lchild, rchild, nodeData);
	}

	bTree.checkRoot();
	auto ans = bTree.preorderTraversal();

	cout << ans[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans[i]);
	auto ans1 = bTree.lostorderTraversal();

	cout << endl;

	cout << ans1[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans1[i]);

	auto ans2 = bTree.levelTraversal();

	cout << endl;

	cout << ans2[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans2[i]);

	return 0;
}