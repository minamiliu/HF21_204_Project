//============================================
//
// タイトル:	 CL25課題
// プログラム名: renderer.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

#ifndef _RENDERER_H_
#define _RENDERER_H_

//============================================
//マクロ定義
//============================================

//============================================
//構造体定義
//============================================

class CRenderer
{
public:

	CRenderer();
	virtual ~CRenderer();

	LPDIRECT3DDEVICE9 GetDevice();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
};

#endif