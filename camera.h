//============================================
//
// タイトル:	 CL25課題
// プログラム名: camera.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//============================================
//インクルードファイル
//============================================
#include "main.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CCamera
{
public:

	CCamera();
	virtual ~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCamera(void);
	//CCamera *GetCamera(void);

private:

	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// 向き（回転角）
	float m_fDistance;			// 視点と注視点の距離
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		// ビューマトリックス
};

#endif
