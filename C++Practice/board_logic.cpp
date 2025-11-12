#include <iostream>
#include <vector>
#include "board_logic.hpp"

using namespace std;

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
bool is_legal_move(Board& board, int x_int, int y_int, Player player, bool consoleOutput) {

	if (x_int == -1 || y_int < 1 || y_int > 8) {
		if (consoleOutput) cout << "不正な手なので、再入力してくださいね？？" << endl;
		return false;
	}

	// そもそもそのセルがEmptyであること
	if (board[x_int][y_int] != Cell::Empty) {
		if (consoleOutput) cout << "不正な手なので、再入力してくださいね？？" << endl;
		return false;
	}

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

	if (consoleOutput) cout << "不正な手なので、再入力してくださいね？？" << endl;
	return false;
}

/*
	石のひっくり返し処理
*/
void place_stone(Board& board, int x_int, int y_int, Player player) {

	cout << "石のひっくり返し処理を開始します。";

	Cell enemyStone = player == Player::Black ? Cell::White : Cell::Black;
	Cell allyStone = player == Player::Black ? Cell::Black : Cell::White;

	cout << "入力された座標は、" << to_string(x_int) << to_string(y_int) << endl;

	// 反転させる対象の石
	// mapだと、キー重複ができないため、x軸でひっくり返す石が複数ある時、最初の1つしか反転できない。
	// そのため、<pair<int, int>をvectorで保持する
	vector<pair<int, int>> reverseCellsVector;

	// まず入力座標を反転対象ベクターに追加
	reverseCellsVector.emplace_back(make_pair(x_int, y_int));

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

				// 隣接する敵の石の方角に向かって、自分の石または番兵または空白セルにぶつかるまで探索する
				while (true) {
					xxi += xi;
					yyi += yi;

					// cout << to_string(xxi) << to_string(yyi) << endl;

					if (board[xxi][yyi] == allyStone) {
						// cout << "隣接するセルの方角に、自分の石がありました。" << endl;

						reverseCellsVector.emplace_back(make_pair(nextCellX, nextCellY));
						// cout << "reverseCellsVectorに追加した：" << to_string(nextCellX) << to_string(nextCellY) << "cell_mapの要素数：";
						// cout << to_string(reverseCellsVector.size()) << endl;

						// 反転対象ベクターに追加
						for (const auto& item : reverseCandidateCellsVector) {
							reverseCellsVector.emplace_back(item);
						}
						break;
					}

					if (board[xxi][yyi] == enemyStone) {
						reverseCandidateCellsVector.emplace_back(make_pair(xxi, yyi));
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

	cout << to_string(reverseCellsVector.size() - 1) << "個のセルを反転させました。" << endl;
}

// 黒/白ともに打てるセルが存在しなくなったか判定
bool is_board_full(Board& board, Player* player) {

	// 64マス全て埋まった場合に「パスします」メッセージを出さないためにまずは全件チェック
	int numOfEmpty = 0;
	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			if (board[x][y] == Cell::Empty) {
				numOfEmpty++;
			}
		}
	}

	if (numOfEmpty == 0) return true;

	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			if (board[x][y] == Cell::Empty) {
				if (is_legal_move(board, x, y, *player, false)) {
					// まだ石を置ける座標があった
					return false;
				}
			}
		}
	}

	// 手番を変更
	cout << "石を置けるセルがないため、パスします" << endl;
	*player = *player == Player::Black ? Player::White : Player::Black;

	for (int x = 1; x < 9; x++) {
		for (int y = 1; y < 9; y++) {
			if (board[x][y] == Cell::Empty) {
				if (is_legal_move(board, x, y, *player, false)) {
					// まだ石を置ける座標があった
					return false;
				}
			}
		}
	}

	// 黒・白ともに石を置けるセルが存在しないため、対局終了
	return true;
}

// 勝者判定
int judge_winner(Board& board, int* numOfBlackStone, int *numOfWhiteStone) {

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
int convertAlphabetToNum(string input) {

	char x_alphabet = toupper(input.front());

	// Aの文字コードは10進数で65
	if (x_alphabet >= 'A' && x_alphabet <= 'H') return x_alphabet - 'A' + 1;

	return -1;

}

int getYinput(string input) {

	// int型に変換して返却
	return stoi(input.substr(1, 2));
}
