// 多重インクルード防止
#pragma once
#include "board_logic.hpp"

// 盤面の表示 ※メソッド名は変えないでください。引数と戻り値は変更可
void show_board(Board& board);

// 手番の表示（黒番or白番どちらの手番かを標準出力）※メソッド名は変えないでください。引数と戻り値は変更可
void show_player(Player player);

// コマンドプロンプトのそれまでの出力をクリア ※メソッド名は変えないでください。引数と戻り値は変更可
void clear_screen();

// 勝者を表示 ※メソッド名は変えないでください。引数と戻り値は変更可
void show_winner(int result);

// ※必要に応じてメソッドの追加可
