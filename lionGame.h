//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: lionGame.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _LIONGAME_H_
#define _LIONGAME_H_

//============================================
//インクルードファイル
//============================================
#include "manager.h"

//============================================
//マクロ定義
//============================================
#define MAX_WALL (5)
#define MAX_CUBE (100)
//============================================
//前方宣言
//============================================
class CPlayerX;
class CMeshWall;
class CCubeX;
class CScore;
class CTime;
class CEffectBG;
class CChange;
class CScene2D;
class CSound;
//============================================
//構造体定義
//============================================

class CLionGame : public CManager
{
public:
	typedef enum 
	{
		STATE_NORMAL = 0,
		STATE_UPGRADE,
		STATE_LION,
		STATE_BONUS,
		STATE_FINISH,
		STATE_MAX,
	}STATE;

	CLionGame();
	virtual ~CLionGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//静的
	static CScore *GetScore(void);
	static CPlayerX *GetPlayer(void);
	static HRESULT LoadAll(void);
protected:
	void CreateStageLiu(void);
	void CreateStageUsukura(void);
	void CalcBonus(void);
private:

	STATE m_state;
	int m_nCntState;	//状態のカウンター

	CChange *m_pChange; //変身
	CTime *m_pTime;
	static CPlayerX *m_pPlayer;
	static CScore *m_pScore;

	int m_nGameCnt;
	CScene2D *m_pTextureMlt;
	CScore *m_pTextureHd;

	CSound *m_pSound;
};

#endif
