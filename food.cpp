//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: food.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "food.h"
#include "foodIcon.h"

//============================================
// �}�N����`
//============================================
#define TEXTURE_TOMATO	"data/TEXTURE/tomato.png"
#define TEXTURE_CABBAGE "data/TEXTURE/cabbage.png"
#define TEXTURE_MEAT	"data/TEXTURE/meat.png"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CFood::m_pTexture[TYPE_MAX] = {};
bool CFood::bClear[TYPE_MAX] = {false};
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFood::CFood()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFood::~CFood()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CFood::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type)
{
	CBillBoard::Init( pos, size);
	SetObjType(OBJTYPE_L_FOOD);

	m_type = type;
	bClear[type] = false;

	//�A�C�R��
	m_pIcon = CFoodIcon::Create(D3DXVECTOR3( 50.0f + type * 100.0f, 50.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), m_pTexture[type]);

	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CFood::Uninit(void)
{
	CBillBoard::Uninit();
}
//=============================================================================
//
//=============================================================================
void CFood::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CFood::Draw(void)
{
	CBillBoard::Draw();
}
//=============================================================================
//
//=============================================================================
CFood *CFood::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type)
{
	CFood *pFood;
	pFood = new CFood;

	pFood->Init(pos, size, type);

	//�e�N�X�`���̊��蓖��
	pFood->BindTexture( m_pTexture[type]);

	return pFood;
}
//=============================================================================
//�e�N�X�`���̃��[�h
//=============================================================================
HRESULT CFood::Load(void)
{
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch (cntType)
		{
		case TYPE_TOMATO:
			strFileName = TEXTURE_TOMATO;
			break;

		case TYPE_CABBAGE:
			strFileName = TEXTURE_CABBAGE;
			break;

		case TYPE_MEAT:
			strFileName = TEXTURE_MEAT;
			break;
		}

		if (m_pTexture[cntType] == NULL)
		{
			LPDIRECT3DDEVICE9 pDevice;
			pDevice = CManager::GetRenderer()->GetDevice();

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, strFileName, &m_pTexture[cntType]);
		}
	}

	return S_OK;
}

//=============================================================================
//�e�N�X�`���̃A�����[�h
//=============================================================================
void CFood::Unload(void)
{
	//�e�N�X�`���̔j��
	for (int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if (m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
	}
}

//=============================================================================
//�A�C�R���̎擾
//=============================================================================
CFoodIcon* CFood::GetIcon(void)
{
	return m_pIcon;
}

//=============================================================================
//�H�ނ��Q�b�g
//=============================================================================
void CFood::SetClear(void)
{
	bClear[m_type] = true;
}

//=============================================================================
//�H�ނ�S���Q�b�g������
//=============================================================================
bool CFood::isAllClear(void)
{
	//check
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		if( bClear[cntType] == false)
		{
			return false;
		}
	}
	return true;
}