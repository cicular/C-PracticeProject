#include "game_test.hpp"

// テスト用関数
std::map<int, std::string> makeTestGameData(std::string moves) {

	std::map<int, std::string> map;

	int key = 1;
	for (size_t i = 0; i < moves.size(); i += 2) {
		map.insert(make_pair(key, moves.substr(i, 2)));
		key++;
	}

	return map;
}
