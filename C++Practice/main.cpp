#include <iostream>
#include <string>
#include "board_view.hpp"
#include "board_logic.hpp"

using namespace std;

int main() {

	cout << "オセロスタート！！";

	Board board;

	Player player = Player::Black;

	// 盤面の生成
	init_board(board);

	// 終局までループ
	while (!is_board_full(board)) {

		// コマンドプロンプトクリア
		//clear_screen();
		// 盤面の表示
		show_board(board);
		// 手番の表示
		show_player(player);
		// 入力受付
		string input;
		do {
			// 盤上の座標は左上を原点として、横方向を a～h, 縦方向を 1～8 で表す。
			// (例：左上隅はa1，右下隅は h8)
			// 参考：https://www.othello.org/lesson/lesson/term.html
			std::cout << "配置場所を入力してください (例: E6): " << std::endl;
			cin >> input;
		} while (!is_legal_move(board, input, player));
		//石を配置する
		place_stone();

		player = player == Player::Black ? Player::White : Player::Black;

	}
	// 盤面の表示
	show_board(board);

	#ifdef DEBUG
	// 勝利判定
	judge_winner();
	#endif

	return 0;
}
