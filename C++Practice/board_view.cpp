#include <iostream>
#include "board_view.hpp"

using namespace std;

// 盤面の表示
void show_board(Board& board) {

	// xを内側のループにする。
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			switch (board[x][y])
			{
			case Cell::White:
				cout << "○";
				break;

			case Cell::Black:
				cout << "●";
				break;

			case Cell::Sentinel:
				// cout << "△";
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
	
	if (player == Player::Black) {
		cout << "黒の手番です" << endl;
	} else {
		cout << "白の手番です" << endl;
	}
}

// 勝者を表示
void show_winner() {

}
