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
#include "timeBg.h"
#include "sun.h"
//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/�X�e�[�W�p/bg.jpg"
#define TEXTURE_START "data/TEXTURE/�X�e�[�W�p/start.png"
#define TEXTURE_GOAL "data/TEXTURE/�X�e�[�W�p/goal.png"
#define TEXTURE_MASU "data/TEXTURE/�X�e�[�W�p/masu.png"

#define TEXTURE_GORIRA_MASU "data/TEXTURE/�X�e�[�W�p/gorira.png"
#define TEXTURE_ZEBRA_MASU "data/TEXTURE/�X�e�[�W�p/zebra.png"
#define TEXTURE_LION_MASU "data/TEXTURE/�X�e�[�W�p/lion.png"

#define TEXTURE_GOMIBOX "data/TEXTURE/�S�~��(�D�F).png"
#define TEXTURE_GOMI "data/TEXTURE/�S�~.png"
#define TEXTURE_ROAD1 "data/TEXTURE/�X�e�[�W�p/��1.png"
#define TEXTURE_ROAD2 "data/TEXTURE/�X�e�[�W�p/��2.png"
#define MASU_ROTATE	(0.8)
#define ROAD_ROTATE1	(55)
#define ROAD_ROTATE2	(55)
#define ROAD2_TYOUSEI	(-5)
#define PLAYER_POS_TYOUSEI (40)
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

//�e�}�X�̈ʒu
D3DXVECTOR3 CStage::pos[MASU_MAX] = 
{
	//W�̌`ver
	//D3DXVECTOR3( SCREEN_WIDTH*1/6, SCREEN_HEIGHT*3/4, 0.0f),//�X�^�[�g�ʒu
	//D3DXVECTOR3( SCREEN_WIDTH*2/6, SCREEN_HEIGHT*2/4, 0.0f),//�S�~�̂�
	//D3DXVECTOR3( SCREEN_WIDTH*3/6, SCREEN_HEIGHT*3/4, 0.0f),//�Еt��
	//D3DXVECTOR3( SCREEN_WIDTH*4/6, SCREEN_HEIGHT*2/4, 0.0f),//������
	//D3DXVECTOR3( SCREEN_WIDTH*5/6, SCREEN_HEIGHT*3/4, 0.0f)	//�S�[���ʒu

	//�|����Z�̌`ver
	D3DXVECTOR3( SCREEN_WIDTH*1/6, SCREEN_HEIGHT-100, 0.0f),//�X�^�[�g�ʒu
	D3DXVECTOR3( SCREEN_WIDTH*1/6+100, SCREEN_HEIGHT-300, 0.0f),//�S�~�̂�
	D3DXVECTOR3( SCREEN_WIDTH*3/6, SCREEN_HEIGHT-300, 0.0f),//�Еt��
	D3DXVECTOR3( SCREEN_WIDTH*5/6-100, SCREEN_HEIGHT-300, 0.0f),//������
	D3DXVECTOR3( SCREEN_WIDTH*5/6, SCREEN_HEIGHT-500, 0.0f)	//�S�[���ʒu

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



	switch(m_stageNow)
	{
	case MASU_START:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),3,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),3,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//�X�^�[�g�ʒu
					D3DXVECTOR3(90, 90, 0.0f),
					4.0);


		break;
	case MASU_GORIRA:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),0,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),0,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//�X�^�[�g�ʒu
					D3DXVECTOR3(90, 90, 0.0f),
					4.4);


		break;
	case MASU_ZEBRA:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),1,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),1,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//�X�^�[�g�ʒu
					D3DXVECTOR3(90, 90, 0.0f),
					4.8);

		break;
	case MASU_LION:
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),2,0);
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),2,1);

		CSun::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/6,0),//�X�^�[�g�ʒu
					D3DXVECTOR3(90, 90, 0.0f),
					5.2);

		break;
	}

	CStageBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	switch(m_stageNow)
	{
	case MASU_START:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),3,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),3,1);
		break;
	case MASU_GORIRA:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),0,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),0,1);
		break;
	case MASU_ZEBRA:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),1,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),1,1);
		break;
	case MASU_LION:
		//CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH/8, 0.0f),2,0);
		CTimeBg::Create(D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_WIDTH*6/16, 0.0f),D3DXVECTOR3(SCREEN_WIDTH, SCREEN_WIDTH*4/8, 0.0f),2,1);
		break;
	}


	//��
	CScene2D::Create(	D3DXVECTOR3(pos[MASU_START].x-(pos[MASU_START].x-pos[MASU_GORIRA].x)/2,pos[MASU_START].y-(pos[MASU_START].y-pos[MASU_GORIRA].y)/2,pos[MASU_START].z),
						D3DXVECTOR3(5*ROAD_ROTATE1, 5*ROAD_ROTATE1, 0.0f),
						TEXTURE_ROAD1);

	CScene2D::Create(	D3DXVECTOR3(pos[MASU_GORIRA].x-(pos[MASU_GORIRA].x-pos[MASU_ZEBRA].x)/2,pos[MASU_GORIRA].y-(pos[MASU_GORIRA].y-pos[MASU_ZEBRA].y)/2 - ROAD2_TYOUSEI,pos[MASU_GORIRA].z),
						D3DXVECTOR3(5*ROAD_ROTATE2, 5*ROAD_ROTATE2, 0.0f),
						TEXTURE_ROAD2);

	CScene2D::Create(	D3DXVECTOR3(pos[MASU_ZEBRA].x-(pos[MASU_ZEBRA].x-pos[MASU_LION].x)/2,pos[MASU_ZEBRA].y-(pos[MASU_ZEBRA].y-pos[MASU_LION].y)/2 - ROAD2_TYOUSEI,pos[MASU_ZEBRA].z),
						D3DXVECTOR3(5*ROAD_ROTATE2, 5*ROAD_ROTATE2, 0.0f),
						TEXTURE_ROAD2);

	CScene2D::Create(	D3DXVECTOR3(pos[MASU_LION].x-(pos[MASU_START].x-pos[MASU_GORIRA].x)/2,pos[MASU_LION].y-(pos[MASU_START].y-pos[MASU_GORIRA].y)/2 - ROAD2_TYOUSEI,pos[MASU_LION].z),
						D3DXVECTOR3(5*ROAD_ROTATE1, 5*ROAD_ROTATE1, 0.0f),
						TEXTURE_ROAD1);

	//�X�^�[�g
	CScene2D::Create( pos[MASU_START], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_START);

	//�S�~�̂ăQ�[��
	CScene2D::Create( pos[MASU_GORIRA], D3DXVECTOR3(300, 300, 0.0f) * MASU_ROTATE, TEXTURE_GORIRA_MASU);
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5, SCREEN_HEIGHT*2/4-120, 0.0f), D3DXVECTOR3(200, 120, 0.0f), TEXTURE_GOMIBOX);
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH*2/5-50, SCREEN_HEIGHT*2/4-170, 0.0f), D3DXVECTOR3(70, 50, 0.0f), TEXTURE_GOMI);

	//�Еt���Q�[��
	CScene2D::Create( pos[MASU_ZEBRA], D3DXVECTOR3(300, 300, 0.0f) * MASU_ROTATE, TEXTURE_ZEBRA_MASU);
	//�������Q�[��
	CScene2D::Create( pos[MASU_LION], D3DXVECTOR3(300, 300, 0.0f) * MASU_ROTATE, TEXTURE_LION_MASU);

	//�S�[��
	CScene2D::Create( pos[MASU_GOAL], D3DXVECTOR3(300, 120, 0.0f), TEXTURE_GOAL);
	switch(m_stageNow)
	{
	case MASU_START:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_START].x,pos[MASU_START].y-PLAYER_POS_TYOUSEI,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-PLAYER_POS_TYOUSEI,0),//�S�[���ʒu
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_GORIRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_GORIRA].x,pos[MASU_GORIRA].y-PLAYER_POS_TYOUSEI,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-PLAYER_POS_TYOUSEI,0),//�S�[���ʒu
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_ZEBRA:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_ZEBRA].x,pos[MASU_ZEBRA].y-PLAYER_POS_TYOUSEI,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_LION].x,pos[MASU_LION].y-PLAYER_POS_TYOUSEI,0),//�S�[���ʒu
							D3DXVECTOR3(100, 100, 0.0f)
						);
		break;
	case MASU_LION:
		CStagePlayer::Create(	D3DXVECTOR3(pos[MASU_LION].x,pos[MASU_LION].y-PLAYER_POS_TYOUSEI,0),//�X�^�[�g�ʒu
							D3DXVECTOR3(pos[MASU_GOAL].x,pos[MASU_GOAL].y-PLAYER_POS_TYOUSEI,0),//�S�[���ʒu
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
		case MASU_LION:
			SetNextScene( MODE_RESULT);
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
