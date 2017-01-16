//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: result.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "scene2D.h"
#include "effectBG.h"


//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/resultBG.jpg"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================


//============================================
//�R���X�g���N�^
//============================================
CResult::CResult() : CManager(MODE_RESULT)
{

}

CResult::~CResult()
{
	
}

HRESULT CResult::Init(void)
{
	//�I�u�W�F�N�g�̐���(2D�|���S��)
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	//CEffectBG::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	return S_OK;
}

void CResult::Uninit()
{
	CManager::Uninit();
}

void CResult::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TITLE);
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CResult::Draw()
{
	CManager::Draw();
}
