#include "iostream"
#include "algorithm"
using namespace std;

int main() {
	int n, x, y;
	cin >> n >> x >> y;
	//��¼��ǰ����
	int gap = min(min(x - 1, n - x), min(y - 1, n - y));
	int num = n - 2 * gap;
	int step = n * n - num * num;

	int dx[] = { 0,1,0,-1 };
	int dy[] = { 1,0,-1,0 };
	//��¼����
	for (int status = 0, i = (n - num) / 2 + 1, j = i-1; i != x || j != y; step++) {
		i += dx[status];
		j += dy[status];
		//�ж��Ƿ�Խ��
		if (i + dx[status] > n - gap || i + dx[status]<gap + 1 || j + dy[status]>n - gap || j + dy[status] < gap + 1) {
			status = status < 3 ? status + 1 : 0;
		}
	}
	//���
	cout << step-1;
	return 0;
}