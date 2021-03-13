#include "iostream"
#include "algorithm"
#include "cstdio"
#include "cstring"
using namespace std;

class mountain {
public:
	long long pos = 0;
	long long height = 0;
};

//ɽ���λ��
long long pos[100009] = { 0 };
long long height[100009] = { 0 };
mountain mountains[100009];

//����DP����
int dp_temp[100009][2];

//��������
int num = 0;

//��̬�滮
int dp(int cur_pos, int cur_state) {
	if (cur_pos >= num)
		return 0;
	if (dp_temp[cur_pos][cur_state] >= 0)
		return dp_temp[cur_pos][cur_state];
	//�ж��Ƿ�����������
	if (cur_pos == 0 || (cur_state == 0 && pos[cur_pos] - height[cur_pos] > pos[cur_pos - 1]) ||
		(cur_state == 1 && pos[cur_pos] - height[cur_pos] > pos[cur_pos - 1] + height[cur_pos - 1])) {
		int ans = 1 + dp(cur_pos + 1, 0);
		dp_temp[cur_pos][cur_state] = ans;
		return ans;
	}
	else {
		int ans = 0;
		//�ж��Ƿ����������
		if (cur_pos == num - 1 || pos[cur_pos] + height[cur_pos] < pos[cur_pos + 1]) {
			ans = 1 + dp(cur_pos + 1, 1);
		}
		//����
		int shit_ans = dp(cur_pos + 1, 0);
		ans = shit_ans > ans ? shit_ans : ans;
		dp_temp[cur_pos][cur_state] = ans;
		return ans;
	}
}

int main() {
	scanf("%d", &num);

	memset(dp_temp, -1, sizeof(dp_temp));

	for (int i = 0; i < num; ++i)
		scanf("%lld", &mountains[i].pos);
	for (int i = 0; i < num; ++i)
		scanf("%lld", &mountains[i].height);

	//����
	sort(mountains, mountains + num, [](mountain a, mountain b) {
		return a.pos < b.pos;
	});

	//д��
	for (int i = 0; i < num; ++i) {
		pos[i] = mountains[i].pos;
		height[i] = mountains[i].height;
	}

	printf("%d", dp(0, 0));

	return 0;
}