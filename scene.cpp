//============================================
//
// タイトル:	 未来創造展チーム204
// プログラム名: scene.cpp
// 作成者:		 HAL東京ゲーム学科　劉南宏
// 作成日:       2016/10/19
//
//============================================

//============================================
//インクルードファイル
//============================================
#include "main.h"
#include "scene.h"

//============================================
//静的メンバ変数の初期化
//============================================
CScene *CScene::m_apScene[MAX_SCENE] = {};
int CScene::m_nNumScene = 0;

CScene *CScene::m_apEffect[MAX_EFFECT] = {};
int CScene::m_nNumEffect = 0;

CScene *CScene::m_apChange[MAX_CHANGE] = {};
int CScene::m_nNumChange = 0;
//============================================
// マクロ定義
//============================================


//============================================
// 構造体定義
//============================================


//============================================
//コンストラクタ
//============================================
CScene::CScene()
{
	m_layer = LAYER_SCENE;
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] == NULL)
		{
			m_apScene[nCntScene] = this;
			m_nID = nCntScene;
			m_nNumScene++;
			break;
		}
	}
}

CScene::CScene(LAYER layer)
{
	m_layer = layer;
	switch(layer)
	{
	case LAYER_EFFECT:
		for(int nCntScene = 0; nCntScene < MAX_EFFECT; nCntScene++)
		{
			if(m_apEffect[nCntScene] == NULL)
			{
				m_apEffect[nCntScene] = this;
				m_nID = nCntScene;
				m_nNumEffect++;
				break;
			}
		}
		break;
	case LAYER_CHANGE:
		for(int nCntScene = 0; nCntScene < MAX_CHANGE; nCntScene++)
		{
			if(m_apChange[nCntScene] == NULL)
			{
				m_apChange[nCntScene] = this;
				m_nID = nCntScene;
				m_nNumChange++;
				break;
			}
		}
		break;
	}

}

//============================================
//デストラクタ
//============================================
CScene::~CScene()
{
	
}

//============================================
//全部のシーン更新
//============================================
void CScene::UpdateAll(void)
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Update();
		}
	}

	for(int nCntScene = 0; nCntScene < MAX_EFFECT; nCntScene++)
	{
		if(m_apEffect[nCntScene] != NULL)
		{
			m_apEffect[nCntScene]->Update();
		}
	}

	for(int nCntScene = 0; nCntScene < MAX_CHANGE; nCntScene++)
	{
		if(m_apChange[nCntScene] != NULL)
		{
			m_apChange[nCntScene]->Update();
		}
	}
}

//============================================
//全部のシーン描画
//============================================
void CScene::DrawAll(void)
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Draw();
		}
	}

	for(int nCntScene = 0; nCntScene < MAX_EFFECT; nCntScene++)
	{
		if(m_apEffect[nCntScene] != NULL)
		{
			m_apEffect[nCntScene]->Draw();
		}
	}	

	for(int nCntScene = 0; nCntScene < MAX_CHANGE; nCntScene++)
	{
		if(m_apChange[nCntScene] != NULL)
		{
			m_apChange[nCntScene]->Draw();
		}
	}
}

//============================================
//全部のシーン開放
//============================================
void CScene::ReleaseAll(void)
{
	for(int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Uninit();
			m_apScene[nCntScene] = NULL;
		}
	}

	for(int nCntScene = 0; nCntScene < MAX_EFFECT; nCntScene++)
	{
		if(m_apEffect[nCntScene] != NULL)
		{
			m_apEffect[nCntScene]->Uninit();
			m_apEffect[nCntScene] = NULL;
		}
	}

	for(int nCntScene = 0; nCntScene < MAX_CHANGE; nCntScene++)
	{
		if(m_apChange[nCntScene] != NULL)
		{
			m_apChange[nCntScene]->Uninit();
			m_apChange[nCntScene] = NULL;
		}
	}
}

//============================================
//自我開放
//============================================
void CScene::Release(void)
{
	switch(m_layer)
	{
	case LAYER_SCENE:
		if(m_apScene[m_nID] != NULL)
		{
			int nID = m_nID;
			delete m_apScene[nID];
			m_apScene[nID] = NULL;
			m_nNumScene--;
		}
		break;
	case LAYER_EFFECT:
		if(m_apEffect[m_nID] != NULL)
		{
			int nID = m_nID;
			delete m_apEffect[nID];
			m_apEffect[nID] = NULL;
			m_nNumEffect--;
		}
		break;
	case LAYER_CHANGE:
		if(m_apChange[m_nID] != NULL)
		{
			int nID = m_nID;
			delete m_apChange[nID];
			m_apChange[nID] = NULL;
			m_nNumChange--;
		}
		break;
	}	
}
//============================================
//Sceneのポインターを取得
//============================================
CScene *CScene::GetScene(int nIdxScene)
{
	return m_apScene[nIdxScene];
}
//============================================
//タイプを設定
//============================================
void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}
//============================================
//タイプを取得
//============================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

