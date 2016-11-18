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
CResult::CResult() : CManager(TYPE_RESULT)
{

}

CResult::~CResult()
{
	
}

HRESULT CResult::Init(void)
{
	//�I�u�W�F�N�g�̐���(2D�|���S��)
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	return S_OK;
}

void CResult::Uninit()
{
	CManager::Uninit();
}

void CResult::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetScene( TYPE_TITLE);
	}
}
void CResult::Draw()
{
	CManager::Draw();
}
