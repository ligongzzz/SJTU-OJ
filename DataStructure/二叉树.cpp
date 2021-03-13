//�������� ���ݽṹģ�� By @ligongzzz
//����ʱ�䣺2019��1��25��


#include "iostream"
#include "cstdio"
#include "queue"
#include "cmath"
#include "stack"
#include "cstring"
using namespace std;

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

	//����һ����Ӧ��С����
	void createTree(int num) {
		nodeList = new node*[num + 1]{ nullptr };
		sizeOfTree = num;
	}
	//������㣨ȫ����ɺ���ҪCheckRoot���и��ڵ�ʶ��
	void createNode(int nodeNum, int lchild, int rchild, T data) {
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
	//����һ��num��С����������ΪtreeData
	void createTree(T* treeData, int num) {
		createTree(num);
		for (int i = 1; i <= num; i++) {
			int lchild = i * 2 <= num ? i * 2 : 0,
				rchild = i * 2 + 1 <= num ? i * 2 + 1 : 0;
			createNode(i, lchild, rchild, treeData[i - 1]);
		}
		checkRoot();
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
		queue<node*> treeQueue;
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

	//������
	class preorderIterator {
		stack<node*> myStack;
		node* currentData = nullptr;
		friend preorderIterator myBinaryTree::preorderBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//��������������Ϊ��
		bool finish() {
			return currentData == nullptr&&myStack.empty();
		}

		preorderIterator& operator++() {
			if (finish())
				return *this;
			if (myStack.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myStack.top();
			myStack.pop();
			if (currentData->rchild != nullptr)
				myStack.push(currentData->rchild);
			if (currentData->lchild != nullptr)
				myStack.push(currentData->lchild);
			return *this;
		}
	};

	preorderIterator preorderBegin() {
		preorderIterator result;
		result.myStack.push(root);
		++result;
		return result;
	}

	class inorderIterator {
		stack<node*> myStack;
		node* currentData = nullptr;
		friend inorderIterator myBinaryTree::inorderBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//��������������Ϊ��
		bool finish() {
			return currentData == nullptr&&myStack.empty();
		}

		inorderIterator& operator++() {
			if (finish())
				return *this;
			if (myStack.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myStack.top();
			myStack.pop();
			for (node* p = currentData->rchild; p != nullptr; p = p->lchild)
				myStack.push(p);
			return *this;
		}
	};

	inorderIterator inorderBegin() {
		inorderIterator result;
		for (node* p = root; p != nullptr; p = p->lchild)
			result.myStack.push(p);
		++result;
		return result;
	}

	class postorderIterator {
		stack<node*> myStack;
		node* currentData = nullptr;
		friend postorderIterator myBinaryTree::postorderBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//��������������Ϊ��
		bool finish() {
			return currentData == nullptr&&myStack.empty();
		}

		postorderIterator& operator++() {
			if (finish())
				return *this;
			if (myStack.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myStack.top();
			myStack.pop();
			if (myStack.empty() || myStack.top()->rchild == currentData)
				return *this;
			for (node* p = myStack.top()->rchild; p != nullptr;) {
				myStack.push(p);
				if (p->lchild != nullptr)
					p = p->lchild;
				else if (p->rchild != nullptr)
					p = p->rchild;
				else
					break;
			}
			return *this;
		}
	};

	postorderIterator postorderBegin() {
		postorderIterator result;
		for (node* p = root; p != nullptr;) {
			result.myStack.push(p);
			if (p->lchild != nullptr)
				p = p->lchild;
			else if (p->rchild != nullptr)
				p = p->rchild;
			else
				break;
		}
		++result;
		return result;
	}

	//�������������
	class levelIterator {
		queue<node*> myQueue;
		node* currentData = nullptr;
		friend levelIterator myBinaryTree::levelBegin();
	public:
		T& get() {
			return currentData->data;
		}
		//��������������Ϊ��
		bool finish() {
			return currentData == nullptr&&myQueue.empty();
		}

		levelIterator& operator++() {
			if (finish())
				return *this;
			if (myQueue.empty()) {
				currentData = nullptr;
				return *this;
			}
			currentData = myQueue.front();
			myQueue.pop();
			if (currentData->lchild != nullptr)
				myQueue.push(currentData->lchild);
			if (currentData->rchild != nullptr)
				myQueue.push(currentData->rchild);
			return *this;
		}
	};

	levelIterator levelBegin() {
		levelIterator result;
		result.myQueue.push(root);
		++result;
		return result;
	}
};
