//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: player2D.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _CHANGE_H_
#define _CHANGE_H_

//============================================
//インクルードファイル
//============================================
#include "scene.h"
#include "scene2D.h"
//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CChange : public CScene
{
public:
	CChange();
	virtual ~CChange();

	HRESULT Init( LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CChange *Create( LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	static bool GetState(void);
	static void changeState(void);
private:
	static CScene2D *m_pChamgeBg;
	static int changeCnt;
	static bool m_bState;
	static bool m_bAnimalPlayerFlag;
};

#endif
