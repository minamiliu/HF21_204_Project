//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: limbX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/16
//
//============================================

#ifndef _LIMBX_H_
#define _LIMBX_H_

//============================================
//インクルードファイル
//============================================
#include "partX.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CLimbX : public CPartX
{
public:
	typedef struct
	{
		int nFrame;
		float rotX;
	}MOTION;

	typedef enum
	{
		TYPE_L_HAND = 0,
		TYPE_R_HAND,
		TYPE_L_FOOT,
		TYPE_R_FOOT,
		TYPE_LION_L_HAND,
		TYPE_LION_R_HAND,
		TYPE_LION_L_FOOT,
		TYPE_LION_R_FOOT,
		TYPE_MAX,
	}TYPE;

	CLimbX();
	virtual ~CLimbX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindXfile(TYPE type);

	static CLimbX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:

	//変数
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[TYPE_MAX];		// マテリアル情報の数

	TYPE m_type;

	//モーション
	static MOTION *m_pMotionPara;
	int m_nCntFrame;
	int m_nMotionNow;
	float m_rotXTurn;
	float m_rotXLocal;
	D3DXVECTOR3 m_posLocal;
	D3DXVECTOR3 m_rotLocal;

};

#endif
