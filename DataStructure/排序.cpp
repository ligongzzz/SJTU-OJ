//������ By @ligongzzz
//����ʱ�䣺2019��3��9��


#include "iostream"
#include "algorithm"
#include "list"
using namespace std;

//Ĭ�Ϻ���(cmpΪ��ǰ�������ȷ˳��
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

	return 0;
}