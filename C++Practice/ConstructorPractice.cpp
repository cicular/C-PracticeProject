#include <iostream>
using namespace std;

class Student {
public:
	int num;
	// 引数のないコンストラクタ
	Student();
	// 引数のあるコンストラクタ
	Student(int x);
	// デストラクタ
	~Student();
	// コピーコンストラクタ
	Student(const Student &obj);
};

int main() {
	// 引数のないコンストラクタ実行
	Student student;
	cout << student.num << endl;

	// 引数のあるコンストラクタ実行
	Student student2(20);
	cout << student2.num << endl;

	// オブジェクトが初期化されると通常、コンストラクタは発動しない
	// student2とstudent3で同じアドレスのデータを共有することになる。勝手な書き換えを防ぐため。
	Student student3 = student2;
	cout << student3.num << endl;
	cout << student2.num << endl;

	return 0;
}

// 引数のないコンストラクタ
Student::Student() {
	cout << "コンストラクタ実行" << endl;
	num = 10;
}

// 引数のあるコンストラクタ
Student::Student(int x) {
	cout << "コンストラクタ実行" << endl;
	num = x;
}

// デストラクタ
Student::~Student() {
	cout << "デストラクタ実行" << endl;
}

// コピーコンストラクタ
Student::Student(const Student &obj) {
	cout << "コピーコンストラクタ実行" << endl;
	num = 30;
}
