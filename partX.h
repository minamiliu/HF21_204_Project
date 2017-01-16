//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: partX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2017/01/04
//
//============================================

#ifndef _PARTX_H_
#define _PARTX_H_

//============================================
//インクルードファイル
//============================================

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CPartX
{
public:

	CPartX();
	virtual ~CPartX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPartX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	HRESULT LoadXfile(LPCSTR strFileName);
	
	void BindXfile( LPDIRECT3DTEXTURE9	pTexture,		// テクスチャへのポインタ
					LPD3DXMESH			pD3DXMesh,		// メッシュ情報へのポインタ
					LPD3DXBUFFER		pD3DXBuffMat,	// マテリアル情報へのポインタ
					DWORD				nNumMat);		// マテリアル情報の数


	//基本情報の設定、取得
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	D3DXVECTOR3 GetRot(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetRot(D3DXVECTOR3 rot); 

private:

	//変数
	LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャへのポインタ
	LPD3DXMESH  m_pD3DXMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER  m_pD3DXBuffMat;		// マテリアル情報へのポインタ
	DWORD	m_nNumMat;					// マテリアル情報の数

	D3DXVECTOR3 m_pos;					// モデルの位置
	D3DXVECTOR3 m_rot;					// モデルの向き(回転)
	D3DXVECTOR3 m_scl;					// モデルの大きさ(スケール)

	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

	D3DXVECTOR3 m_size;
	bool m_bLoadXfile;

};

#endif
