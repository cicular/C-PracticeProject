#include <iostream>
#include "board_logic.hpp"

using namespace std;

/*
	番兵を含めた10×10の盤面を初期化する。
*/
void init_board(Board& board) {

	cout << "盤面の初期表示を開始します" << endl;

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			board[x][y] = Cell::Empty;
		}
	}

	for (int i = 0; i < 10; i++) {
		// 番兵
		board[i][9] = Cell::Sentinel;
		board[9][i] = Cell::Sentinel;
		board[i][0] = Cell::Sentinel;
		board[0][i] = Cell::Sentinel;
	}

	// 初期の石の配置
	board[4][4] = Cell::White;
	board[4][5] = Cell::Black;
	board[5][4] = Cell::Black;
	board[5][5] = Cell::White;

	cout << "盤面の初期表示をしました。" << endl;
}

bool is_legal_move(Board& board, string input, Player player) {
	
	string x_alphabet = input.substr(0, 1);
	string y_str = input.substr(1, 2);

	// int型に変換
	int y_int = stoi(y_str);

	int x_int;

	if (x_alphabet == "A") {
		x_int = 1;
	}
	else if (x_alphabet == "B") {
		x_int = 2;
	}
	else if (x_alphabet == "C") {
		x_int = 3;
	}
	else if (x_alphabet == "D") {
		x_int = 4;
	}
	else if (x_alphabet == "E") {
		x_int = 5;
	}
	else if (x_alphabet == "F") {
		x_int = 6;
	}
	else if (x_alphabet == "G") {
		x_int = 7;
	}
	else if (x_alphabet == "H") {
		x_int = 8;
	}
	else {
		return false;
	}

	std::cout << "入力された座標は、" << to_string(x_int) << to_string(y_int) << std::endl;

	// そもそもそのセルがEmptyであること
	if (board[x_int][y_int] != Cell::Empty) {
		return false;
	}
	else {
		Cell compareCell = player == Player::Black ? Cell::White : Cell::Black;

/*
		for (int x = x_int - 1; x <= x_int + 1; x++) {
			cout << "探索" << to_string(x) << endl;
		}
*/
#ifndef DEBUG
		// 隣接する縦・横・斜めの8セルのいずれかが敵の石であること
		for (int x = x_int - 1; x <= x_int + 1; x++) {
			for (int y = y_int - 1; y <= y_int + 1; y++) {
				cout << "探索" << endl;
				if (board[x][y] == compareCell) {
					cout << "隣接するセルに、敵の石がありました。" << endl;
					
					// かつ
					// その隣接する敵の石の直線方向に、自分の石があること
					// x_int-1、y_int-1 ⇒左上方向に探索 ⇒ x:x_int-2,y:y_int-2 x:x_int-3,y:y_int-3 x:x_int-4,y:y_int-4 つまりxとyをマイナスしていく
					// x_int-1、y_int   ⇒左方向に探索   ⇒ x:x_int-2,y:y_int   x:x_int-3,y:y_int   x:x_int-4,y:y_int   つまりxのみマイナスしていく
					// x_int-1、y_int+1 ⇒左下方向に探索 ⇒ x:x_int-2,y:y_int+2 x:x_int+3,y:y_int+3 x:x_int+4,y:y_int+4 つまりxはマイナス、yはプラスしていく
					// x_int  、y_int-1 ⇒上方向に探索　　　つまりyのみをマイナスしていく
					// x_int  、y_int   ⇒
					// x_int  、y_int+1 ⇒下方向に検索      つまりyのみをプラスしていく
					// x_int+1、y_int-1 ⇒右上方向に探索    つまりxはプラス、yはマイナスしていく
					// x_int+1、y_int   ⇒右方向に探索      つまりxのみプラスしていく
					// x_int+1、y_int+1 ⇒右下方向に探索    つまりxとyをプラスしていく

				}
			}
		}
#endif
	}


	return false;
}

void place_stone() {

}

bool is_board_full(Board& board) {

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (board[x][y] == Cell::Empty) {
				cout << "満盤ではない" << endl;
				return false;
			}
		}
	}

	return true;
}

int judge_winner() {
	return 0;
}
