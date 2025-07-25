//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: fade.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/19
//
//============================================

#ifndef _FADE_H_
#define _FADE_H_

//============================================
//インクルードファイル
//============================================

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_CHANGE,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade();
	virtual ~CFade();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

	static void SetFade(void);
	static bool isFading(void);
	
private:
	//関数
	static void SetAlpha(int alpha);

	//変数
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	static int m_nAlpha;
	static FADE m_state;
};

#endif
