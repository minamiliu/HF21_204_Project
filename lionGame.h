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
#define MAX_CUBE (20)
//============================================
//前方宣言
//============================================
class CPlayerX;
class CMeshWall;
class CCubeX;
class CScore;
class CTime;
//============================================
//構造体定義
//============================================

class CLionGame : public CManager
{
public:
	typedef enum 
	{
		STATE_NORMAL = 0,
		STATE_SUPER,
		STATE_MAX,
	}STATE;

	CLionGame();
	virtual ~CLionGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//スコア
	static CScore *GetScore(void);

private:

	CTime *m_pTime;
	STATE m_state;
	//static CScore *m_score;
};

#endif
