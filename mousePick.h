//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: mousePick.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/06
//
//============================================

#ifndef _MOUSEPICK_H_
#define _MOUSEPICK_H_

//============================================
//インクルードファイル
//============================================
#include "main.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CMousePick
{
public:

	CMousePick();
	virtual ~CMousePick();

	static D3DXVECTOR3 GetWorldPos( POINT pos);

private:

	// スクリーン座標をワールド座標に変換
	static D3DXVECTOR3 *CalcScreenToWorld(
		D3DXVECTOR3* pout,
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

	// XZ平面とスクリーン座標の交点算出関数
	static D3DXVECTOR3 *CMousePick::CalcScreenToXZ(
		D3DXVECTOR3* pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

};

#endif
