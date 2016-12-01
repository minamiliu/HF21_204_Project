//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene.h
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/21
//
//============================================

#ifndef _SCENE_H_
#define _SCENE_H_

//============================================
//マクロ定義
//============================================
#define MAX_SCENE	(100)

//============================================
//構造体定義
//============================================

class CScene
{
public:
	typedef enum
	{
		OBJTYPE_TRASH = 0,
		OBJTYPE_MAX
	}OBJTYPE;
	CScene();
	virtual ~CScene();

	virtual HRESULT Init(void){ return S_OK;};
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);


	OBJTYPE GetObjType(void);
	void SetObjType(OBJTYPE type);
	static CScene *GetScene(int nIdxScene);
	virtual D3DXVECTOR3 GetPosition(void) = 0;
	virtual D3DXVECTOR3 GetSize(void) = 0;
protected:
	
	void Release(void);

private:

	static CScene *m_apScene[MAX_SCENE];
	static int m_nNumScene;
	int m_nID;
	OBJTYPE m_objType;
};

#endif