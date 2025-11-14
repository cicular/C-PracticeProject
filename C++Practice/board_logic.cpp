#include <iostream>
#include <vector>
#include "board_logic.hpp"

/*
	番兵を含めた10×10の盤面を初期化する。
*/
void init_board(Board& board) {

	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
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
}

/*
	合法手判定
*/
bool is_legal_move(const Board& board, int x_int, int y_int, Player player) {

	if (x_int == -1 || y_int < 1 || y_int > 8) return false;

	// そもそもそのセルがEmptyであること
	if (board[x_int][y_int] != Cell::Empty) return false;

	Cell enemyStone = player == Player::Black ? Cell::White : Cell::Black;
	Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

	// 置かれたセルを起点にして全方向探索
	for (int xi = -1; xi <= 1; xi++) {
		for (int yi = -1; yi <= 1; yi++) {

			int xxi = x_int + xi;
			int yyi = y_int + yi;
			// cout << to_string(xxi) << to_string(yyi) << endl;
			// 隣接する8個のセルに敵の石が存在するか
			if (board[xxi][yyi] == enemyStone) {

				while (true) {
					xxi += xi;
					yyi += yi;

					// cout << to_string(xxi) << to_string(yyi) << endl;

					// 隣接するセルの方角に、自分の石が存在するか
					if (board[xxi][yyi] == allyStone) {
						return true;
					}
					// 番兵または空白セルぶつかったら終端なのでループを抜ける
					if (board[xxi][yyi] == Cell::Sentinel || board[xxi][yyi] == Cell::Empty) break;
				}
			}
		}
	}

	return false;
}

/*
	石のひっくり返し処理
*/
void place_stone(Board& board, int x_int, int y_int, Player player) {

	Cell enemyStone = player == Player::Black ? Cell::White : Cell::Black;
	Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

	std::cout << "入力された座標は、" << std::to_string(x_int) << std::to_string(y_int) << std::endl;

	// 反転させる対象の石
	// mapだと、キー重複ができないため、x軸でひっくり返す石が複数ある時、最初の1つしか反転できない。
	// そのため、<pair<int, int>をvectorで保持する
	std::vector<std::pair<int, int>> reverseCellsVector;

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
				std::vector<std::pair<int, int>> reverseCandidateCellsVector;

				// 隣接する敵の石の方角に向かって、自分の石または番兵または空白セルにぶつかるまで探索する
				while (true) {
					xxi += xi;
					yyi += yi;

					// cout << to_string(xxi) << to_string(yyi) << endl;

					if (board[xxi][yyi] == allyStone) {
						// cout << "隣接するセルの方角に、自分の石がありました。" << endl;

						reverseCellsVector.emplace_back(std::make_pair(nextCellX, nextCellY));
						// cout << "reverseCellsVectorに追加した：" << to_string(nextCellX) << to_string(nextCellY) << "cell_mapの要素数：";
						// cout << to_string(reverseCellsVector.size()) << endl;

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

					if (board[xxi][yyi] == Cell::Empty || board[xxi][yyi] == Cell::Sentinel) break;

				}
			}
		}
	}

	// 最後にまとめて反転処理
	// https://www.delftstack.com/ja/howto/cpp/how-to-iterate-over-map-in-cpp/
	for (const auto& item : reverseCellsVector) {
		// cout << "[" << to_string(item.first) << "," << to_string(item.second) << "]" << endl;
		board[item.first][item.second] = allyStone;
	}

	std::cout << std::to_string(reverseCellsVector.size() - 1) << "個のセルを反転させました。" << std::endl;
}

bool is_board_full(const Board& board) {

	// 空きマスが1つでもあれば false、なければ true
	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			if (board[x][y] == Cell::Empty) {
				return false;
			}
		}
	}

	return true;
}

// 勝者判定
int judge_winner(const Board& board, int* numOfBlackStone, int *numOfWhiteStone) {

	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			// *numOfWhiteStone++;と書くと、
			// numOfWhiteStone（アドレス）が1つ先（+sizeof(int) バイト）に進んでしまうので誤り
			if (board[x][y] == Cell::Black) (*numOfBlackStone)++;
			if (board[x][y] == Cell::White) (*numOfWhiteStone)++;
		}
	}

	return *numOfBlackStone == *numOfWhiteStone ? 0 : *numOfWhiteStone < *numOfBlackStone ? 1 : 2;

}

// 文字コードを利用してint型に変換
int convert_alphabet_to_num(const std::string input) {

	char x_alphabet = toupper(input.front());

	// Aの文字コードは10進数で65
	if (x_alphabet >= 'A' && x_alphabet <= 'H') return x_alphabet - 'A' + 1;

	return -1;

}

bool has_any_legal_move(const Board& board, Player player) {

	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			if (board[x][y] == Cell::Empty) {
				if (is_legal_move(board, x, y, player)) {
					// まだ石を置ける座標があった
					return true;
				}
			}
		}
	}

	return false;
}
