//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: game.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _GAME_H_
#define _GAME_H_

//============================================
//インクルードファイル
//============================================
#include "manager.h"

//============================================
//マクロ定義
//============================================
#define MAX_WALL (5)
#define MAX_CUBE (10)
//============================================
//前方宣言
//============================================
class CPlayerX;
class CMeshWall;
class CCubeX;
//============================================
//構造体定義
//============================================

class CGame : public CManager
{
public:

	CGame();
	virtual ~CGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPlayerX *m_player;
	CMeshWall *m_pMeshWall[MAX_WALL];
	int m_nNumWall;

	CCubeX *m_cube[MAX_CUBE];
	int m_nNumCube;
};

#endif
