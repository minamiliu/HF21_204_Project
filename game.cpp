//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: game.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"

//============================================
// �}�N����`
//============================================
#define CAMERA_DISTANCE	(200.0f)
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================


//============================================
//�R���X�g���N�^
//============================================
CGame::CGame() : CManager(MODE_GAME)
{

}

CGame::~CGame()
{
	
}

HRESULT CGame::Init(void)
{
	m_pCamera->Init();

	//�I�u�W�F�N�g�̐���(3D�|���S��)
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//�E�H�[��
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 500.0f), D3DXVECTOR3( D3DXToRadian(90.0f), 0.0f, 0.0f), 10, 1, 100.0f, 100.0f);
	CScene3D::Create( D3DXVECTOR3( 500.0f, 0.0f, 0.0f), D3DXVECTOR3( D3DXToRadian(90.0f), D3DXToRadian(90.0f), 0.0f), 10, 1, 100.0f, 100.0f);
	CScene3D::Create( D3DXVECTOR3( -500.0f, 0.0f, 0.0f), D3DXVECTOR3( D3DXToRadian(90.0f), D3DXToRadian(-90.0f), 0.0f), 10, 1, 100.0f, 100.0f);
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, -500.0f), D3DXVECTOR3( D3DXToRadian(90.0f), D3DXToRadian(180.0f), 0.0f), 10, 1, 100.0f, 100.0f);

	//�I�u�W�F�N�g�̐���(Xfile)
	m_player = CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 2.0f);

	//�I�u�W�F�N�g�̐���(2D�|���S��)

	return S_OK;
}

void CGame::Uninit()
{
	CManager::Uninit();
}

void CGame::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();

	{//�J�����Ǐ]
		CCamera *pCamera = GetCamera();

		//�����_
		pCamera->SetPosR( m_player->GetPosition());

		//���_
		D3DXVECTOR3 posV = pCamera->GetPosV();
		posV.x = pCamera->GetPosR().x - CAMERA_DISTANCE * sinf(pCamera->GetRot().y);
		posV.z = pCamera->GetPosR().z - CAMERA_DISTANCE * cosf(pCamera->GetRot().y);
		pCamera->SetPosV( posV);

		//����
		pCamera->SetRot( m_player->GetRot());
	}


	//�X�L�b�v�V�[��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TRASHGAME);
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CGame::Draw()
{
	CManager::Draw();
}
