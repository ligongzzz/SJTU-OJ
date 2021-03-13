#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
using namespace std;

constexpr double jd = 0.00001;

//����
template <class T>
void mySwap(T&a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

struct School
{
	char name[7]; //ѧԺ����
	double score; //��Ȩ�ܷ�
	int count;    //ѧ������

	int scoreA = 0, scoreB = 0, scoreC = 0;
};

class Solution
{
public:
	Solution(int cnt) { numOfSchool = 0; schools = new School[cnt]; }
	//����ѧ����Ϣ���޸�����ѧԺ����Ӧ��Ϣ
	void modify(char* id, double score, char* schoolName);
	void displayResult();  //���
	~Solution() { delete[] schools; }

	// ���Ը������������������Ա

private:
	School *schools;    // ���ѧԺ��Ϣ��ָ��
	unsigned int numOfSchool;  // ѧԺ����

// ���Ը������������������Ա

};
void Solution::displayResult() {
	//���
	for (int i = 0; i < numOfSchool; i++) {
		schools[i].score = double(schools[i].scoreA) + double(schools[i].scoreB) / 1.5 + double(schools[i].scoreC) * 1.5;
	}

	//��ʼ����
	sort(schools, schools + numOfSchool, [](School a, School b) {
		return int(a.score) > int(b.score) ||
			int(a.score) == int(b.score) && (a.count < b.count) ||
			(int(a.score) == int(b.score) && (a.count == b.count) && strcmp(a.name, b.name) < 0);
	});
	/*auto num = numOfSchool;
	auto destination = schools;
	for (int i = num - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
		{
			bool flag = false;
			if (int(destination[j].score) < int(destination[j+1].score)) flag = true;
			else if (int(destination[j].score) == int(destination[j+1].score) && destination[j].count > destination[j + 1].count) flag = true;
			else if (int(destination[j].score) == int(destination[j+1].score) && destination[j].count == destination[j + 1].count&&strcmp(destination[j].name, destination[j + 1].name) > 0) flag = true;
			if(flag)
			   mySwap(destination[j], destination[j + 1]);
		}*/
	cout << numOfSchool;
	for (int i = 0; i < numOfSchool; i++) {
		cout << endl;
		//�ж��Ƿ���
		int n = 0;
		for (n = 1; n <= numOfSchool; n++)
			if (int(schools[n - 1].score) == int(schools[i].score))
				break;
		cout << n << " " << schools[i].name << " " << int(schools[i].score) << " " << schools[i].count;
	}
}

void Solution::modify(char* id, double score, char* schoolName) {
	//��Сд
	for (int i = 0; i < strlen(schoolName); i++) {
		if (schoolName[i] >= 'A'&&schoolName[i] <= 'Z') {
			schoolName[i] -= 'A' - 'a';
		}
	}
	//�鲢ѧԺ
	bool flag = false;
	int thisSchool = 0;
	for (int i = 0; i < numOfSchool; i++) {
		if (strcmp(schoolName, schools[i].name) == 0) {
			flag = true;
			thisSchool = i;
			break;
		}
	}
	if (!flag) {
		thisSchool = numOfSchool++;
		schools[thisSchool].count = 0;
		schools[thisSchool].score = 0.0;
		strcpy(schools[thisSchool].name, schoolName);
	}

	//��ʼ���
	schools[thisSchool].count++;
	if (id[0] == 'A') schools[thisSchool].scoreA += score;
	else if (id[0] == 'B') schools[thisSchool].scoreB += score;
	else if (id[0] == 'T') schools[thisSchool].scoreC += score;
}
//main������Ҫ���κ��޸�
int main()
{
	int numOfPerson;
	cin >> numOfPerson;   //���뿼������

	char id[7]; //׼��֤��
	int score;  //����
	char schoolName[7]; //ѧԺ����

	Solution solution(numOfPerson);

	for (int i = 0; i < numOfPerson; i++) {
		cin >> id >> score >> schoolName;    // ��ȡ������Ϣ
		solution.modify(id, score, schoolName);  //����ѧ����Ϣ���޸�����ѧԺ����Ӧ��Ϣ
	}
	solution.displayResult();    //������

	return 0;
}