/*******************************************************************************
* タイトル:		stagePlayer
* プログラム名:	stagePlayer.h
* 作成者:		小林玲雄
* 作成日:		2016/12/03
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#ifndef _STAGEPLAYER_H_
#define _STAGEPLAYER_H_
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
class CStagePlayer : public CScene2D
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_MOVE,
		STATE_MAX
	}STAGE_PLAYER_STATE;

	CStagePlayer();
	~CStagePlayer();
	static CStagePlayer* Create(D3DXVECTOR3 pos,D3DXVECTOR3 nextPos,D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_time;
	int m_animPat;
	int m_animCnt;
	int m_work;
	static D3DXVECTOR3 m_startPos;
	static D3DXVECTOR3 m_nextPos;
	static STAGE_PLAYER_STATE m_state;
	static STAGE_PLAYER_STATE m_oldState;
};
#endif