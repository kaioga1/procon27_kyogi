#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utility>
#include <vector>
#include <map>
//二つの値から大小関係により一方を選択するマクロを作る。
//二つの値のうち小さい方を選択する
#define min(a, b)  (((a) < (b)) ? (a) : (b))
// 二つの値のうち大きい方を選択する
#define max(a, b)  (((a) > (b)) ? (a) : (b))
using namespace std;


//２次元平面上の２つの線分が交差するか判定する関数を作る。
//構造体：
typedef struct POINT_tag // POINT_t …… 点
{
	int x; // x 座標
	int y; // y 座標
} POINT_t;

typedef struct LINE_tag // LINE_t …… 線分、直線
{
	POINT_t a; // 始点
	POINT_t b; // 終点
} LINE_t;

//*********************************************************
// 点 p が有向線分 e(a,b) の左右どちら側にあるか調べる。
// 点 p が有向線分 e の　左側にある場合  1 を、
// 　   　有向線分 e の直線上にある場合  0 を、
// 　   　有向線分 e の　右側にある場合 -1 を返す。
//*********************************************************
int side(POINT_t &p, LINE_t &e)
{
	POINT_t & p1 = p;
	POINT_t p2 = e.a; // 有向線分 e の始点
	POINT_t p3 = e.b; // 有向線分 e の終点

	// 有向線分 (p2,p1), (p2,p3) の外積の z 成分を求める
	const int n  = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	if      (n > 0) return  1; // 左
	else if (n < 0) return -1; // 右
	else            return  0; // 線上
}//side

//*********************************************************
// 点 a, b が直線 e を跨いで存在するか判定する。
// 点 a, b が直線 e を跨いでいれば真、さもなくば偽を返す
// 点が直線上に存在する場合には『直線を跨ぐ』と判断する。
//*********************************************************
/*int straddle(LINE_t *e, POINT_t *a, POINT_t *b)
{
	// 点 a, b が互いに有向線分 e の異なる側にあるならば、点 a, b は線分 e を跨ぐ。
	return 0 >= (side(a,e) * side(b,e));
}//straddle
*/
//関数：
//*********************************************************
// 線分 e1, e2 が交差するか判定する。
// 線分 e1, e2 が交差すれば真、さもなくば偽を返す
//*********************************************************
int intersect(LINE_t &e1, LINE_t &e2)
{
	// 線分 e1, e2 を対角線とする２つの長方形が交わらない場合、線分 e1, e2 が交わることはない。
	if ( min(e1.a.x, e1.b.x) > max(e2.a.x, e2.b.x) ) return 0;
	if ( min(e1.a.y, e1.b.y) > max(e2.a.y, e2.b.y) ) return 0;
	if ( min(e2.a.x, e2.b.x) > max(e1.a.x, e1.b.x) ) return 0;
	if ( min(e2.a.y, e2.b.y) > max(e1.a.y, e1.b.y) ) return 0;

	// 線分 e2 が直線 e1 を跨ぎ、かつ、線分 e1 が直線 e2 を跨ぐならば、線分 e1, e2 は交差する。
	return 1;//straddle(e1, &e2->a, &e2->b) && straddle(e2, &e1->a, &e1->b);
}//intersect

int main(){
	POINT_t a, b;
	int out;
	out = side(*a,*b);
	cout << out << endl;

	return 0; 
}
