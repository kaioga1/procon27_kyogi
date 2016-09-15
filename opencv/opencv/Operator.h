#pragma once
# include "Common.h"

class GUI;

/*
全体を操作するクラス
これがメインのクラスになる(はず
*/
class Operator {
public:
	//クォンストラクタ(ふざけた
	Operator();

	
private:
	shared_ptr<PieceManager> piece_manager;
	shared_ptr<GUI> gui;
};