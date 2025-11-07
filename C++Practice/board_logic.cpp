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

bool is_legal_move(Board& board, int x_int, int y_int, Player player) {

	if (x_int == -1) return false;

	std::cout << "入力された座標は、" << to_string(x_int) << to_string(y_int) << std::endl;

	// そもそもそのセルがEmptyであること
	if (board[x_int][y_int] != Cell::Empty) {
		return false;
	}
	else {
		Cell compareCell = player == Player::Black ? Cell::White : Cell::Black;
		Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

		// 置かれたセルを起点にして全方向探索
		for (int xi = -1; xi <= 1; xi++) {
			for (int yi = -1; yi <= 1; yi++) {
				
				int xxi = x_int + xi;
				int yyi = y_int + yi;
				cout << to_string(xxi) << to_string(yyi) << endl;
				if (board[xxi][yyi] == compareCell) {
					cout << "隣接するセルに、敵の石がありました。" << endl;

					// while (board[xxi][yyi] == compareCell) {
					while (true) {
						xxi += xi;
						yyi += yi;

						cout << to_string(xxi) << to_string(yyi) << endl;

						if (board[xxi][yyi] == allyStone) {
							cout << "隣接するセルの方角に、自分の石がありました。" << endl;
							return true;
						}

						if (board[xxi][yyi] == Cell::Sentinel) {
							break;
						}
					}
				}
			}
		}
	}

	return false;
}

void place_stone(Board& board, int x_int, int y_int, Player player) {

	cout << "石のひっくり返し処理を開始します。" << endl;

	Cell compareCell = player == Player::Black ? Cell::White : Cell::Black;
	Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

	// 置かれたセルを起点にして全方向探索
	for (int xi = -1; xi <= 1; xi++) {
		for (int yi = -1; yi <= 1; yi++) {

			int xxi = x_int + xi;
			int yyi = y_int + yi;
			cout << to_string(xxi) << to_string(yyi) << endl;
			if (board[xxi][yyi] == compareCell) {
				cout << "隣接するセルに、敵の石がありました。" << endl;

				while (true) {
					xxi += xi;
					yyi += yi;

					cout << to_string(xxi) << to_string(yyi) << endl;

					if (board[xxi][yyi] == allyStone) {
						cout << "隣接するセルの方角に、自分の石がありました。" << endl;
						
					}

					if (board[xxi][yyi] == compareCell) {
						board[xxi][yyi] = allyStone;
					}

					if (board[xxi][yyi] == Cell::Sentinel) {
						break;
					}

					//						if (board[xxi][yyi] == Cell::Black) {
						//						return true;
							//				}

				}
			}
		}
	}
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

int convertAlphabetToNum(string input) {

	string x_alphabet = input.substr(0, 1);

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
		x_int = -1;
	}

	return x_int;
}

int getYinput(string input) {
	string y_str = input.substr(1, 2);
	// int型に変換
	int y_int = stoi(y_str);

	return y_int;
}
