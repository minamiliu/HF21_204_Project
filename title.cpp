//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: title.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "scene2D.h"

#include "zebra.h"
#include "gorira.h"
#include "lion.h"
//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/�T�o���i�^�C�g���p/�w�i/titleBg.png"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================


//============================================
//�R���X�g���N�^
//============================================
CTitle::CTitle() : CManager(MODE_TITLE)
{
	
}

CTitle::~CTitle()
{
	
}

HRESULT CTitle::Init(void)
{

	//�I�u�W�F�N�g�̐���(2D�|���S��)
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	//
	CZebra::Create(D3DXVECTOR3( SCREEN_WIDTH + 600, SCREEN_HEIGHT-250, 0.0f), D3DXVECTOR3(300, 200, 0.0f));
	CGorira::Create(D3DXVECTOR3( SCREEN_WIDTH + 300, SCREEN_HEIGHT-230, 0.0f), D3DXVECTOR3(160, 140, 0.0f));
	CLion::Create(D3DXVECTOR3( SCREEN_WIDTH + 900, SCREEN_HEIGHT-225, 0.0f), D3DXVECTOR3(230, 220, 0.0f));

	return S_OK;
}

void CTitle::Uninit()
{
	CManager::Uninit();
}

void CTitle::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();

	//CZebra::Update();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TRASHGAME);
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CTitle::Draw()
{
	CManager::Draw();
	//CZebra::Draw();
}
