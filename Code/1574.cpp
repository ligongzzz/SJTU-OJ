#include "iostream"

using namespace std;

int main() {
	long long n, m, k, x;
	cin >> n >> m >> k >> x;

	//����10��i�η�������
	long long base = 10 % n;
	long long result = 1;
	while (true) {
		long long temp = k % 10;
		for (int i = 0; i < temp; i++)
			result = result * base%n;
		k = k / 10;
		if (k == 0)
			break;
		//�޸�base��ֵ
		long long baseTemp = base;
		for (int i = 0; i < 9; i++) {
			base = base * baseTemp % n;
		}
	}

	m = m * result%n;

	cout << (x + m) % n;

	return 0;
}