//============================================
//
// タイトル:	 CL25課題
// プログラム名: sceneX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

#ifndef _SCENEX_H_
#define _SCENEX_H_

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
//敵クラス
class CSceneX : public CScene
{
public:

	CSceneX();
	virtual ~CSceneX();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);

private:
	//関数
	D3DXVECTOR3 Get2VecRotAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);

	//変数
	LPDIRECT3DTEXTURE9	m_pTexture;		// テクスチャへのポインタ
	LPD3DXMESH  m_pD3DXMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER  m_pD3DXBuffMat;		// マテリアル情報へのポインタ
	DWORD	m_nNumMat;					// マテリアル情報の数

	D3DXVECTOR3 m_pos;					// モデルの位置
	D3DXVECTOR3 m_rot;					// モデルの向き(回転)
	D3DXVECTOR3 m_scl;					// モデルの大きさ(スケール)
	D3DXVECTOR3 m_move;					// モデルの移動量
	float m_speed;						// モデルのスピード

	D3DXVECTOR3 m_rotTarget;			// モデルの向き(回転)
	D3DXVECTOR3 m_rotAngle;				// モデルの向き(回転)

	//キーフレイム
	//D3DXVECTOR3 posChild;				//子座標
	//D3DXVECTOR3 posChildTarget;		//子座標の目標
	//D3DXVECTOR3 rotChild;				//子座標の向き
	//D3DXVECTOR3 rotChildAngle;		//子座標の毎回の回転量
	//D3DXVECTOR3 rotChildTarget;		//子座標の向きの目標

	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

};

#endif
