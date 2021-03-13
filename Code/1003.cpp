#include <cstdio>
#include <iostream>

using namespace std;

//������߳�
int L = 0;
//ģ��������
int plate[101][101] = { 0 };
//��һ�ֽ���ʱ�ķ�ֳ���
int _plate[101][101] = { 0 };
//�հ׸�����
int blank = 0;
//��ֳ����
int turns = 0;
//�жϸ�λ���Ƿ�Ϊ�ո�
int judge(int i, int j) {
	if (i >= 0 && i < L && j >= 0 && j < L) {
		if (_plate[i][j] == 0 && plate[i][j] == 0) {
			plate[i][j] = 1;
			return 1;
		}
	}
	return 0;
}
//��ֳ
void multiply() {
	while (blank > 0) {
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j < L; ++j) {
				if (_plate[i][j] == 1) {
					blank -= judge(i + 1, j);
					blank -= judge(i, j + 1);
					blank -= judge(i - 1, j);
					blank -= judge(i, j - 1);
				}
			}
		}
		for (int i = 0; i < L; ++i) {
			for (int j = 0; j < L; ++j) {
				_plate[i][j] = plate[i][j];
			}
		}
		turns++;
	}
	return;
}

int main() {
	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < L; ++j) {
			scanf("%d", &plate[i][j]);
			_plate[i][j] = plate[i][j];
			if (plate[i][j] == 0)
				blank++;
		}
	}

	multiply();
	printf("%d", turns);
	return 0;
}