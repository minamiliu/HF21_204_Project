//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: meshWall.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/12/06
//
//============================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//============================================
//インクルードファイル
//============================================
#include "scene3D.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CMeshWall : public CScene3D
{
public:

	CMeshWall();
	virtual ~CMeshWall();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	bool HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint);

private:

};

#endif
