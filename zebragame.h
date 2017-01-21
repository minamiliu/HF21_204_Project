//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: game.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/17
//
//============================================

#ifndef _ZEBRAGAME_H_
#define _ZEBRAGAME_H_

//============================================
//インクルードファイル
//============================================
#include "manager.h"

//============================================
//マクロ定義
//============================================
#define MAX_WALL (5)
//============================================
//前方宣言
//============================================
class CZebra;
class CZebraBox;
class CScene2D;
class CMeshWall;
class CPoint3D;
class CScore;
//============================================
//構造体定義
//============================================

class CZebraGame : public CManager
{
public:

	CZebraGame();
	virtual ~CZebraGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetZebraPointer(CScene2D *pZebra);
	static void PutObj(bool toy);
	static HRESULT LoadAll(void);
	static CScore *GetScore(void);

private:
	static CScene2D *m_pZebra;
	CScene2D *m_pZebraBox;
	static CPoint3D *m_pPoint3D;
	static int m_PutToy;
	static int m_PutBook;
	CMeshWall *m_pMeshWall[MAX_WALL];
	int m_nNumWall;
	static CScore *m_pScore;
};

#endif
