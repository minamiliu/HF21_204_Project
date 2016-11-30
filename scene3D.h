//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene3D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//============================================
//インクルードファイル
//============================================
#include "scene.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CScene3D : public CScene
{
public:

	CScene3D();
	virtual ~CScene3D();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	//関数
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	//変数

	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;	// インデックスバッファへのポインタ

	D3DXVECTOR3		m_pos;					// 位置
	D3DXVECTOR3		m_rot;					// 向き
	D3DXMATRIX		m_mtxWorld;				// ワールドマトリックス

	int m_nNumBlockX, m_nNumBlockZ;			// ブロック数
	int m_nNumVertex;						// 総頂点数
	int m_nNumVertexIndex;					// 総インデックス数
	int m_nNumPolygon;						// 総ポリゴン数
	float m_fSizeBlockX, m_fSizeBlockZ;		// ブロックサイズ

	D3DXVECTOR3 m_size;
};

#endif
