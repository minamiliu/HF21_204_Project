//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: collision.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/02
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "collison.h"

//============================================
//静的メンバ変数の初期化
//============================================


//============================================
// マクロ定義
//============================================


//============================================
// 構造体定義
//============================================


//============================================
//コンストラクタ
//============================================
CCollision::CCollision()
{

}

//============================================
//デストラクタ
//============================================
CCollision::~CCollision()
{
	
}
//=============================================================================
// 内積
//=============================================================================
float CCollision::DotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	
	float ans = (vl.x * vr.x) + (vl.y * vr.y) + (vl.z * vr.z);

	return ans;
}


//=============================================================================
// 外積
//=============================================================================
D3DXVECTOR3 CCollision::CrossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr )
{
	D3DXVECTOR3 ret;

	ret.x = (vl.y * vr.z) - (vl.z*vr.y);
	ret.y = (vl.z * vr.x) - (vl.x*vr.z);
	ret.z = (vl.x * vr.y) - (vl.y*vr.x);

	return ret;
}



//=============================================================================
// ポリゴンと線分との当たり判定
// p0  :ポリゴンの頂点1
// p1  :ポリゴンの頂点2
// p2  :ポリゴンの頂点3
// pos0:始点（移動前）
// pos1:終点（移動後）
// 
// 返り値：0は当たっていない  1:当たっている
//=============================================================================
bool CCollision::HitCheck(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 *hitPos)
{
	D3DXVECTOR3		nor;		// ポリゴンの法線

	{	// ポリゴンの外積をとって法線を求める
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;
		nor = CrossProduct( vec01, vec02);
		D3DXVec3Normalize( &nor, &nor);
	}

	{	// 平面と線分の内積とって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の内積とって衝突している可能性を調べる
		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;
		float a = DotProduct( vec1, nor);
		float b = DotProduct( vec2, nor);
		if( (a * b) > 0 ) return false;
	}

	{	// ポリゴンと線分の交点を求める
		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;
		float	d1 = fabs( DotProduct( nor, vec1));	// 内分比を求める為の点とポリゴンとの距離
		float	d2 = fabs( DotProduct( nor, vec2));	// 内分比を求める為の点とポリゴンとの距離
		float	a = d1 / (d1+d2);					// 内分比
		
		
		// pos0からpos1へのベクトル（移動ベクトル）
		D3DXVECTOR3 vec3 = pos1 -pos0; 

		// 交点
		D3DXVECTOR3 p3 = pos0 + vec3 * a;

		// 交点を渡す
		*hitPos = p3;

		{	// 求めた交点がポリゴンの中にあるか調べる
			
			// ポリゴンの各辺のベクトル
			D3DXVECTOR3 v1 = p1 - p0;
			D3DXVECTOR3 v2 = p2 - p1;
			D3DXVECTOR3 v3 = p0 - p2;

			// 各頂点と交点とのベクトル
			D3DXVECTOR3 v4 = p3 - p1;
			D3DXVECTOR3 v5 = p3 - p2;
			D3DXVECTOR3 v6 = p3 - p0;

			// 各辺との外積で法線を求める
			D3DXVECTOR3 n1 = CrossProduct( v1, v4);
			D3DXVECTOR3 n2 = CrossProduct( v2, v5);
			D3DXVECTOR3 n3 = CrossProduct( v3, v6);

			// それぞれのベクトルの向きを内積でチェック
			if( DotProduct( n1, n2) < -0.02f ) return false;
			if( DotProduct( n1, n3) < -0.02f ) return false;
		}
	}

	return true;
}


//=============================================================================
// 壁ずりベクトル
//
// out : 正規化壁ずりベクトル（戻り値）
// front : 進行ベクトル
// normal: 衝突点での法線ベクトル
//
//=============================================================================
D3DXVECTOR3* CCollision::GetWallScratchVector(D3DXVECTOR3 *out, D3DXVECTOR3 &front, D3DXVECTOR3 &normal)
{
    D3DXVECTOR3 tNormal;
    D3DXVec3Normalize(&tNormal, &normal);

	*out = (front - DotProduct( front, tNormal) * tNormal);
	return out;
}

//*****************************************************************************
// 丸の当たり判定
//*****************************************************************************
bool CCollision::HitCheckBall( D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2)
{
	//バウンディングスフィア
	if( (pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y) + (pos1.z - pos2.z)*(pos1.z - pos2.z) 
		< (radius1 + radius2)*(radius1 + radius2) )
	{
		return true;
	}	
		
	return false;
}
//*****************************************************************************
// 平面の円の当たり判定
//*****************************************************************************
bool CCollision::HitCheckCircleXZ( D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2)
{
	//バウンディングスフィア
	if( (pos1.x - pos2.x)*(pos1.x - pos2.x)  + (pos1.z - pos2.z)*(pos1.z - pos2.z) 
		< (radius1 + radius2)*(radius1 + radius2) )
	{
		return true;
	}	
		
	return false;
}
//*****************************************************************************
// ２点の向きベクトルを取得
//*****************************************************************************
D3DXVECTOR3 CCollision::GetRotationAngle( D3DXVECTOR3 myPos, D3DXVECTOR3 target, D3DXVECTOR3 myRot)
{
	// 方向角度
	D3DXVECTOR3 dir = target - myPos;
	// Y軸角度
	float yAngle = atan2( dir.x, dir.z );

	//180度以上差があれば+-360度して逆回し
	if( yAngle - myRot.y > D3DX_PI ) {
		yAngle -= D3DX_PI * 2.0f;
	} else if( myRot.y - yAngle > D3DX_PI ) {
		yAngle += D3DX_PI * 2.0f;
	}

	//Y軸角度修正
	if(yAngle > D3DX_PI)
	{
		yAngle = yAngle - D3DX_PI*2;
	}
	else if(yAngle < 0.0f - D3DX_PI)
	{
		yAngle = yAngle + D3DX_PI*2;
	}

	// X軸角度
	float zxLen = sqrt( dir.x * dir.x + dir.z * dir.z );
	float xAngle = atan2( dir.y, zxLen );

	return D3DXVECTOR3( -xAngle, yAngle, 0.0f); 
}

//*****************************************************************************
// 視野内の判定
//*****************************************************************************
bool CCollision::HitCheckViewArea( D3DXVECTOR3 myPos, D3DXVECTOR3 tarPos, D3DXVECTOR3 myRot, float myView)
{
	D3DXVECTOR3 rotAnlge = GetRotationAngle( myPos, tarPos, myRot); 
	float fDiff = rotAnlge.y - myRot.y;

	if( fDiff > D3DX_PI)
	{
		fDiff = D3DX_PI * 2 - fDiff;
	}
	else if( fDiff < 0.0f - D3DX_PI)
	{
		fDiff = D3DX_PI * 2 + fDiff;
	}

	if( fabs(fDiff) <= myView)
	{
		return true;
	}
	return false;
}

//*****************************************************************************
// ２点距離を取得
//*****************************************************************************
float CCollision::GetDistanceXZ( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	return sqrtf( (pos1.x - pos2.x)*(pos1.x - pos2.x)  + (pos1.z - pos2.z)*(pos1.z - pos2.z) );
}
