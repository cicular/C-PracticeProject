#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "board_view.hpp"
#include "board_logic.hpp"
#include "game_test.hpp"

using namespace std;

#define TEST

int main() {

#ifdef TEST
	// D3C3B3B2E6B4A3D2B5A5D1E1A1B1F1B6C1D6D7E3F2F6G7D8C8B8B7H8C2G1H1A6C6F5G6E7G8H6E8F8A8A4G3G4C7A2A7C5C4F3G2E2H5H3H4H7G5F7H2F4
	// f5d6c5f4d7f6d3c3e3f3d2c4b5c6b6e2b4a5f2a4b3a6g4a3e6d1e1c2c1g3h3g5g6h4h5a7a2a1b7a8c7b2b1c8b8d8e8f8e7g2f1g1h1h2f7h6g7g8
	// F5D6C3F3C5C6D3F4E7B5B6D2E1D1F2F1F6B4A5G7G5A7A3B7A8B8C8H5H6G2H1H3H2G3H4C7A6F8B2A1C1B1G4B3C2C4A2A4D8E3G1E6D7E8G8F7H8H7E2G6
	map<int, string> kifuMap = makeTestGameData("D3C3B3B2E6B4A3D2B5A5D1E1A1B1F1B6C1D6D7E3F2F6G7D8C8B8B7H8C2G1H1A6C6F5G6E7G8H6E8F8A8A4G3G4C7A2A7C5C4F3G2E2H5H3H4H7G5F7H2F4");
	int moveCount = 0;
#endif

	system("color f0");

	Board board;

	Player player = Player::Black;

	// 盤面の生成
	init_board(board);



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
#ifdef TEST
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
