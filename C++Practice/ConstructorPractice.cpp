#include <iostream>
using namespace std;

class Student {
public:
	int num;
	// �����̂Ȃ��R���X�g���N�^
	Student();
	// �����̂���R���X�g���N�^
	Student(int x);
	// �f�X�g���N�^
	~Student();
	// �R�s�[�R���X�g���N�^
	Student(const Student &obj);
};

int main() {
	// �����̂Ȃ��R���X�g���N�^���s
	Student student;
	cout << student.num << endl;

	// �����̂���R���X�g���N�^���s
	Student student2(20);
	cout << student2.num << endl;

	// �I�u�W�F�N�g�������������ƒʏ�A�R���X�g���N�^�͔������Ȃ�
	// student2��student3�œ����A�h���X�̃f�[�^�����L���邱�ƂɂȂ�B����ȏ���������h�����߁B
	Student student3 = student2;
	cout << student3.num << endl;
	cout << student2.num << endl;

	return 0;
}

// �����̂Ȃ��R���X�g���N�^
Student::Student() {
	cout << "�R���X�g���N�^���s" << endl;
	num = 10;
}

// �����̂���R���X�g���N�^
Student::Student(int x) {
	cout << "�R���X�g���N�^���s" << endl;
	num = x;
}

// �f�X�g���N�^
Student::~Student() {
	cout << "�f�X�g���N�^���s" << endl;
}

// �R�s�[�R���X�g���N�^
Student::Student(const Student &obj) {
	cout << "�R�s�[�R���X�g���N�^���s" << endl;
	num = 30;
}
