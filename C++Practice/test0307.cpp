#include <iostream> // .hはつけない
#include <string>   // .hはつけない
using namespace std;

int main2(void) {
	cout << "aaa\n";

	int aaa = 8;
	cout << aaa << endl;

	int* paaa = &aaa;
	std::cout << paaa << std::endl;

	int vaaa = *paaa;
	cout << vaaa << endl;

	// 標準入力
	string a;
	cin >> a;
	cout << "a=" << a;

	return 0;
}
