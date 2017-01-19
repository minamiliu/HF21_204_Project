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
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//============================================
//構造体定義
//============================================
//３Ｄポリゴン
typedef struct
{
	D3DXVECTOR3 vtx; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR	col; //頂点カラー
	D3DXVECTOR2	tex; //テクスチャ座標
}VERTEX_3D;

class CScene3D : public CScene
{
public:

	CScene3D();
	CScene3D(LAYER layer);
	virtual ~CScene3D();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, bool bUseYnotZ);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Draw(const D3DXMATRIX *mtxView);

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, bool bUseYnotZ);

	HRESULT Load(LPCSTR strFileName);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetColor(const D3DXCOLOR &col); //色を変更
	
protected:
	virtual bool HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint);

private:
	//関数
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	//変数
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;		// インデックスバッファへのポインタ
	bool m_bLoadTexture;					// テクスチャを読み込んだかどうか

	D3DXVECTOR3		m_pos;					// 位置
	D3DXVECTOR3		m_rot;					// 向き
	D3DXMATRIX		m_mtxWorld;				// ワールドマトリックス

	int m_nNumBlockX, m_nNumBlockZ;			// ブロック数
	int m_nNumVertex;						// 総頂点数
	int m_nNumVertexIndex;					// 総インデックス数
	int m_nNumPolygon;						// 総ポリゴン数
	float m_fSizeBlockX, m_fSizeBlockZ;		// ブロックサイズ

	D3DXVECTOR3 m_size;
	bool m_bUseYnotZ;
};

#endif
