//���鼯�� ���ݽṹģ�� By @ligongzzz
//����ʱ�䣺2019��2��14��


#include "iostream"
#include "cstring"
#include "set"
#include "queue"
#include "vector"
using namespace std;

//���鼯
class disjointSet {
public:
	//����
	int* parent;
	int length = 0;

	//���캯��
	disjointSet() = default;
	disjointSet(int size) :length(size) {
		parent = new int[size];
		memset(parent, -1, length * sizeof(int));
	}

	//��������
	~disjointSet() {
		length = 0;
		delete[] parent;
	}

	//Ѱ��
	int find(int x) {
		int temp = x;
		for (; parent[temp] >= 0; temp = parent[temp]);
		//ѹ��·��
		for (int i = x; i != temp;) {
			int tempi = parent[i];
			parent[i] = temp;
			i = tempi;
		}
		return temp;
	}
	//�ϲ�
	void set_union(int root1, int root2) {
		if (root1 == root2)
			return;
		if (parent[root1] > parent[root2]) {
			parent[root2] += parent[root1];
			parent[root1] = root2;
		}
		else {
			parent[root1] += parent[root2];
			parent[root2] = root1;
		}
	}
};