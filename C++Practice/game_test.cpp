#include <iostream>
#include "game_test.hpp"

using namespace std;

// テスト用関数
map<int, string> makeTestGameData(string moves) {

	map<int, string> map;

	int key = 1;
	for (int i = 0; i < moves.size(); i += 2) {
		cout << moves.substr(i, 2) << endl;
		map.insert(make_pair(key, moves.substr(i, 2)));
		key++;
	}

	return map;
}
