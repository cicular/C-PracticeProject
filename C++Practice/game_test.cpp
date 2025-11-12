#include "game_test.hpp"

using namespace std;

// テスト用関数
map<int, string> makeTestGameData(string moves) {

	map<int, string> map;

	int key = 1;
	for (size_t i = 0; i < moves.size(); i += 2) {
		map.insert(make_pair(key, moves.substr(i, 2)));
		key++;
	}

	return map;
}
