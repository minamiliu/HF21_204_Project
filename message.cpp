//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "message.h"

//============================================
// �}�N����`
//============================================

#define TEXTURE_START "data/TEXTURE/start.png"


#define TEXTURE_FINISH "data/TEXTURE/finish.png"
//============================================

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMessage::CMessage()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMessage::~CMessage()
{
	
}

//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CMessage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{

	CScene2D::Init(pos, size);
	SetObjType( OBJTYPE_L_ITEM);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CMessage::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CMessage::Update(void)
{
	CScene2D::Update();
	D3DXVECTOR3 pos;
	pos = GetPosition();
	pos.x-=8;
	SetPosition(pos);
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CMessage::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CMessage *CMessage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName)
{
	CMessage *pMessage;
	pMessage = new CMessage;
	pMessage->Init(pos, size);
	//�e�N�X�`���̓ǂݍ���
	pMessage->CScene2D::Load( strFileName);
	return pMessage;
}
