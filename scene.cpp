//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "scene.h"

//============================================
//�ÓI�����o�ϐ��̏�����
//============================================
CScene *CScene::m_apScene[MAX_SCENE] = {};
int CScene::m_nNumScene = 0;

CScene *CScene::m_apEffect[MAX_EFFECT] = {};
int CScene::m_nNumEffect = 0;

CScene *CScene::m_apChange[MAX_CHANGE] = {};
int CScene::m_nNumChange = 0;
//============================================
// �}�N����`
//============================================


//============================================
// �\���̒�`
//============================================


//============================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//============================================
CScene::~CScene()
{
	
}

//============================================
//�S���̃V�[���X�V
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
//�S���̃V�[���`��
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
//�S���̃V�[���J��
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
//����J��
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
//Scene�̃|�C���^�[���擾
//============================================
CScene *CScene::GetScene(int nIdxScene)
{
	return m_apScene[nIdxScene];
}
//============================================
//�^�C�v��ݒ�
//============================================
void CScene::SetObjType(OBJTYPE type)
{
	m_objType = type;
}
//============================================
//�^�C�v���擾
//============================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

