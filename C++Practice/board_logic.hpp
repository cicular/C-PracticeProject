// 多重インクルード防止
#pragma once
#include <array>
#include <string>

using namespace std;

// セルの状態
enum class Cell { Empty = 0, Black=1, White=2, Sentinel =-1 };

// プレイヤーの手番
enum class Player { Black, White };

enum class Horizontal { A=1, B=2 };

// 盤面型（番兵含め10×10）
using Board = std::array<std::array<Cell, 10>, 10>;

// 盤面の作成（番兵を含んだ10×10のボードをつくる） ※メソッド名は変えないでください。引数と戻り値は変更可
void init_board(Board& board);

// 合法手判定（合法手ならtrueを返し、不正手ならfalseを返す） ※メソッド名は変えないでください。引数と戻り値は変更可
bool is_legal_move(Board& board, string input, Player player);

//石を配置し、ひっくり返す ※メソッド名は変えないでください。引数と戻り値は変更可
void place_stone(); 

// 終了（満盤）判定（石が置けるマスがあるか判定。満盤ならtrue）※メソッド名と戻り値は変えないでください。引数と変更可
bool is_board_full(Board& board);

// ゲームの勝者を判定（黒石の数/白石の数を数える）※メソッド名と戻り値は変えないでください。引数は変更可
int judge_winner();

// ※必要に応じてメソッドの追加可
