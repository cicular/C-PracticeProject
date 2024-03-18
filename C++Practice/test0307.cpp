#include <iostream> // .h‚Í‚Â‚¯‚È‚¢
#include <string>   // .h‚Í‚Â‚¯‚È‚¢
using namespace std;

int main2(void) {
	cout << "aaa\n";

	int aaa = 8;
	cout << aaa << endl;

	int* paaa = &aaa;
	std::cout << paaa << std::endl;

	int vaaa = *paaa;
	cout << vaaa << endl;

	// •W€“ü—Í
	string a;
	cin >> a;
	cout << "a=" << a;

	return 0;
}
