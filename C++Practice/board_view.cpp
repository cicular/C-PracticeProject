#include <iostream>
#include "board_view.hpp"

// 盤面の表示
void show_board(Board& board) {

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			switch (board[x][y])
			{
			case Cell::White:
				std::cout << "○";
				break;

			case Cell::Black:
				std::cout << "●";
				break;

			case Cell::Sentinel:
				//std::cout << "-";
				break;

			default:
				std::cout << "-";
				break;
			}
		}
		std::cout << std::endl;
	}
}

// 手番の表示（黒番or白番どちらの手番かを標準出力）
void show_player(Player player) {
	
	if (player == Player::Black) {
		std::cout << "黒の手番です" << std::endl;
	} else {
		std::cout << "白の手番です" << std::endl;
	}
}

// 勝者を表示
void show_winner() {

}
