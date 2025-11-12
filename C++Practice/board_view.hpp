// 多重インクルード防止
#pragma once
#include "board_logic.hpp"

// 盤面の表示
void show_board(Board& board);

// 手番の表示（黒番or白番どちらの手番かを標準出力）
void show_player(Player player);

// コマンドプロンプトのそれまでの出力をクリア
void clear_screen();

// 勝者を表示
void show_winner(int result, int numOfBlackStone, int numOfWhiteStone);

// 不正手を入力された場合のメッセージを表示
void show_illegal_move_msg();
