//============================================
//
// タイトル:	 CL25課題
// プログラム名: manager.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/11/01
//
//============================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

//============================================
//マクロ定義
//============================================

//============================================
//前方宣言
//============================================
class CRenderer;
class CInputKeyboard;
class CInputMouse;

//============================================
//構造体定義
//============================================

class CManager
{
public:

	CManager();
	virtual ~CManager();
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	//レンダラー
	static CRenderer *GetRenderer(void);

	//入力処理
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

private:
	//レンダラー
	static CRenderer *m_pRenderer;

	//入力処理
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;

};

#endif
