#include <iostream> // .h�͂��Ȃ�
#include <string>   // .h�͂��Ȃ�
using namespace std;

int main2(void) {
	cout << "aaa\n";

	int aaa = 8;
	cout << aaa << endl;

	int* paaa = &aaa;
	std::cout << paaa << std::endl;

	int vaaa = *paaa;
	cout << vaaa << endl;

	// �W������
	string a;
	cin >> a;
	cout << "a=" << a;

	return 0;
}
