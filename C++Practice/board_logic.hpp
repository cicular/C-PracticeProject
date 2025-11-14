// 多重インクルード防止
#pragma once
#include <array>
#include <string>

// セルの状態
enum class Cell { Empty, Black, White, Sentinel };

// プレイヤーの手番
enum class Player { Black, White };

// 盤面型（番兵含め10×10）
using Board = std::array<std::array<Cell, 10>, 10>;

// 盤面の作成（番兵を含んだ10×10のボードをつくる）
void init_board(Board& board);

// 合法手判定（合法手ならtrueを返し、不正手ならfalseを返す）
bool is_legal_move(const Board& board, int x_input, int y_input, Player player);

// 石を配置し、ひっくり返す
void place_stone(Board& board, int x_input, int y_input, Player player);

// 終了（満盤）判定（64マス内にEmptyがあるか判定。Emptyが0個ならtrue）
bool is_board_full(const Board& board);

// ゲームの勝者を判定（黒石の数/白石の数を数える）
int judge_winner(const Board& board, int* numOfBlackStone, int *numOfWhiteStone);

// アルファベットから数字に変換
int convert_alphabet_to_num(const std::string input);

// まだEmptyのセルがあればtrue
bool has_any_legal_move(const Board& board, Player player);
