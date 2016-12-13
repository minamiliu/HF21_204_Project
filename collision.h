//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: collison.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/02
//
//============================================

#ifndef _COLLISION_H_
#define _COLLISION_H_

//============================================
//マクロ定義
//============================================


//============================================
//構造体定義
//============================================

class CCollision
{
public:
	CCollision();
	virtual ~CCollision();

	// ポリゴンと線分との当たり判定
	static bool HitCheck(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 *hitPos);

	// 壁ずりベクトル
	static D3DXVECTOR3* GetWallScratchVector(D3DXVECTOR3 *out, D3DXVECTOR3 &front, D3DXVECTOR3 &normal);

	// 丸の当たり判定
	static bool HitCheckBall( D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2);

	// 平面の円の当たり判定
	static bool HitCheckCircleXZ( D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2);

	// ２点の向きベクトルを取得
	static D3DXVECTOR3 GetRotationAngle( D3DXVECTOR3 myPos, D3DXVECTOR3 target, D3DXVECTOR3 myRot);

	// 視野内の判定
	static bool HitCheckViewArea( D3DXVECTOR3 myPos, D3DXVECTOR3 tarPos, D3DXVECTOR3 myRot, float myView);

	// ２点距離を取得
	static float GetDistance( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);

	//2Dバウンドボックスの当たり判定
	static bool HitCheck2D( D3DXVECTOR3 pos1,  D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2);

	//2Dスフィア の当たり判定
	static bool HitCheck2D( D3DXVECTOR3 pos1,  float radius1, D3DXVECTOR3 pos2, float radius2);

	// 内積
	static float DotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr);

	// 外積
	static D3DXVECTOR3 CrossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr );

private:

};

#endif