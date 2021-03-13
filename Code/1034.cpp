#include "iostream"
#include "cstdio"
using namespace std;

int val[400009] = { 0 };
//����������
class f_queue {
public:
	//�洢�����������ݵ�����
	int queue_data[400009] = { 0 };
	//��ͷԪ��λ��
	int start = 0;
	//��βԪ��λ��
	int end = 0;
	//���뺯��
	void push(int num) {
		int i = end;
		//�Ӷ�β��ʼɨ�裬��С��num��Ԫ��ȫ��������ֱ���������ڵ���num��Ԫ��
		for (; i > start; --i) {
			if (queue_data[i - 1] >= num)
				break;
		}
		//��num���뵥��������
		queue_data[i] = num;
		end = i + 1;
	}
	//��������
	void pop(int num) {
		//�ж���Ҫ������num�Ƿ����ͷԪ����ȣ��������򽫶�ͷ���ӣ����������򲻽����κβ���
		if (num == queue_data[start])
			++start;
	}
	//���ض�ͷԪ��
	int front() {
		return queue_data[start];
	}
};

//��������
f_queue qdata;

int main() {
	int N, K;
	cin >> N >> K;

	int init = 0;
	for (int i = 0, cur_max = 0; i < N; ++i) {
		scanf("%d", &val[i]);
	}
	
	//ƴ�ӣ����ҽ�ǰK��Ԫ���뵥������
	for (int i = 0; i < K; ++i) {
		val[N + i] = val[i];
		qdata.push(val[i]);
	}

	int rp_max = qdata.front();
	for (int i = 0; i < N; ++i) {
		//�ƶ����ڣ��Ƚ���i��Ԫ�س��������У��ٽ���i+K��Ԫ����ӣ����жϴ�ʱ���������е����ֵ�Ƿ��rp_maxС
		qdata.pop(val[i]);
		qdata.push(val[i + K]);
		if (qdata.front() < rp_max)
			rp_max = qdata.front();
	}
	//�����rp_max
	cout << rp_max;

	return 0;
}