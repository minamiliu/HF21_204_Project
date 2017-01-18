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
#define TEXTURE_TOMATO	"data/TEXTURE/LionGame/tomato.png"
#define TEXTURE_CARROT  "data/TEXTURE/LionGame/carrot.png"
#define TEXTURE_BANANA	"data/TEXTURE/LionGame/banana.png"
#define TEXTURE_MILK	"data/TEXTURE/LionGame/milk.png"
#define TEXTURE_CABBAGE	"data/TEXTURE/LionGame/cabbage.png"
#define TEXTURE_CURRY	"data/TEXTURE/LionGame/curry.png"
#define TEXTURE_EGG		"data/TEXTURE/LionGame/egg.png"
#define TEXTURE_ONION	"data/TEXTURE/LionGame/onion.png"
#define TEXTURE_POTATO	"data/TEXTURE/LionGame/potato.png"
#define TEXTURE_MEAT	"data/TEXTURE/LionGame/meat.png"


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

	//�������
	m_type = type;
	bClear[type] = false;
	m_state = STATE_NORMAL;
	m_nCntState = 0;
	m_posInit = pos;
	m_fAngle = 0.0f;
	m_fTurn = 0.0f;
	m_fMoveY = 0.0f;

	//�A�C�R��
	m_pIcon = CFoodIcon::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), m_pTexture[type], (int)type);

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
	//��ԍX�V
	switch( m_state)
	{
	case STATE_NORMAL:

		break;
	case STATE_FLYING:
		m_nCntState--;
		if( m_nCntState <= 0)
		{			
			//�H�ނ̔j��
			this->Uninit();
			return;
		}
		else
		{
			//���W
			D3DXVECTOR3 pos = this->GetPosition();
			m_fMoveY += 0.1f;
			pos.y += m_fMoveY;
			
			//��]
			m_fAngle += 0.01f;
			m_fTurn += m_fAngle; 
			pos.x = m_posInit.x + 30.0f * sinf( m_fTurn); 
			pos.z = m_posInit.z + 30.0f * cosf( m_fTurn);

			this->SetPosition(pos);
		}
		break;
	}	
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

		case TYPE_CARROT:
			strFileName = TEXTURE_CARROT;
			break;

		case TYPE_BANANA:
			strFileName = TEXTURE_BANANA;
			break;

		case TYPE_MILK:
			strFileName = TEXTURE_MILK;
			break;

		case TYPE_CABBAGE:
			strFileName = TEXTURE_CABBAGE;
			break;

		case TYPE_CURRY:
			strFileName = TEXTURE_CURRY;
			break;

		case TYPE_EGG:
			strFileName = TEXTURE_EGG;
			break;

		case TYPE_ONION:
			strFileName = TEXTURE_ONION;
			break;

		case TYPE_POTATO:
			strFileName = TEXTURE_POTATO;
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
//=============================================================================
// �X�e�[�g��ݒ�
//=============================================================================
void CFood::SetState(STATE state, int nCntState)
{
	m_state = state;
	m_nCntState = nCntState;
}
//=============================================================================
// �X�e�[�g���擾
//=============================================================================
CFood::STATE CFood::GetState(void)
{
	return m_state;
}