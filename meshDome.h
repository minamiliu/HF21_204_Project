//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: meshDome.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/12
//
//============================================

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

//============================================
//インクルードファイル
//============================================
#include "scene.h"

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================

//============================================
//構造体定義
//============================================
class CMeshDome : public CScene
{
public:
	CMeshDome();
	virtual ~CMeshDome();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);

	static CMeshDome *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV);
	HRESULT Load(void);
	void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffTop;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffTop;	// インデックスバッファへのポインタ
	bool m_bLoadTexture;					// テクスチャを読み込んだかどうか

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3 m_pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3 m_rot;						// ポリゴンの回転角

	int m_nNumBlockH;						// ブロック数
	int m_nNumBlockV;						// ブロック数
	int m_nNumVertex;						// 総頂点数	
	int m_nNumVertexIndex;					// 総インデックス数
	int m_nNumPolygon;						// 総ポリゴン数
	float m_fRadius;						// 半径
};

#endif
