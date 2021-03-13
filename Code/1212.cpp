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
		return head->next->data;
	}
	//���
	T& back() {
		return rear->data;
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
	long long sizeOfTree= 0;

	//������
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}

	void creadNode(int nodeNum, int lchild, int rchild,int data) {
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
	T* levelTraversal(){
		if (sizeOfTree == 0)
			return NULL;

		T *result = new T[sizeOfTree];
		mQueue<node*> treeQueue;
		long long pos = 0;
		//��������
		treeQueue.push(root);

		//��α���
		while (!treeQueue.empty()) {
			//����
			node* temp= treeQueue.front();
			treeQueue.pop();

			//���
			if (temp->lchild != nullptr)
				treeQueue.push(temp->lchild);
			if (temp->rchild != nullptr)
				treeQueue.push(temp->rchild);

			//д��
			result[pos++] = temp->data;
		}

		//����
		return result;
	}
};

int main() {
	int num;
	myBinaryTree<int> bTree;
	cin >> num;
	bTree.createTree(num);

	for (int i = 1; i <= num; i++) {
		int lchild, rchild, nodeData;
		scanf("%d %d %d", &lchild, &rchild, &nodeData);
		bTree.creadNode(i, lchild, rchild, nodeData);
	}

	bTree.checkRoot();
	auto ans = bTree.levelTraversal();

	cout << ans[0];
	for (int i = 1; i < bTree.sizeOfTree; i++)
		printf(" %d", ans[i]);

	return 0;
}