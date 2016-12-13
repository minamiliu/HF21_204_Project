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
#include "zebragame.h"
#include "renderer.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"
#include "toy.h"
#include "point3D.h"
#include "score.h"
//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

CScore *CZebraGame::m_score  = NULL;
//============================================
//�R���X�g���N�^
//============================================
CZebraGame::CZebraGame() : CManager(MODE_GAME)
{

}

CZebraGame::~CZebraGame()
{
	
}

HRESULT CZebraGame::Init(void)
{
	m_pCamera->Init();

	//�I�u�W�F�N�g�̐���(3D�|���S��)
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);
	//�J�����̈ʒu
	//CCamera::SetPosV(D3DXVECTOR3(0.0f,-500.0f,200.0f));
	for(int nCnt = 0 ; nCnt < 10 ;nCnt++)
	{
		//�I�u�W�F�N�g�̐���(Xfile)
		CToy::Create( D3DXVECTOR3( 50.0f*nCnt-200.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	}
	//�I�u�W�F�N�g�̐���(2D�|���S��)
	m_score = CScore::Create( D3DXVECTOR3(150, 100.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f));
	m_score->SetScore(1000);
	//�I�u�W�F�N�g�̐���(2D�|���S��)
	CPoint3D::Create( D3DXVECTOR3( 300.0f, 500.0f, 0.0f), D3DXVECTOR3( 20.0f, 20.0f, 0.0f),0);
	return S_OK;
}

void CZebraGame::Uninit()
{
	CManager::Uninit();
}

void CZebraGame::Update()
{
	CManager::Update();

	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_RESULT);
	}
}
void CZebraGame::Draw()
{
	CManager::Draw();
}

CScore *CZebraGame::GetScoreP(void)
{
	return m_score;
}