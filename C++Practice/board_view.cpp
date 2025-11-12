#include <iostream>
#include "board_view.hpp"

using namespace std;

// 盤面の表示
void show_board(Board& board) {

	// xを内側のループにする。
	for (int y = 1; y < 9; y++) {
		for (int x = 1; x < 9; x++) {
			switch (board[x][y])
			{
			case Cell::White:
				cout << "○";
				break;

			case Cell::Black:
				cout << "●";
				break;

			default:
				cout << "-";
				break;
			}
		}
		cout << endl;
	}
}

// 手番の表示（黒番or白番どちらの手番かを標準出力）
void show_player(Player player) {
	
	string consoleOutput = player == Player::Black ? "黒の手番です" : "白の手番です";
	cout << consoleOutput << endl;
}

// 勝者を表示
void show_winner(int result, int numOfBlackStone, int numOfWhiteStone) {

	switch (result) {
		case 1:
			cout << "黒の勝ちです" << endl;
			break;
		case 2:
			cout << "白の勝ちです" << endl;
			break;
		default:
			cout << "接戦でしたね。引き分けです" << endl;
			break;
	}

	cout << "黒石の数：" << numOfBlackStone << endl;
	cout << "白石の数：" << numOfWhiteStone << endl;
}
