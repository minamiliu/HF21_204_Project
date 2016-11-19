//============================================
//
// タイトル:	 未来創造展チーム204
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
class CCamera;

//============================================
//構造体定義
//============================================

class CManager
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_LOADING, // ローディング
		TYPE_LOGO, // ロゴ表示
		TYPE_TITLE, // タイトル
		TYPE_MANUAL, //マニュアル
		TYPE_SELECT, // セレクト
		TYPE_GAME, // ゲーム
		TYPE_ENDING, // エンディング
		TYPE_STAFFROLL, // スタッフロール
		TYPE_RESULT, // リザルト
		TYPE_QUIT, // 終了
		TYPE_MAX,	//最大値
	} TYPE;

	CManager();
	CManager(TYPE type);
	virtual ~CManager();
	
	virtual HRESULT InitProgram(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	virtual HRESULT Init(void);
	virtual void UninitProgram(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//レンダラー
	static CRenderer *GetRenderer(void);

	//入力処理
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

	//カメラ
	static CCamera *GetCamera(void);

	//画面遷移
	static CManager *SetScene(TYPE type);
	static void CheckScene( CManager **ppManager);

protected:
	//カメラ
	static CCamera *m_pCamera;

private:
	//レンダラー
	static CRenderer *m_pRenderer;

	//入力処理
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;

	//画面遷移
	static CManager *m_pSceneManager;
	static TYPE m_type;
};

#endif
