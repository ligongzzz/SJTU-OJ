#include "iostream"
#include "cstring"
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
	char *ch;
	int startNum = 0;
	int len = 0;

	//��ʼ��
	unsignedBigInt(const char *input) {
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
	int realLength(const unsignedBigInt &b) {
		return strlen(b.ch + b.startNum);
	}

	//���ƹ��캯��
	unsignedBigInt(const unsignedBigInt& b) {
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
	friend ostream &operator<<(ostream &output, const unsignedBigInt &bi);
	friend istream &operator>>(istream &input, unsignedBigInt &bi);

	//��ֵ
	unsignedBigInt &operator=(const unsignedBigInt &b) {
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
	unsignedBigInt &operator=(const char* b) {
		if (del)
			delete[] ch;

		len = (strlen(b) + 1) * 2;
		startNum = strlen(b);
		memset(ch, 0, len);

		for (int i = 0; i < strlen(b); i++)
			ch[i + startNum] = b[i];

		del = true;
		return *this;
	}
	unsignedBigInt &operator=(int num) {
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
	//С��
	bool operator<(const unsignedBigInt &b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) < 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) < strlen(b.ch + b.startNum) ? true : false;
	}

	//����
	bool operator>(const unsignedBigInt &b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) > 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) > strlen(b.ch + b.startNum) ? true : false;
	}

	//С�ڵ���
	bool operator<=(const unsignedBigInt &b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) <= 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) < strlen(b.ch + b.startNum) ? true : false;
	}

	//���ڵ���
	bool operator>=(const unsignedBigInt &b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) >= 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) > strlen(b.ch + b.startNum) ? true : false;
	}

	//���ڵ���
	bool operator==(const unsignedBigInt &b) {
		return strcmp(ch + startNum, b.ch + b.startNum) == 0 ? true : false;
	}

	//�����
	//�Ӻ�
	unsignedBigInt operator+(const unsignedBigInt &b) {
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

	//++c
	unsignedBigInt operator++() {
		*this = *this + unsignedBigInt("1");
		return *this;
	}

	//c++
	unsignedBigInt operator++(int i) {
		unsignedBigInt temp = *this;
		*this = temp + unsignedBigInt("1");
		return temp;
	}

	//����
	unsignedBigInt operator-(const unsignedBigInt &b) {
		if (*this == b)
			return unsignedBigInt(0);

		unsignedBigInt temp(-1, max(realLength(*this), realLength(b)) + 2);
		int jw = 0;

		for (int i = 0; realLength(*this) > i || realLength(b) > i; i++) {
			//�жϱ����������
			int j1 = realLength(*this) <= i ? 0 : ch[startNum + strlen(ch + startNum) - i - 1] - '0';
			int j2 = realLength(b) <= i ? 0 : b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] - '0';

			//����
			if (j1 - jw - j2 < 0) {
				temp.ch[--temp.startNum] = 10 + j1 - jw - j2 + '0';
				jw = 1;
			}
			else {
				temp.ch[--temp.startNum] = j1 - jw - j2 + '0';
				jw = 0;
			}
		}

		//����
		for (; temp.ch[temp.startNum] == '0';)
			temp.ch[temp.startNum++] = 0;

		//����
		return temp;
	}

	//--c
	unsignedBigInt operator--() {
		*this = *this - unsignedBigInt("1");
		return *this;
	}

	//c--
	unsignedBigInt operator--(int i) {
		unsignedBigInt temp = *this;
		*this = temp - unsignedBigInt("1");
		return temp;
	}

	//�˺�
	unsignedBigInt operator*(const unsignedBigInt &b) {
		unsignedBigInt temp(0, realLength(*this) + realLength(b) + 2);
		for (int i = 0; i < strlen(b.ch + b.startNum); i++) {
			int curPos = b.startNum + strlen(b.ch + b.startNum) - 1 - i;
			unsignedBigInt addNum(-1, realLength(*this) + realLength(b) + 2);
			if (b.ch[curPos] != '0') {
				//Accelerate
				int jw = 0;
				for (int j = startNum + strlen(ch + startNum) - 1; j >= startNum || jw != 0; j--) {
					int c1 = ch[j] == 0 ? 0 : ch[j] - '0';
					int c2 = b.ch[curPos] == 0 ? 0 : b.ch[curPos] - '0';

					if (c1*c2 + jw < 10) {
						addNum.ch[--addNum.startNum] = c1 * c2 + jw + '0';
						jw = 0;
					}
					else {
						addNum.ch[--addNum.startNum] = (c1*c2 + jw) % 10 + '0';
						jw = (c1*c2 + jw) / 10;
					}
				}
				//Calculate
				for (int j = 0; j < i; j++)
					addNum.ch[addNum.startNum + strlen(addNum.ch + addNum.startNum)] = '0';

				temp = temp + addNum;
			}
		}
		return temp;
	}

	//����
	unsignedBigInt operator/(const unsignedBigInt &b) {
		//�ų��쳣
		if (unsignedBigInt("0") == b) {
			throw "NaN";
		}

		//��ʱ������
		unsignedBigInt temp(-1, max(realLength(*this), realLength(b)) + 2);
		//���ս��
		unsignedBigInt result(-1, max(realLength(*this), realLength(b)) + 2);

		for (int i = startNum; i < startNum + strlen(ch + startNum); i++) {
			//����һλ
			temp.ch[temp.startNum + strlen(temp.ch + temp.startNum)] = ch[i];
			//��ʼ����
			unsignedBigInt tempResult = b;
			int wr = 0;
			for (; tempResult <= temp; wr++) {
				tempResult = tempResult + b;
			}
			result.ch[result.startNum + strlen(result.ch + result.startNum)] = wr + '0';
			//�����ֵ
			tempResult = tempResult - b;
			if (tempResult == temp) {
				temp = unsignedBigInt(-1, max(realLength(*this), realLength(b)) + 2);
			}
			else {
				temp = temp - tempResult;
			}
		}

		//ȥ0
		for (; strlen(result.ch + result.startNum) > 1 && result.ch[result.startNum] == '0';)
			result.ch[result.startNum++] = 0;

		return result;
	}

	//%
	unsignedBigInt operator%(const unsignedBigInt &b) {
		return *this - *this / b * b;
	}

	//+=
	void operator+=(const unsignedBigInt &b) {
		*this = *this + b;
	}

	//-=
	void operator-=(const unsignedBigInt &b) {
		*this = *this - b;
	}

	//*=
	void operator*=(const unsignedBigInt &b) {
		*this = *this * b;
	}

	// /=
	void operator/=(const unsignedBigInt &b) {
		*this = *this / b;
	}

	//%=
	void operator%=(const unsignedBigInt &b) {
		*this = *this% b;
	}
};

//�������������
//�޷��Ŵ�����
ostream &operator<<(ostream &output, const unsignedBigInt &bi) {
	output << bi.ch + bi.startNum;
	return output;
}
istream &operator>>(istream &input, unsignedBigInt &bi) {
	char ch[maxNum];
	input >> ch;
	bi = unsignedBigInt(ch);
	return input;
}

int main() {
	
	char ch[2000] = { 0 };
	cin >> ch;
	
	unsignedBigInt input(ch);
	//cout << "����������ǣ�" << endl<<input << endl;

	//������
	int cnt = 0;
	ch[strlen(ch) / 2] = 0;
	unsignedBigInt temp1 = input * 2, temp = ch, y, jd("999999");
	
	for (; cnt < 1000; cnt++) {
		if (y < temp&&temp - y < jd)
			break;
		else if (y >= temp && y - temp < jd)
			break;
		y=temp;
		temp = (temp + temp1 / temp) / 2;
	}
	//cout << "ѭ����" << cnt << "��" << endl;
	unsignedBigInt i = temp, j = (temp+1)*temp/2;
	//cout << i << endl << j << endl;
	if (j < input)
		for (; j < input; j += i)
			++i;
	else {
		for (; j >= input; i--)
			j -= i;
		++i;
		j += i;
	}

	if (i % 2 == 1)
		cout << j + 1 - input << "/" << input + i - j;
	else
		cout << input + i - j << "/" << j + 1 - input;

	return 0;
}