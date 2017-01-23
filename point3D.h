//============================================
//
// タイトル:	 HF
// プログラム名: trash.h
// 作成者:		 HAL東京ゲーム学科　yamaga keisuke
// 作成日:       2016/11/10
//
//============================================

#ifndef _POINT3D_H_
#define _POINT3D_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================
class CChange;

//============================================
//構造体定義
//============================================

class CPoint3D : public CScene2D
{
public:

	CPoint3D();
	virtual ~CPoint3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPoint3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CPoint3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HWND hwnd);
	D3DXVECTOR3 Get3DPosition(void);
	void CPoint3D::ChangeZebra(void);
	
private:
	D3DXVECTOR3 m_startPos;//ベクトルの始点
	D3DXVECTOR3 m_endPos;//ベクトルの終点
	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_3Dpos;
	HWND m_hwnd;
	static bool m_zebra;
	CChange *m_pChange; //変身
};

#endif
