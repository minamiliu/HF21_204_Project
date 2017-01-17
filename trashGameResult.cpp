//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: trashGameResult.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@�R�ƌ[��
// �쐬��:       2016/12/13
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "score.h"
#include "trashGameResult.h"
#include "scene2D.h"
//============================================
// �}�N����`
//============================================
#define TEXTURE_BGPOLYGON "data/TEXTURE/rendering003-16.png"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CScore *CTrashGameResult::m_pScore;
int CTrashGameResult::m_nTrashGameResultCnt = 0;
//============================================
//�R���X�g���N�^
//============================================
CTrashGameResult::CTrashGameResult() : CManager(MODE_TRASHGAMERESULT)
{
	m_nTrashGameResultCnt = 0;
}

CTrashGameResult::~CTrashGameResult()
{
	
}

HRESULT CTrashGameResult::Init(void)
{ 
	//m_pCamera->Init();
	
	//�I�u�W�F�N�g�̐���(3D�|���S��)
	//CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//�I�u�W�F�N�g�̐���(Xfile)
	//CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);

	//�w�i
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f),TEXTURE_BGPOLYGON);
	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(640, 360.0f, 0.0f), D3DXVECTOR3(600.0f, 100.0f, 0.0f), 6, RED(1.0f));
	return S_OK;
}

void CTrashGameResult::Uninit()
{
	CManager::Uninit();
}

void CTrashGameResult::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_ZEBRAGAME);
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}

void CTrashGameResult::Draw()
{
	CManager::Draw();
}


int CTrashGameResult::GetTrashGameResultCnt(void)
{
	return m_nTrashGameResultCnt;
}