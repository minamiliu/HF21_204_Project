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
#include "stage.h"
#include "stagePlayer.h"
#include "stageBg.h"
//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/�X�e�[�W�p/bg.jpg"
#define TEXTURE_START "data/TEXTURE/�X�e�[�W�p/start.png"
#define TEXTURE_MASU "data/TEXTURE/�X�e�[�W�p/masu.png"
#define TEXTURE_GOMIBOX "data/TEXTURE/�S�~��(�D�F).png"
#define TEXTURE_GOMI "data/TEXTURE/�S�~.png"
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

//�e�}�X�̈ʒu
D3DXVECTOR3 CStage::pos[MASU_MAX] = 
{
	D3DXVECTOR3( SCREEN_WIDTH*1/5, SCREEN_HEIGHT*3/4, 0.0f),//�X�^�[�g�ʒu
	D3DXVECTOR3( SCREEN_WIDTH*2/5, SCREEN_HEIGHT*2/4, 0.0f),//�S�~�̂�
	D3DXVECTOR3( SCREEN_WIDTH*3/5, SCREEN_HEIGHT*3/4, 0.0f),//�Еt��
	D3DXVECTOR3( SCREEN_WIDTH*4/5, SCREEN_HEIGHT*2/4, 0.0f)	//������
};

CStage::MASU_TYPE CStage::m_stageNow = MASU_START;
//============================================
//�R���X�g���N�^
//============================================
CStage::CStage()// : CManager(MODE_STAGE)
{
	
}
CStage::CStage(MASU_TYPE type)
{
	m_stageNow = type;
}

CStage::~CStage()
{
	
}

HRESULT CStage::Init(void)
{

	//�I�u�W�F�N�g�̐���(2D�|���S��)
	//�w�i
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);
	CStageBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//�X�^�[�g
	CScene2D::Create( pos[MASU_START], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_START);

	//�S�~�̂ăQ�[��
	CScene2D::Create( pos[MASU_GORIRA], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_MASU);

	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5, SCREEN_HEIGHT*2/4-120, 0.0f), D3DXVECTOR3(200, 120, 0.0f), TEXTURE_GOMIBOX);
	CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5-50, SCREEN_HEIGHT*2/4-170, 0.0f), D3DXVECTOR3(70, 50, 0.0f), TEXTURE_GOMI);
	//�Еt���Q�[��
	CScene2D::Create( pos[MASU_ZEBRA], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_MASU);
	//�������Q�[��
	CScene2D::Create( pos[MASU_LION], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_MASU);

	switch(m_stageNow)
	{
	case MASU_START:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_START].x,pos[MASU_START].y-50,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-50,0),//�S�[���ʒu
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_GORIRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-50,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-50,0),//�S�[���ʒu
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_ZEBRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-50,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_LION].x,pos[MASU_LION].y-50,0),//�S�[���ʒu
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	}
	return S_OK;
}

void CStage::Uninit()
{
	CManager::Uninit();
}

void CStage::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();


	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		switch(m_stageNow)
		{
		case MASU_START:
			SetNextScene( MODE_TRASHGAME);
			break;
		case MASU_GORIRA:
			SetNextScene( MODE_ZEBRAGAME);
			break;
		case MASU_ZEBRA:
			SetNextScene( MODE_LIONGAME);
			break;
		}
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CStage::Draw()
{
	CManager::Draw();
}
