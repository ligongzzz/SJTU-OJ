#include "iostream"
#include "cstring"
#include "cmath"
#include "algorithm"

using namespace std;

//����
constexpr auto maxNum = 10000;
constexpr auto intMax = 20;

//���޷��Ŵ�������
class unsignedBigInt {
private:
	bool del = false;
public:
	char* ch;
	int startNum = 0;
	int len = 0;

	//��ʼ��
	unsignedBigInt(const char* input) {
		if (del)
			delete[] ch;

		len = (strlen(input) + 1) * 2;
		startNum = strlen(input);
		ch = new char[len];
		memset(ch, 0, len);
		for (int i = 0; i < strlen(input); i++)
			ch[i + startNum] = input[i];

		del = true;
	}
	unsignedBigInt(int num) {
		if (del)
			delete[] ch;

		//��ʱ����
		int n = 0, temp[intMax];
		if (num == 0) {
			n = 1;
			temp[0] = 0;
		}
		else
			for (; num > 0; num /= 10)
				temp[n++] = num % 10;


		len = (n + 1) * 2;
		startNum = n;
		ch = new char[len];
		memset(ch, 0, len);

		for (int i = 0; i < n; i++)
			ch[startNum + i] = temp[n - i - 1] + '0';

		del = true;
	}
	unsignedBigInt(void) {
		if (del)
			delete[] ch;

		len = 1;
		startNum = 0;
		ch = new char[len];
		memset(ch, 0, len);

		del = true;
	}
	unsignedBigInt(int num, int sizen) {
		if (del)
			delete[] ch;

		len = (sizen + 1) * 2;
		startNum = sizen;
		ch = new char[len];
		memset(ch, 0, len);

		if (num >= 0) {
			int n = 0, temp[intMax];
			if (num == 0) {
				n = 1;
				temp[0] = 0;
			}
			else
				for (; num > 0; num /= 10)
					temp[n++] = num % 10;

			for (int i = 0; i < n; i++)
				ch[startNum + i] = temp[n - i - 1] + '0';
		}

		del = true;
	}

	//����
	~unsignedBigInt() {
		if (del)
			delete[] ch;
	}

	//������ʵ����
	int realLength(const unsignedBigInt & b) {
		return strlen(b.ch + b.startNum);
	}

	//���ƹ��캯��
	unsignedBigInt(const unsignedBigInt & b) {
		if (del)
			delete[] ch;

		len = b.len;
		startNum = b.startNum;
		ch = new char[len];
		for (int i = 0; i < len; i++)
			ch[i] = b.ch[i];

		del = true;
	}

	//�������
	friend ostream & operator<<(ostream & output, const unsignedBigInt & bi);
	friend istream & operator>>(istream & input, unsignedBigInt & bi);

	//��ֵ
	unsignedBigInt & operator=(const unsignedBigInt & b) {
		//�������ֵ
		if (this == &b)
			return *this;

		if (del)
			delete[] ch;

		len = b.len;
		startNum = b.startNum;
		ch = new char[len];
		for (int i = 0; i < len; i++)
			ch[i] = b.ch[i];

		del = true;
		return *this;
	}

	unsignedBigInt & operator=(int num) {
		if (del)
			delete[] ch;

		//��ʱ����
		int n = 0, temp[intMax];
		if (num == 0) {
			n = 1;
			temp[0] = 0;
		}
		else
			for (; num > 0; num /= 10)
				temp[n++] = num % 10;


		len = (n + 1) * 2;
		startNum = n;
		ch = new char[len];
		memset(ch, 0, len);

		for (int i = 0; i < n; i++)
			ch[startNum + i] = temp[n - i - 1] + '0';

		del = true;
		return *this;
	}

	//�ȽϷ�
	//����
	bool operator>(const unsignedBigInt & b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) > 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) > strlen(b.ch + b.startNum) ? true : false;
	}
	//�����
	//�Ӻ�
	unsignedBigInt operator+(const unsignedBigInt & b) {
		unsignedBigInt temp(-1, max(realLength(*this), realLength(b)) + 2);
		int jw = 0;
		int test = realLength(*this);

		for (int i = 0; realLength(*this) > i || realLength(b) > i || jw != 0; i++) {
			//�жϼ���
			int j1 = realLength(*this) <= i ? 0 : ch[startNum + strlen(ch + startNum) - i - 1] - '0';
			int j2 = realLength(b) <= i ? 0 : b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] - '0';

			//����
			temp.ch[--temp.startNum] = (j1 + j2 + jw) % 10 + '0';
			jw = (j1 + j2 + jw) / 10;
		}

		//����
		return temp;
	}
};


//�������������
//�޷��Ŵ�����
ostream& operator<<(ostream & output, const unsignedBigInt & bi) {
	output << bi.ch + bi.startNum;
	return output;
}
istream& operator>>(istream & input, unsignedBigInt & bi) {
	char ch[maxNum];
	input >> ch;
	bi = unsignedBigInt(ch);
	return input;
}

unsignedBigInt numData[51][51];
int k, h;
void cnt(int num, int depth) {
	if (depth == 1) {
		numData[num][depth] = 1;
		return;
	}
	if (numData[num][depth] > 0)
		return;
	//����
	for (int i = 0; i < num; i++) {
		cnt(k - i, depth - 1);
		numData[num][depth] = numData[num][depth] + numData[k - i][depth - 1];
	}
	return;
}

int main() {
	cin >> k >> h;
	for (int i = 0; i <= k; i++)
		for (int j = 0; j <= h; j++)
			numData[i][j] = 0;
	cnt(k, h);

	cout << numData[k][h];

	return 0;
}