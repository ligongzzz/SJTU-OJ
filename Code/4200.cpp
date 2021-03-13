#include "iostream"
#include "cstdio"
#include "cstdlib"
#include "algorithm"
#include "cstring"

using namespace std;

class Person {
public:
	Person() {}
	bool isLegal(); //�ж������Ƿ����������true,���򷵻�flase
	void read();    //���������Ϣ

  // ���Ը������������������Ա
	friend class Solution;

private:
	char name[6];        //����
	char birthday[11];   //����

  // ���Ը������������������Ա

};
void Person::read() {
	cin >> name >> birthday;
}

bool Person::isLegal() {
	int year, month, day;
	sscanf(birthday, "%d/%d/%d", &year, &month, &day);
	//�жϲ�����
	if (month > 12 || day > 31)
		return false;
	int yearTime = year * 10000 + month * 100 + day;
	if (yearTime > 20181220 || yearTime < 18981220)
		return false;
	else
		return true;
}

class Solution {
public:
	Solution() { count = 0; }
	void regPerson(const Person &person);//ͳ����Ч�����������Լ������������곤����
	void displayResult();  //��������Ϣ

// ���Ը������������������Ա

private:
	char eldestName[6]; //���곤�˵�����
	char eldestBirthday[11]; //���곤�˵�����
	char youngestName[6]; //�������˵�����
	char youngestBirthday[11];  //�������˵�����
	int count;   //��Ч��������
};

void Solution::displayResult() {
	cout << count << " " << eldestName << " " << youngestName;
}

void Solution::regPerson(const Person &person) {
	count++;
	int year, month, day;
	int yearTime = 0, eldestYearTime = 0, youngestYearTime = 0;

	sscanf(person.birthday, "%d/%d/%d", &year, &month, &day);
	yearTime = year * 10000 + month * 100 + day;

	if (count > 1) {
		sscanf(eldestBirthday, "%d/%d/%d", &year, &month, &day);
		eldestYearTime = year * 10000 + month * 100 + day;

		sscanf(youngestBirthday, "%d/%d/%d", &year, &month, &day);
		youngestYearTime = year * 10000 + month * 100 + day;
	}

	//�ж��Ƿ������С
	if (yearTime < eldestYearTime || count == 1) {
		strcpy(eldestName, person.name);
		strcpy(eldestBirthday, person.birthday);
	}
	if (yearTime > youngestYearTime || count == 1) {
		strcpy(youngestName, person.name);
		strcpy(youngestBirthday, person.birthday);
	}
}

//main������Ҫ���κ��޸�
int main()
{
	Solution solution;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		Person person;
		person.read();
		if (person.isLegal()) {
			solution.regPerson(person);
		}
	}
	solution.displayResult();

	return 0;
}