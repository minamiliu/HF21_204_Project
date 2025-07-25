//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: playerX.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/15
//
//============================================

#ifndef _BOOK_H_
#define _BOOK_H_

//============================================
//インクルードファイル
//============================================
#include "sceneX.h"

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CBook : public CSceneX
{
public:

	CBook();
	virtual ~CBook();
	typedef enum
	{
			TYPE_RED,
			TYPE_GREEN,
			TYPE_BLUE,
			TYPE_YELLOW,
			BOOKTYPE_MAX
	}BOOKTYPE;
	#define MAX_BOOKTYPE (BOOKTYPE_MAX)
	#define MAX_BOOK (15)
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBook *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	static HRESULT Load(void);
	void CBook::BindXfile( int type);

	void CBook::ChangePicked(bool pick, bool zebra);
	void GetBoxpos(void);

	static int m_nNumber;
private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[MAX_BOOKTYPE];		// テクスチャへのポインタ
	static LPD3DXMESH			m_pD3DXMesh		[MAX_BOOKTYPE];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pD3DXBuffMat	[MAX_BOOKTYPE];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat		[MAX_BOOKTYPE];		// マテリアル情報の数
	bool m_bPicked;
	bool m_bZebra;
	bool m_bBack;
	int m_nID;
	
	D3DXVECTOR3 m_Move;
	float m_gravity;
	int m_Timecnt;
	D3DXVECTOR3 m_oldpos;
	
	static D3DXVECTOR3 Toyboxpos;
	static D3DXVECTOR3 Bookboxpos;

};

#endif
