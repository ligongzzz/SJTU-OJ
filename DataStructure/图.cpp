//ͼ�� ���ݽṹģ�� By @ligongzzz
//����ʱ�䣺2019��1��20��


#include "iostream"
#include "queue"
#include "cstdio"
#include "queue"
#include "vector"
using namespace std;

//����
constexpr auto maxPoints = 100009;
constexpr auto maxLines = 10;
constexpr auto inf = 9999999;

//���
template <class T>
class myPoint {
public:
	int num = 0;
	int line[maxLines] = { 0 };
	T linelen[maxLines] = { 0 };
	T cur_pos = (T)inf;
};

//Dijkstra���ö����
template <class T>
class myDijkstraPriorityQueue {
public:
	vector<int> queueData;
	unsigned int sizeOfQueue = 0;
	myPoint<T>* points = nullptr;

	bool cmp(int a, int b) const {
		return points[a].cur_pos < points[b].cur_pos;
	}

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

	//Percolate Up
	void percolateUp(unsigned int pos) {
		//���Ϲ���
		for (auto i = pos; i > 1; i = i / 2) {
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

	//����
	myDijkstraPriorityQueue(myPoint<T> *points):points(points) {
		queueData.clear();
		queueData.push_back(0);
		sizeOfQueue = 0;
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
	void push(const int& input) {
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
	int top() {
		return queueData[1];
	}
	//����
	int pop() {
		auto temp = queueData[1];
		queueData[1] = queueData[sizeOfQueue--];
		queueData.pop_back();
		percolateDown(1);
		return temp;
	}
};

//����ͼ
template <class T>
class myGraph {
public:
	int num = 0;
	myPoint<T> points[maxPoints];

	void addPoint() {
		num++;
	}
	void addPoint(int n) {
		num += n;
	}
	void addLine(int from, int to, T length) {
		points[from].line[points[from].num] = to;
		points[from].linelen[points[from].num] = length;
		points[from].num++;
	}

	//���·�㷨
	T SPFA(int from, int to) const{
		T *length = new T[num];
		bool *inQueue = new bool[num];
		//��¼���·��
		for (int i = 0; i < num; i++) {
			length[i] = inf;
			inQueue[i] = false;
		}
		length[from] = 0.0;
		queue<int> road;
		//���
		road.push(from);
		inQueue[from] = true;

		while (!road.empty()) {
			//����һ���ڵ�
			int curPoint = road.front();
			inQueue[road.front()] = false;
			road.pop();

			//����
			for (int i = 0;
				i < points[curPoint].num;
				i++) {
				if (length[curPoint] +
					points[curPoint].linelen[i] <
					length[points[curPoint].line[i]]) {
					//����
					length[points[curPoint].line[i]] = length[curPoint] + points[curPoint].linelen[i];
					if (!inQueue[points[curPoint].line[i]]) {
						road.push(points[curPoint].line[i]);
						inQueue[points[curPoint].line[i]] = true;
					}
				}
			}
		}
		auto result = length[to];
		delete length;
		delete inQueue;
		return result;
	}

	//Dijkstra Algorithm
	T dijkstra(int from, int to) {
		bool* arrived = new bool[num] {0};
		myDijkstraPriorityQueue<T> queue_data(points);
		points[from].cur_pos = (T)0;
		queue_data.push(from);
		while (!queue_data.empty()) {
			auto cur_point = queue_data.top();
			if (arrived[cur_point]) {
				queue_data.pop();
				continue;
			}
			if (cur_point == to)
				return points[cur_point].cur_pos;
			queue_data.pop();
			arrived[cur_point] = true;
			for (int i = 0; i < points[cur_point].num; ++i) {
				auto next_point = points[cur_point].line[i];
				if (!arrived[next_point]) {
					points[next_point].cur_pos = points[cur_point].cur_pos + points[cur_point].linelen[i];
					queue_data.push(next_point);
				}
			}
		}
		return (T)inf;
	}
};