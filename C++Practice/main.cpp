#include <iostream>
#include <string>
#include <cstdlib>
#include "board_view.hpp"
#include "board_logic.hpp"

using namespace std;

// 関数プロトタイプ
void makeBoardForTest1(Board& board);

int main() {

	system("color f0");

	Board board;

	Player player = Player::Black;

	// 盤面の生成
	init_board(board);

	makeBoardForTest1(board);

	// 終局までループ
	while (!is_board_full(board, &player)) {

		// コマンドプロンプトクリア
		//clear_screen();
		
		// 盤面の表示
		show_board(board);
		// 手番の表示
		show_player(player);
		// 入力受付
		string input;
		int x_input;
		int y_input;
		do {
			// 盤上の座標は左上を原点として、横方向を a～h, 縦方向を 1～8 で表す。
			// (例：左上隅はa1，右下隅は h8)
			// 参考：https://www.othello.org/lesson/lesson/term.html
			cout << "配置場所を入力してください (例: E6): " << endl;
			cin >> input;

			x_input = convertAlphabetToNum(input);
			y_input = getYinput(input);
		} while (!is_legal_move(board, x_input, y_input, player, true));
		//石を配置する
		place_stone(board, x_input, y_input, player);

		player = player == Player::Black ? Player::White : Player::Black;

	}
	// 盤面の表示
	show_board(board);

	#ifndef DEBUG
	// 勝利判定
	int result = judge_winner(board);

	show_winner(result);
	#endif

	return 0;
}

// 動作確認用データ作成関数（黒石置けるセルなし）
void makeBoardForTest1(Board& board) {

	for (int i = 0; i < 10; i++) {
		board[i][9] = Cell::Sentinel;
		board[9][i] = Cell::Sentinel;
		board[i][0] = Cell::Sentinel;
		board[0][i] = Cell::Sentinel;
	}

	for (int i = 1; i < 9; i++) {
		board[1][i] = Cell::White;
	}

	board[2][1] = Cell::White;
	board[2][2] = Cell::White;
	board[2][3] = Cell::White;
	board[2][4] = Cell::White;
	board[2][5] = Cell::White;
	board[2][6] = Cell::White;
	board[2][7] = Cell::White;
	board[2][8] = Cell::Empty;

	board[3][1] = Cell::White;
	board[3][2] = Cell::White;
	board[3][3] = Cell::White;
	board[3][4] = Cell::Black;
	board[3][5] = Cell::White;
	board[3][6] = Cell::White;
	board[3][7] = Cell::Black;
	board[3][8] = Cell::Empty;

	board[4][1] = Cell::White;
	board[4][2] = Cell::White;
	board[4][3] = Cell::White;
	board[4][4] = Cell::White;
	board[4][5] = Cell::White;
	board[4][6] = Cell::White;
	board[4][7] = Cell::Black;
	board[4][8] = Cell::Black;

	board[5][1] = Cell::White;
	board[5][2] = Cell::White;
	board[5][3] = Cell::White;
	board[5][4] = Cell::White;
	board[5][5] = Cell::Black;
	board[5][6] = Cell::Black;
	board[5][7] = Cell::Black;
	board[5][8] = Cell::Black;

	board[6][1] = Cell::White;
	board[6][2] = Cell::White;
	board[6][3] = Cell::White;
	board[6][4] = Cell::Black;
	board[6][5] = Cell::Black;
	board[6][6] = Cell::Empty;
	board[6][7] = Cell::Empty;
	board[6][8] = Cell::Empty;

	board[7][1] = Cell::White;
	board[7][2] = Cell::White;
	board[7][3] = Cell::White;
	board[7][4] = Cell::White;
	board[7][5] = Cell::Empty;
	board[7][6] = Cell::Empty;
	board[7][7] = Cell::Empty;
	board[7][8] = Cell::Empty;

	board[8][1] = Cell::Empty;
	board[8][2] = Cell::White;
	board[8][3] = Cell::White;
	board[8][4] = Cell::White;
	board[8][5] = Cell::Empty;
	board[8][6] = Cell::Empty;
	board[8][7] = Cell::Empty;
	board[8][8] = Cell::Empty;
}
