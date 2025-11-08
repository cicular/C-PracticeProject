#include <iostream>
#include <vector>
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

	if (x_int == -1) {
		cout << "不正な手なので、再入力してくださいね？？" << endl;
		return false;
	}

	// std::cout << "入力された座標は、" << to_string(x_int) << to_string(y_int) << std::endl;

	// そもそもそのセルがEmptyであること
	if (board[x_int][y_int] != Cell::Empty) {
		return false;
	}
	else {
		Cell enemyStone = player == Player::Black ? Cell::White : Cell::Black;
		Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

		// 置かれたセルを起点にして全方向探索
		for (int xi = -1; xi <= 1; xi++) {
			for (int yi = -1; yi <= 1; yi++) {
				
				int xxi = x_int + xi;
				int yyi = y_int + yi;
				// cout << to_string(xxi) << to_string(yyi) << endl;
				if (board[xxi][yyi] == enemyStone) {
					// cout << "隣接するセルに、敵の石がありました。" << endl;

					// while (board[xxi][yyi] == enemyStone) {
					while (true) {
						xxi += xi;
						yyi += yi;

						// cout << to_string(xxi) << to_string(yyi) << endl;

						if (board[xxi][yyi] == allyStone) {
							// cout << "隣接するセルの方角に、自分の石がありました。" << endl;
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

	cout << "不正な手なので、再入力してくださいね？？" << endl;
	return false;
}

void place_stone(Board& board, int x_int, int y_int, Player player) {

	cout << "石のひっくり返し処理を開始します。";

	Cell enemyStone = player == Player::Black ? Cell::White : Cell::Black;
	Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

	std::cout << "入力された座標は、" << to_string(x_int) << to_string(y_int) << std::endl;

	// 反転させる対象の石
	// mapだと、キー重複ができないため、x軸でひっくり返す石が複数ある時、最初の1つしか反転できない。
	// そのため、<pair<int, int>をvectorで保持する
	vector<pair<int, int>> reverseCellsVector;

	// まず入力座標を反転対象ベクターに追加
	reverseCellsVector.emplace_back(std::make_pair(x_int, y_int));

	// 置かれたセルを起点にして全方向探索
	for (int xi = -1; xi <= 1; xi++) {
		for (int yi = -1; yi <= 1; yi++) {

			int xxi = x_int + xi;
			int yyi = y_int + yi;
			// cout << to_string(xxi) << to_string(yyi) << endl;
			// 隣接するセルに、敵の石があるか？
			if (board[xxi][yyi] == enemyStone) {

				int nextCellX = xxi;
				int nextCellY = yyi;

				// 反転させるかもしれない対象の石
				vector<pair<int, int>> reverseCandidateCellsVector;

				// 隣接する敵の石の方角に向かって、自分の石または番兵にぶつかるまで探索する
				while (true) {
					xxi += xi;
					yyi += yi;

					// cout << to_string(xxi) << to_string(yyi) << endl;

					if (board[xxi][yyi] == allyStone) {
						// cout << "隣接するセルの方角に、自分の石がありました。" << endl;

						reverseCellsVector.emplace_back(std::make_pair(nextCellX, nextCellY));
						// cout << "reverseCellsVectorに追加した：" << to_string(nextCellX) << to_string(nextCellY) << "cell_mapの要素数：";
						cout << to_string(reverseCellsVector.size()) << endl;

						// 反転対象ベクターに追加
						for (const auto& item : reverseCandidateCellsVector) {
							reverseCellsVector.emplace_back(item);
						}
						break;
					}

					if (board[xxi][yyi] == enemyStone) {
						reverseCandidateCellsVector.emplace_back(std::make_pair(xxi, yyi));
						// cout << "reverseCandidateCellsVectorに追加した：" << to_string(xxi) << to_string(yyi) << endl;
						continue;
					}

					if (board[xxi][yyi] == Cell::Sentinel) {
						break;
					}
				}
			}
		}
	}

	// 反転処理
	// https://www.delftstack.com/ja/howto/cpp/how-to-iterate-over-map-in-cpp/
	for (const auto& item : reverseCellsVector) {
		// cout << "[" << to_string(item.first) << "," << to_string(item.second) << "]" << endl;
		board[item.first][item.second] = allyStone;
	}

	cout << to_string(reverseCellsVector.size() - 1) << "個のセルを反転させました。" << endl;
}

bool is_board_full(Board& board) {

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (board[x][y] == Cell::Empty) {
				// cout << "満盤ではない" << endl;
				return false;
			}
		}
	}

	return true;
}

int judge_winner(Board& board) {

	int numOfBlack = 0;
	int numOfWhite = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (board[x][y] == Cell::Sentinel) continue;
			
			if (board[x][y] == Cell::Black) numOfBlack++;
			
			if (board[x][y] == Cell::White) numOfWhite++;
		}
	}

	if (numOfBlack == numOfWhite) return 0;

	return numOfWhite < numOfBlack ? 1 : 2;

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

	// int型に変換して返却
	return stoi(input.substr(1, 2));
}
