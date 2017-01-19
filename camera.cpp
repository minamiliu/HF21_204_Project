//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: camera.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/10
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "playerX.h"

//============================================
// マクロ定義
//============================================
#define	CAM_POS_V_X				(0.0f)					// カメラの視点初期位置(X座標)
#define	CAM_POS_V_Y				(100.0f)				// カメラの視点初期位置(Y座標)
#define	CAM_POS_V_Z				(-300.0f)				// カメラの視点初期位置(Z座標)
#define	CAM_POS_R_X				(0.0f)					// カメラの注視点初期位置(X座標)
#define	CAM_POS_R_Y				(0.0f)					// カメラの注視点初期位置(Y座標)
#define	CAM_POS_R_Z				(0.0f)					// カメラの注視点初期位置(Z座標)
#define	VIEW_ANGLE				(D3DXToRadian(60.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z				(100.f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z				(4000.0f)										// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA		(2.0f)											// カメラの移動量
#define	VALUE_ROTATE_CAMERA		(D3DX_PI * 0.01f)								// カメラの回転量
#define	VALUE_ADJUST_DISTANCE	(2.0f)											// 視点と注視点の距離調整量

#define CAM_ROT_X				(D3DXToRadian(22.0f))

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CCamera::CCamera()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CCamera::~CCamera()
{
	
}

HRESULT CCamera::Init(void)
{
	float fVecX,fVecZ;

	// 視点初期化
	m_posV = D3DXVECTOR3( CAM_POS_V_X, CAM_POS_V_Y, CAM_POS_V_Z);
	// 注視点初期化
	m_posR = D3DXVECTOR3( CAM_POS_R_X, CAM_POS_R_Y, CAM_POS_R_Z);
	// 上方向ベクトル初期化
	m_vecU = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
	// カメラ向き（回転角）の初期化
	m_rot = D3DXVECTOR3( CAM_ROT_X, 0.0f, 0.0f);
	// 視点と注視点の距離を求める
	fVecX = m_posV.x - m_posR.x;						// X方向（視点ー注視点）
	fVecZ = m_posV.z - m_posR.z;						// Z方向（視点ー注視点）
	// 視点と注視点の距離
	m_fDistance = sqrtf(fVecX * fVecX + fVecZ * fVecZ);

	return S_OK;
}

void CCamera::Uninit(void)
{

}

void CCamera::Update(void)
{

}

void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH( &m_mtxView, &m_posV, &m_posR, &m_vecU);
	
	// ビューマトリックスの設定
	pDevice->SetTransform( D3DTS_VIEW, &m_mtxView);
	
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxProjection);
	
	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH( &m_mtxProjection, VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);
	
	// プロジェクションマトリックスの設定(透視変換の設定)
	pDevice->SetTransform( D3DTS_PROJECTION, &m_mtxProjection);
}

D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}
void CCamera::SetPosR(D3DXVECTOR3 posR)
{
	m_posR = posR;
}

D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}
void CCamera::SetPosV(D3DXVECTOR3 posV)
{
	m_posV = posV;
}

D3DXMATRIX *CCamera::GetMtxView(void)
{
	return &m_mtxView;
}
D3DXMATRIX *CCamera::GetMtxProjection(void)
{
	return &m_mtxProjection;
}