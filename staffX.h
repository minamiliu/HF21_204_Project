//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: staffX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/23
//
//============================================

#ifndef _STAFF_H_
#define _STAFF_H_

//============================================
//インクルードファイル
//============================================
#include "sceneX.h"

//============================================
//マクロ定義
//============================================
#define MAX_LIMB (4)
//============================================
//前方宣言
//============================================
class CShadow;

//============================================
//構造体定義
//============================================
class CStaffX : public CSceneX
{
public:

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_000,
		TYPE_MAX,
	}TYPE;

	CStaffX();
	virtual ~CStaffX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStaffX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//モデル関係
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[TYPE_MAX];		// マテリアル情報の数	

	CShadow *m_pShadow;			//影
};

#endif
