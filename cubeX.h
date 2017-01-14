//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: cubeX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

#ifndef _CUBEX_H_
#define _CUBEX_H_

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

class CCubeX : public CSceneX
{
public:
	typedef enum
	{
		TYPE_1X1 = 0,
		TYPE_1X2,
		TYPE_1X4,
		TYPE_MAX,
	}TYPE;

	CCubeX();
	virtual ~CCubeX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	float GetDistanceBoxPoint(D3DXVECTOR3 point);
	TYPE GetType(void);

	static HRESULT Load(void);
	static void Unload(void);
	static CCubeX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sideLen, TYPE type);

protected:
	D3DXVECTOR3 GetSideMin(void);
	D3DXVECTOR3 GetSideMax(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[TYPE_MAX];		// マテリアル情報の数

	D3DXVECTOR3 m_sideLen;
	TYPE m_type;
};

#endif
