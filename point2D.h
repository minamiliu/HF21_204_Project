//============================================
//
// タイトル:	 HF
// プログラム名: trash.h
// 作成者:		 HAL東京ゲーム学科　yamaga keisuke
// 作成日:       2016/11/10
//
//============================================

#ifndef _POINT2D_H_
#define _POINT2D_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CPoint2D : public CScene2D
{
public:

	CPoint2D();
	virtual ~CPoint2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPoint2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CPoint2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HWND hwnd);


private:
	D3DXVECTOR3 m_startPos;//ベクトルの始点
	D3DXVECTOR3 m_endPos;//ベクトルの終点
	D3DXVECTOR3 m_speed;
	HWND m_hwnd;
};

#endif
