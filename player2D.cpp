//============================================
//
// �^�C�g��:	 CL25�ۑ�
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
#include "input.h"
#include "player2D.h"
#include "bullet2D.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayer2D::CPlayer2D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayer2D::~CPlayer2D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CPlayer2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPlayer2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPlayer2D::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 pos = CPlayer2D::GetPosition();

	//�ړ�
	if(pInputKeyboard->GetKeyPress(DIK_W))
	{
		pos.y -= 5.0f;
		CPlayer2D::SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_S))
	{
		pos.y += 5.0f;
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_A))
	{
		pos.x -= 5.0f;
		SetPosition(pos);
	}
	if(pInputKeyboard->GetKeyPress(DIK_D))
	{
		pos.x += 5.0f;
		SetPosition(pos);
	}
	
	int mouseMoveX = pInputMouse->GetMouseAxisX();
	if( mouseMoveX != 0)
	{
		pos.x += mouseMoveX;
		SetPosition(pos);
	}


	//�U��
	if(pInputKeyboard->GetKeyTrigger(DIK_SPACE))
	{
		CBullet2D::Create(pos, D3DXVECTOR3( 20.0f, 20.0f, 0.0f));
	}
	if(pInputMouse->GetMouseLeftTrigger())
	{
		CBullet2D::Create(pos, D3DXVECTOR3( 20.0f, 20.0f, 0.0f));
	}

	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPlayer2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CPlayer2D *CPlayer2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer2D *pPlayer2D;
	pPlayer2D = new CPlayer2D;
	pPlayer2D->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pPlayer2D->Load( TEXTURENAME);
	
	return pPlayer2D;
}

