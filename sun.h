/*******************************************************************************
* タイトル:		sun
* プログラム名:	sun.h
* 作成者:		小林玲雄
* 作成日:		2016/12/03
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#ifndef _SUN_H_
#define _SUN_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "scene2D.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
/*******************************************************************************
* クラス定義
*******************************************************************************/
//クラス宣言
class CSun : public CScene2D
{
public:

	CSun();
	~CSun();
	//static CSun* Create(D3DXVECTOR3 pos,D3DXVECTOR3 nextPos,D3DXVECTOR3 size,bool move);
	//HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size);
	static CSun* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,float fRot);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size,float fRot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_time;
	int m_animPat;
	int m_animCnt;
	static bool m_bMove;
	float m_fRot;
	static D3DXVECTOR3 center;
};
#endif