#include <iostream>
#include "board_view.hpp"

// 盤面の表示
void show_board(Board& board) {

	// xを内側のループにする。
	for (int y = 1; y < 9; y++) {
		for (int x = 1; x < 9; x++) {
			switch (board[x][y])
			{
			case Cell::White:
				std::cout << "○";
				break;

			case Cell::Black:
				std::cout << "●";
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
	
	std::string consoleOutput = player == Player::Black ? "黒の手番です" : "白の手番です";
	std::cout << consoleOutput << std::endl;
}

// 勝者を表示
void show_winner(int result, int numOfBlackStone, int numOfWhiteStone) {

	switch (result) {
		case 1:
			std::cout << "黒の勝ちです" << std::endl;
			break;
		case 2:
			std::cout << "白の勝ちです" << std::endl;
			break;
		default:
			std::cout << "接戦でしたね。引き分けです" << std::endl;
			break;
	}

	std::cout << "黒石の数：" << numOfBlackStone << std::endl;
	std::cout << "白石の数：" << numOfWhiteStone << std::endl;
}

void show_illegal_move_msg() {
	std::cout << "：" << "不正な手なので、再入力してくださいね？？" << std::endl;
}

void show_pass_msg() {
	std::cout << "：" << "石を置けるセルがないため、パスします" << std::endl;
}
