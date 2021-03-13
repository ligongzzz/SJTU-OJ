#include "iostream"
#include "cstdio"
using namespace std;

bool visited[109][109] = { 0 };

class nums {
public:
	int m = 0, n = 0;
	double val = 0.0;
};

nums num[10009];

template <class T, class T_val = decltype(*declval<T>()),
	class Compare = bool (*)(T_val, T_val)>
	void quick_sort(T start, T end,
		Compare cmp = [](T_val a, T_val b) {return a < b; }) {
	if (start == end)
		return;
	auto i = start, j = end;
	--j;
	if (i == j)
		return;
	//����
	auto key = *start;
	for (bool status = true; i != j;) {
		if (status) {
			if (cmp(*j, key)) {
				*i = *j;
				++i;
				status = false;
			}
			else
				--j;
		}
		else {
			if (cmp(key, *i)) {
				*j = *i;
				--j;
				status = true;
			}
			else
				++i;
		}
	}
	*i = key;
	//�ݹ�
	quick_sort(start, ++i, cmp);
	quick_sort(i, end, cmp);
}

int main() {
	int n;
	cin >> n;

	int cnt = 0;
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			if (visited[i][j])
				continue;
			//���뼯��
			num[cnt].m = i;
			num[cnt].n = j;
			num[cnt++].val = double(j) / double(i);

			//�����䱶��
			for (int k = 2; k * i <= n; ++k)
				visited[k * i][k * j] = true;
		}
	}

	//����
	quick_sort(num, num + cnt, [](nums a, nums b) {return a.val < b.val; });

	//���
	printf("0/1\n");
	for (int i = 0; i < cnt; ++i)
		printf("%d/%d\n", num[i].n, num[i].m);
	printf("1/1");

	return 0;
}