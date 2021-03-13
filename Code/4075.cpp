#include "iostream"
#include "cstring"
using namespace std;

char A[1000009], B[100009];

int KMP(char* source, char* destination) {
	int len_source = strlen(source),
		len_destination = strlen(destination);

	//int same_num = 0;
	int* same_nums = new int[len_destination] {0};
	for (int i = 0, j = 0; i < len_source;) {
		//ÿһλ�Ƚ�
		if (source[i] == destination[j]) {
			//�ж��Ƿ��ظ�
			if (j > 0 && destination[j] == destination[same_nums[j - 1]]) {
				same_nums[j] = same_nums[j - 1] + 1;
			}
			else if (j > 0) {
				same_nums[j] = 0;
				if (destination[j] == destination[0])
					++same_nums[j];
			}
			//�ƶ�
			++i, ++j;
			//�ж�
			if (j == len_destination)
				return i - len_destination;
		}
		else {
			if (j == 0)
				++i, j = 0;
			else
				j = same_nums[j - 1];
		}
	}
	//ƥ��ʧ��
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> A >> B;
	cout << KMP(A, B);

	return 0;
}