//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: playerX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

#ifndef _TOY_H_
#define _TOY_H_

//============================================
//インクルードファイル
//============================================
#include "sceneX.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CToy : public CSceneX
{
public:

	CToy();
	virtual ~CToy();
	typedef enum
	{
			TYPE_ROBOT,
			TYPE_BLOCK,
			TYPE_CAR,
			TYPE_BEAR,
			TOYTYPE_MAX
	}TOYTYPE;
	#define MAX_TOYTYPE (TOYTYPE_MAX)

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CToy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	static HRESULT CToy::LoadXfile(LPCSTR strFileName, int nCnt);
	void CToy::BindXfile( int type);

	void CToy::ChangePicked(bool pick);
private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[MAX_TOYTYPE];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[MAX_TOYTYPE];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[MAX_TOYTYPE];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[MAX_TOYTYPE];		// マテリアル情報の数
	bool m_bPicked;
	static int m_nNumber;
};

#endif
