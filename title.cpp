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


//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/titleBG.jpg"

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

	return S_OK;
}

void CTitle::Uninit()
{
	CManager::Uninit();
}

void CTitle::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_GAME);
	}
}
void CTitle::Draw()
{
	CManager::Draw();
}
