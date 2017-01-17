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
class CSound;

//============================================
//構造体定義
//============================================

class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_LOADING, // ローディング
		MODE_LOGO, // ロゴ表示
		MODE_TITLE, // タイトル
		MODE_MANUAL, //マニュアル
		MODE_SELECT, // セレクト
		MODE_LIONGAME, //ライオンゲーム
		MODE_ZEBRAGAME,//シマウマゲーム
		MODE_TRASHGAME,//ゴミ投げゲーム
		MODE_TRASHGAMERESULT,//ゴミ投げゲームのリザルト
		MODE_ENDING, // エンディング
		MODE_STAFFROLL, // スタッフロール
		MODE_RESULT, // リザルト
		MODE_QUIT, // 終了
		MODE_MAX,	//最大値
	} MODE;

	CManager();
	CManager(MODE mode);
	virtual ~CManager();
	
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CManager *Create( MODE type, HINSTANCE hInstance, HWND hWnd, bool bWindow);
	static void UpdateAll(void);
	static void DrawAll(void);
	static void Release(void);

	//レンダラー
	static CRenderer *GetRenderer(void);

	//入力処理
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

	//サウンド
	static CSound *GetSound(void);

	//カメラ
	static CCamera *GetCamera(void);

	//画面遷移
	static void NextModeChange(void); //フェードなし
	static void SetNextScene(MODE mode); //フェードあり
	static void SceneChange(void); //シーンの切り替え

	//スコア保存
	void SaveScore(MODE game,int score);
	int LoadScore(MODE game);

	//モデルやテクスチャを一気にロードする
	static HRESULT LoadAll(void);

protected:
	//カメラ
	static CCamera *m_pCamera;

private:
	//レンダラー
	static CRenderer *m_pRenderer;

	//入力処理
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;

	//サウンド
	static CSound *m_pSound;

	//画面遷移
	static CManager *m_pSceneManager;
	static MODE m_modeNow;
	static MODE m_modeNext;

	static HWND m_hWnd;

	//スコア保存
	static int m_trashGameScore;
	static int m_zebraGameScore;
	static int m_lionGameScore;
};

#endif
