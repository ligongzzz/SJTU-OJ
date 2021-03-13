#include "iostream"
#include "vector"
#include "algorithm"
#include "cstdio"
using namespace std;

template <class T>
class myPriorityQueue {
	vector<T> queueData;
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
		queueData.push_back(*new T);
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

//���ڱ������ݵĸ�ʽ
class data_type {
public:
	int val = 0;
	int posa = 0, posb = 0;
	data_type() = default;
	data_type(int val,int posa,int posb):val(val),posa(posa),posb(posb){}
	bool operator<(const data_type& other) const {
		return val < other.val;
	}
};

int a[1000009] = { 0 }, b[1000009] = { 0 };
//�����
myPriorityQueue<data_type> queue_data;
//������ʱ����
data_type data_temp[1000009];
//�����
int ans_data[1000009];

int main() {
	int num;
	scanf("%d", &num);

	for (int i = 0; i < num; ++i)
		scanf("%d", &a[i]);
	for (int i = 0; i < num; ++i)
		scanf("%d", &b[i]);

	sort(a, a + num);
	sort(b, b + num);
	
	//��ʼ����
	for (int i = 0; i < num; ++i) {
		data_type temp(a[0] + b[i], 0, i);
		data_temp[i] = temp;
	}

	queue_data.buildHeap(data_temp,num);

	//���������д��
	for (int i = 0; i < num; ++i) {
		auto temp = queue_data.pop();
		//д���
		ans_data[i] = temp.val;
		//׼����һ��
		if (i < num - 1) {
			++temp.posa;
			temp.val = a[temp.posa] + b[temp.posb];
			queue_data.push(temp);
		}
	}

	//�����
	printf("%d", ans_data[0]);
	for (int i = 1; i < num; ++i)
		printf(" %d", ans_data[i]);

	return 0;
}