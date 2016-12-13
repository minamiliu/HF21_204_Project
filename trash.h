//============================================
//
// タイトル:	 HF
// プログラム名: trash.h
// 作成者:		 HAL東京ゲーム学科　yamaga keisuke
// 作成日:       2016/11/10
//
//============================================

#ifndef _TRASH_H_
#define _TRASH_H_

//============================================
//インクルードファイル
//============================================
#include "scene2D.h"

//============================================
//マクロ定義
//============================================
#define MAX_TRASH (256)
//============================================
//構造体定義
//============================================

class CTrash : public CScene2D
{
public:
	typedef enum
	{
		TRASHTYPE_NORMAL = 0,
		TRASHTYPE_LIGHT,
		TRASHTYPE_HEAVY,
		TRASHTYPE_MAX
	}TRASHTYPE;
	CTrash();
	virtual ~CTrash();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrash *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName,OBJTYPE type);
	D3DXVECTOR3 GetSpeed(void);
	void SetSpeed(D3DXVECTOR3 speed);
	void ReverseMove(void);
	TRASHTYPE GetTrashType(void);
	void TrashEnd(void);
private:
	D3DXVECTOR3 m_speed;
	bool m_fallFlag;//落下フラグ
	bool m_apFlag;//出現フラグ
	static int m_cnt;//出現タイミングカウンター
	float m_gravityCoefficient;//重力係数
	static LPDIRECT3DTEXTURE9 m_pTexture;
	TRASHTYPE m_TrashType;
};

#endif
