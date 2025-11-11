#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "board_view.hpp"
#include "board_logic.hpp"

using namespace std;

// 関数プロトタイプ
map<int, string> makeTestGameData1(string moves);

int main() {

	map<int, string> kifuMap = makeTestGameData1("f5d6c5f4d7f6d3c3e3f3d2c4b5c6b6e2b4a5f2a4b3a6g4a3e6d1e1c2c1g3h3g5g6h4h5a7a2a1b7a8c7b2b1c8b8d8e8f8e7g2f1g1h1h2f7h6g7g8");

	system("color f0");

	Board board;

	Player player = Player::Black;

	// 盤面の生成
	init_board(board);

	int moveCount = 0;

	// 終局までループ
	while (!is_board_full(board, &player)) {

		// コマンドプロンプトクリア
		//clear_screen();
		
		// 盤面の表示
		show_board(board);
		// 手番の表示
		show_player(player);
		// 入力受付
		string input;
		int x_input;
		int y_input;

		do {
#ifndef TEST
			moveCount++;
			input = kifuMap.at(moveCount);
#else
			// 盤上の座標は左上を原点として、横方向をa～h, 縦方向を1～8で表す。
			// (例：左上隅はa1，右下隅は h8)
			// 参考：https://www.othello.org/lesson/lesson/term.html
			cout << "配置場所を入力してください (例: E6): " << endl;
			cin >> input;
#endif
			x_input = convertAlphabetToNum(input);
			y_input = getYinput(input);
		} while (!is_legal_move(board, x_input, y_input, player, true));
		//石を配置する
		place_stone(board, x_input, y_input, player);
		// 手番変更
		player = player == Player::Black ? Player::White : Player::Black;

	}
	// 盤面の表示
	show_board(board);

	// 勝利判定と表示
	show_winner(judge_winner(board));

	return 0;
}

map<int, string> makeTestGameData1(string moves) {

	map<int, string> map;

	int key = 1;
	for (int i = 0; i < moves.size();i+=2) {
		// cout << moves.substr(i, 2) << endl;
		map.insert(make_pair(key, moves.substr(i,2)));
		key++;
	}

	return map;
}
