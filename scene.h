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
#define MAX_CHANGE	(10)
#define MAX_EFFECT	(500)

//============================================
//構造体定義
//============================================

class CScene
{
public:
	typedef enum
	{
		OBJTYPE_TRASH = 0,
		OBJTYPE_L_ITEM,
		OBJTYPE_L_ENEMY,
		OBJTYPE_L_FOOD,
		OBJTYPE_WALL,
		OBJTYPE_CUBE,
		OBJTYPE_LEFTTRASH,
		OBJTYPE_RIGHTTRASH,
		OBJTYPE_POINT2D,//マウスの位置
		OBJTYPE_PLAYER,
		OBJTYPE_TRASHGAME,
		OBJTYPE_TOY,
		OBJTYPE_BOOK,
		OBJTYPE_POINT,
		OBJTYPE_TOYBOX,
		OBJTYPE_BOOKBOX,
		OBJTYPE_MAX
	}OBJTYPE;

	typedef enum
	{
		LAYER_SCENE = 0,
		LAYER_EFFECT,
		LAYER_CHANGE,
		LAYER_MAX
	}LAYER;

	CScene();
	CScene(LAYER layer);
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
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
protected:
	
	void Release(void);

private:
	int m_nID;
	OBJTYPE m_objType;
	LAYER m_layer;

	static CScene *m_apScene[MAX_SCENE];
	static int m_nNumScene;

	static CScene *m_apEffect[MAX_EFFECT];
	static int m_nNumEffect;

	static CScene *m_apChange[MAX_CHANGE];
	static int m_nNumChange;
};

#endif