//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: enemy.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/18
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
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
//LPDIRECT3DTEXTURE9 CFoodIcon::m_pTexture[CFoodIcon::TYPE_MAX] = {};


//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CFoodIcon::CFoodIcon()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CFoodIcon::~CFoodIcon()
{
	
}


//=============================================================================
// �H�ނ̏���������
//=============================================================================

HRESULT CFoodIcon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);

	//�D�F�ɂ���
	this->SetColor(BLACK(0.7f));

	return S_OK;
}




//=============================================================================
// �H�ނ̏I������
//=============================================================================
void CFoodIcon::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �H�ނ̍X�V����
//=============================================================================
void CFoodIcon::Update(void)
{

}

//=============================================================================
// �H�ނ̕`�揈��
//=============================================================================
void CFoodIcon::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �H�ނ̐�������
//=============================================================================
CFoodIcon *CFoodIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 pTexture)
{
	CFoodIcon *pFoodIcon;
	pFoodIcon = new CFoodIcon;
	pFoodIcon->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pFoodIcon->BindTexture( pTexture);
	
	return pFoodIcon;
}

////=============================================================================
////�e�N�X�`���̃��[�h
////=============================================================================
//HRESULT CFoodIcon::Load(void)
//{
//	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
//	{
//		LPCSTR strFileName;
//		switch( cntType)
//		{
//		case TYPE_TOMATO:
//			strFileName = TEXTURE_TOMATO;
//			break;
//
//		case TYPE_CABBAGE:
//			strFileName = TEXTURE_CABBAGE;
//			break;
//
//		case TYPE_MEAT:
//			strFileName = TEXTURE_MEAT;
//			break;
//
//		}
//
//		if( m_pTexture[cntType] == NULL)
//		{
//			LPDIRECT3DDEVICE9 pDevice;
//			pDevice = CManager::GetRenderer()->GetDevice();
//
//			// �e�N�X�`���̓ǂݍ���
//			D3DXCreateTextureFromFile( pDevice, strFileName, &m_pTexture[cntType]);
//		}	
//	}
//
//
//	return S_OK;
//}
//
////=============================================================================
////�e�N�X�`���̃A�����[�h
////=============================================================================
//void CFoodIcon::Unload(void)
//{
//	//�e�N�X�`���̔j��
//	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
//	{
//		if( m_pTexture[cntType] != NULL)
//		{
//			m_pTexture[cntType]->Release();
//			m_pTexture[cntType] = NULL;
//		}	
//	}
//}
////=============================================================================
////�H�ނ̎�ނ��擾
////=============================================================================
//CFoodIcon::TYPE CFoodIcon::GetType(void)
//{
//	return m_type;
//}
////=============================================================================
////�H�ޑS�̂̐���(�X�e�[�W0)
////=============================================================================
//void CFoodIcon::CreateAllFoodIcon(void)
//{
//	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
//	{
//		CFoodIcon::Create(D3DXVECTOR3( 50.0f + cntType * 100.0f, 50.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), (TYPE)cntType);
//	}
//}
