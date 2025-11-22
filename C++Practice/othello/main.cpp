#include <iostream>
#include <string>
#include <cstdlib>
#include "board_view.hpp"
#include "board_logic.hpp"

#define TEST

#ifdef TEST
#include <map>
#include "game_test.hpp"
#endif

int main() {

#ifdef TEST
	std::map<int, std::string> kifuMap = makeTestGameData(TEST_KIFU5);
	int moveCount = 0;
#endif

	system("color f0");

	Board board;

	Player player = Player::Black;

	// 盤面の生成
	init_board(board);

	// 終局までループ
	while (!is_board_full(board)) {

		if (!has_any_legal_move(board, player)) {
			// 手番を変更
			show_pass_msg();
			player = player == Player::Black ? Player::White : Player::Black;
			// 黒・白ともに石を置けるセルが存在しないため、対局終了
			if (!has_any_legal_move(board, player)) break;
		}

		// コマンドプロンプトクリア
		clear_screen();
		
		// 盤面の表示
		show_board(board);
		// 手番の表示
		show_player(player);
		// 入力受付
		std::string input;
		int x_input, y_input;
		bool legal_move_flg = false;

		do {
#ifdef TEST
			moveCount++;
			input = kifuMap.at(moveCount);
#else
			// 盤上の座標は左上を原点として、横方向をa～h, 縦方向を1～8で表す。
			// (例：左上隅はa1，右下隅は h8)
			// 参考：https://www.othello.org/lesson/lesson/term.html
			std::cout << "配置場所を入力してください (例: E6): " << std::endl;
			std::cin >> input;
#endif
			x_input = convert_alphabet_to_num(input);
			y_input = stoi(input.substr(1, 2));

			legal_move_flg = is_legal_move(board, x_input, y_input, player);
			if (!legal_move_flg) show_illegal_move_msg();
		} while (!legal_move_flg);
		//石を配置する
		place_stone(board, x_input, y_input, player);
		// 手番変更
		player = player == Player::Black ? Player::White : Player::Black;

	}
	clear_screen();

	// 盤面の表示
	show_board(board);

	int numOfBlackStone = 0, numOfWhiteStone = 0;

	// 関数呼び出しの各引数がどの順に評価されるかは保証されないため、以下の書き方はNG。
	// 評価順序が未規定なので、処理系によっては先にnumOfBlackStone/numOfWhiteStone（まだ0）をコピー
	// →その後で第1引数のjudge_winnerが実行（カウント更新）という順になることがある。
	// 勝利判定と表示
	// show_winner(judge_winner(board, &numOfBlackStone, &numOfWhiteStone), numOfBlackStone, numOfWhiteStone);

	int winner = judge_winner(board, &numOfBlackStone, &numOfWhiteStone);

	// 評価順序に依存しないよう、先に結果を確定させてから渡す。
	show_winner(winner, numOfBlackStone, numOfWhiteStone);

	return 0;
}
