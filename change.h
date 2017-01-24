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
	typedef enum 
	{
		MODE_GORILLA = 0,
		MODE_ZEBRA,
		MODE_LION,
		MODE_MAX,
	}MODE;

	typedef enum 
	{
		TYPE_PLAYER = 0,
		TYPE_G_ANIMAL,
		TYPE_G_SUPER,
		TYPE_Z_ANIMAL,
		TYPE_Z_SUPER,
		TYPE_L_ANIMAL,
		TYPE_L_SUPER,
		TYPE_MAX,
	}TYPE;

	CChange();
	virtual ~CChange();

	HRESULT Init( MODE mode);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CChange *Create( MODE mode);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	static bool GetState(void);
	static void changeState(void);
	static HRESULT Load(void);
	static void Unload(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];

	static CScene2D *m_pChamgeBg;
	static int changeCnt;
	static bool m_bState;
	static bool m_bAnimalPlayerFlag;
	MODE m_mode;
};

#endif
