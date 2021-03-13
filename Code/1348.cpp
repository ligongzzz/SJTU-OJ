#include "iostream"
#include "iomanip"
#include "cstdio"
#include "queue"
#include "vector"
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
		queueData.push_back((T)0);
		sizeOfQueue = 0;
	}

	//compare�������ظ����a�뺢�ӽ��b�Ĺ�ϵ��ȷ���
	myPriorityQueue(bool(*compare)(T a, T b)) :cmp(compare) {
		queueData.clear();
		queueData.push_back((T)0);
		sizeOfQueue = 0;
	}

	//�������齨����
	void buildHeap(T *eleData, unsigned int eleNum) {
		queueData.clear();
		sizeOfQueue = eleNum;
		queueData.push_back((T)0);
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
	void push(const T& input) {
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
		if (sizeOfQueue == 0)
			return NULL;
		return queueData[1];
	}

	//����
	T pop() {
		if (sizeOfQueue == 0)
			return NULL;
		auto temp = queueData[1];
		queueData[1] = queueData[sizeOfQueue--];
		queueData.pop_back();
		percolateDown(1);
		return temp;
	}
};

int main() {
	int N,num;
	cin >> N;
	int *songTime = new int[N];
	for (int i = 0; i < N; i++)
		scanf("%d", &songTime[i]);

	cin >> num;
	myPriorityQueue<int> boy, girl;
	int *boytemp = new int[num+1], *girltemp = new int[num+1],boyNum=0,girlNum=0;
	for (int i = 0; i < num; i++) {
		int sex;
		scanf("%d", &sex);
		if (sex == 1)
			scanf("%d", &boytemp[boyNum++]);
		else
			scanf("%d", &girltemp[girlNum++]);
	}
	//��������
	boy.buildHeap(boytemp, boyNum);
	delete boytemp;
	girl.buildHeap(girltemp, girlNum);
	delete girltemp;

	double boyTotal = 0, girlTotal = 0;

	for (long long currentTime = 0, i = 0; 
		i < N; 
		currentTime += songTime[i], i++) {
		//���һ�׸裬���һ����
		if (i == N - 1) {
			while (!boy.empty())
				boyTotal += currentTime - boy.pop();
			while (!girl.empty())
				girlTotal += currentTime - girl.pop();
		}
		//���CP
		else {
			while (!boy.empty() && !girl.empty() && boy.top() <= currentTime&&girl.top() <= currentTime) {
				boyTotal += currentTime - boy.pop();
				girlTotal += currentTime - girl.pop();
			}
		}
	}	

	//���
	printf("%.2f %.2f",boyTotal / boyNum,girlTotal / girlNum);
	delete songTime;
	return 0;
}
