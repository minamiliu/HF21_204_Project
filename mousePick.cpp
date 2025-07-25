﻿//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: mousePick.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/06
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "mousePick.h"

//============================================
// マクロ定義
//============================================

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
//コンストラクタ
//=============================================================================
CMousePick::CMousePick()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CMousePick::~CMousePick()
{
	
}

D3DXVECTOR3 *CMousePick::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
) 
{
	// 各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse( &InvView, NULL, View );
	D3DXMatrixInverse( &InvPrj, NULL, Prj );
	D3DXMatrixIdentity( &VP );
	VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
	VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
	D3DXMatrixInverse( &InvViewport, NULL, &VP );

	// 逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord( pout, &D3DXVECTOR3(Sx,Sy,fZ), &tmp );

	return pout;
}

D3DXVECTOR3 *CMousePick::CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	int Screen_w,
	int Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
	CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
	ray = farpos - nearpos;
	D3DXVec3Normalize( &ray, &ray );

	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if( ray.y <= 0 ) {
		// 床交点
		float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
		float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
		*pout = nearpos + (LP0/Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}

D3DXVECTOR3 CMousePick::GetWorldPos( POINT pos)
{
	D3DXVECTOR3 pout;
	D3DXMATRIX *mtxView = CManager::GetCamera()->GetMtxView();
	D3DXMATRIX *mtxProjection = CManager::GetCamera()->GetMtxProjection();

	CalcScreenToXZ( &pout, pos.x, pos.y, SCREEN_WIDTH, SCREEN_HEIGHT, mtxView, mtxProjection);

	return pout;
}