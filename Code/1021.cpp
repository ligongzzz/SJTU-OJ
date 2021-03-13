#include "iostream"
#include "iomanip"
using namespace std;

constexpr auto maxNum = 200;

int main() {
	int num;
	cin >> num;

	int data[maxNum][maxNum] = { 0 };

	//���淽��
	int dx = 1, dy = 0;
	//��λ
	int px = 1, py = 1;
	//״̬
	bool status = true;
	
	for (int i = 1; i <= num*num; i++) {
		//���¸õ�
		data[px][py] = i;
		//�ж��Ƿ��߳�
		if (px + dx > num || py + dy > num || data[px + dx][py + dy] != 0||px+dx<1||py+dy<1) {
			if (dx == 1 && dy == 0) {
				dx = 0;
				dy = 1;
			}
			else if (dx == 0 && dy == 1) {
				dx = -1;
				dy = 0;
			}
			else if (dx == -1 && dy == 0) {
				dx = 0;
				dy = -1;
			}
			else {
				dx = 1;
				dy = 0;
			}
		}
		//ǰ��
		px += dx;
		py += dy;
	}

	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			cout << setw(6) << data[j][i];
		}
		cout << endl;
	}

	return 0;
}