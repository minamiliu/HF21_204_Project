//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: trashGame.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@�R�ƌ[��
// �쐬��:       2016/11/24
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "trashGame.h"
#include "renderer.h"
#include "input.h"
#include "player2D.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "playerX.h"
#include "trash.h"
#include "score.h"
#include "trashBox.h"
#include "point2D.h"
#include "time.h"
#include "debugproc.h"
#include "trajectory.h"
#include "getScore.h"
#include "trashPlayer.h"
#include "trashGameExplosion.h"
#include "message.h"
#include "change.h"
//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
#define TEXTURE_POINT "data/TEXTURE/redPoint.png"
#define TEXTURE_TRASH "data/TEXTURE/�y�b�g�{�g��.png"
#define TEXTURE_TRASHBOX "data/TEXTURE/�S�~��(�D�F).png"
#define TEXTURE_GORILLA "data/TEXTURE/throwingGorilla.png"
#define TEXTURE_BGPOLYGON "data/TEXTURE/rendering003-16.png"
#define TEXTURE_PLAYER "data/TEXTURE/throwingMother.png"
#define TEXTURE_START "data/TEXTURE/start.png"
#define TEXTURE_FINISH "data/TEXTURE/finish.png"
#define GORILLA_GORILLA "data/TEXTURE/�S����.png"
#define STAND_GORILLA "data/TEXTURE/�S����(�����G).png"

#define TEXTURE_EXPLOSION "data/TEXTURE/explosion000.png"
#define	TEX_PATTERN_DIVIDE_X		(8)												// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
#define	TIME_CHANGE_PATTERN			(10)											// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CTrash *CTrashGame::m_pTrash = NULL;
CScene2D *CTrashGame::m_pTrashBox = NULL;
CScore   *CTrashGame::m_pScore = NULL;
//CPoint2D *m_pPoint2D = NULL;
CScene2D *CTrashGame::m_pMouse = NULL;
CScene2D *CTrashGame::m_pPoint2D = NULL;
CScene2D *CTrashGame::m_pMidpoint = NULL;
CScene2D *CTrashGame::m_pCenterPoint = NULL;
CTime *pTime = NULL;
CPlayer2D *pPlayer2D = NULL;
int CTrashGame::m_nTrashGameCnt = 0;
CTrashPlayer *pAnimPlayer = NULL;
CScene2D *pExplosion = NULL;

bool bMessageFlag = false;
//============================================
//�R���X�g���N�^
//============================================
CTrashGame::CTrashGame() : CManager(MODE_TRASHGAME)
{
	m_nTrashGameCnt = 0;
}

CTrashGame::~CTrashGame()
{
	
}

HRESULT CTrashGame::Init(void)
{ 
	m_pCamera->Init();
	//�Q�[���N�����̃}�E�X���ʒu������Ă��܂����߁A�����I�ɉ�ʒ�����
	SetCursorPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	//�X�R�A������
	SaveScore(MODE_TRASHGAME,0);
	//�e�N�X�`���̊��蓖��
	CTrash::Load();
	CTrajectory::Load();
	CTrashPlayer::Load();
	//�w�i
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH*1.2,SCREEN_HEIGHT*1.4,0.0f),TEXTURE_BGPOLYGON);
	//�I�u�W�F�N�g�̐���
	//�v���C���[
	pAnimPlayer = CTrashPlayer::Create( D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 300.0f, 300.0f, 0.0f),TEXTURE_PLAYER);
	//�S�~
	m_pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 400.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CScene::OBJTYPE_TRASH);
	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(150, 50.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f), 6, BLUE(1.0f));
	//�S�~��
	//m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), D3DXVECTOR3(800.0f, 600.0f, 0.0f),TEXTURE_TRASHBOX);
	m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1100.0f, 350.0f, 0.0f), D3DXVECTOR3(650.0f, 300.0f, 0.0f),TEXTURE_TRASHBOX);
	//�^�C��
	pTime = CTime::Create(D3DXVECTOR3(600, 50.0f, 0.0f),D3DXVECTOR3(100, 100.0f, 0.0f),3,12,true,D3DXCOLOR(255,255,255,255));
	pTime->StopTime();
	//�}�E�X�̈ʒu�𓾂�
	CPoint2D::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),0);
	//�˂ɒ�����
	m_pCenterPoint = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f),TEXTURE_POINT);
	//�����ƌ��݈ʒu�̒��ԂɃe�N�X�`��
	m_pMidpoint = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f),TEXTURE_POINT);
	//�}�E�X�̈ʒu�Ƀe�N�X�`��
	m_pMouse = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f),TEXTURE_POINT);

	pExplosion = NULL;
	bMessageFlag = false;
	return S_OK;
}

void CTrashGame::Uninit()
{
	CManager::Uninit();
}

void CTrashGame::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();

	m_nTrashGameCnt++;

	D3DXVECTOR3 posTrashBox;
	D3DXVECTOR3 sizeTrashBox;
	posTrashBox = m_pTrashBox->GetPosition();
	sizeTrashBox = m_pTrashBox->GetSize();
	
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//���~��
	if( pInputKeyboard->GetKeyTrigger(DIK_T))
	{
		pTime->StopTime();
	}


	//�}�E�X��b������J�[�\������ʒ�����
	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
		SetCursorPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	}

	for(int nCntScene = 0;nCntScene < MAX_SCENE;nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);
		if(pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();
			if(type == CScene::OBJTYPE_TRASH || type == CScene::OBJTYPE_LEFTTRASH || type == CScene::OBJTYPE_RIGHTTRASH)
			{
				D3DXVECTOR3 posTrash;
				D3DXVECTOR3 sizeTrash;
				posTrash = pScene->GetPosition();
				sizeTrash = pScene->GetSize();
				//�����蔻��
				if( (posTrash.y + sizeTrash.y/2 > posTrashBox.y - sizeTrashBox.y*0.8/2) &&
					(posTrash.y - sizeTrash.y/2 < posTrashBox.y + sizeTrashBox.y*0.8/2) &&
					(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrashBox.x*0.4/2) &&
					(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrashBox.x*0.4/2))
				{
					D3DXVECTOR3 speed;
					speed = ((CTrash*)pScene)->GetSpeed();
					if(speed.x > 0 &&
						//(posTrash.x - sizeTrash.x/2) < (posTrashBox.x - sizeTrashBox.x) //&&
						(posTrash.y - sizeTrash.y/2) > (posTrashBox.y - sizeTrashBox.y/2) )//||
						//(posTrash.x < (posTrashBox.x - sizeTrashBox.x/2)))
					{//�O���̉E�[�ł͂���
						((CTrash*)pScene)->ReverseMove();
						CTrajectory::Create(D3DXVECTOR3(posTrash.x,posTrash.y,100.0f),D3DXVECTOR3(100,100,0.0f),CTrajectory::TJRTYPE_NORMAL,0.0);
					}
					else
					{//���S�ɓ����Ă�
						//�ŏ��ɓ������Ƃ��Ɏ��Ԃ𓮂���
						if(LoadScore(MODE_TRASHGAME) == 0)
						{
							pTime->StopTime();
							CMessage::Create(D3DXVECTOR3(SCREEN_WIDTH + 100,100,0),D3DXVECTOR3(250,250,0),TEXTURE_START);
						}
						//�X�R�A�ǉ�
						if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_NORMAL)
						{
							m_pScore->AddScore(100);
							CGetScore *pGetScore = CGetScore::Create(posTrash,D3DXVECTOR3(100,100,0.0f),3,BLUE(1.0));
							pGetScore->AddScore(100);
							CManager::AddScore(CManager::MODE_TRASHGAME,100);
						}
						else if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_LIGHT)
						{
							m_pScore->AddScore(180);
							CGetScore *pGetScore = CGetScore::Create(posTrash,D3DXVECTOR3(140,140,0.0f),3,RED(1.0));
							pGetScore->AddScore(180);
							CManager::AddScore(CManager::MODE_TRASHGAME,180);
							for(int cnt=0;cnt<8;cnt++)
							{
								CTrajectory::Create(D3DXVECTOR3(posTrash.x,posTrash.y,100.0f),D3DXVECTOR3(100,100,0.0f),CTrajectory::TJRTYPE_ALLDIRECTION,2*3.14/8*cnt);
							}
						}
						else if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_HEAVY)
						{
							m_pScore->AddScore(150);
							CGetScore *pGetScore = CGetScore::Create(posTrash,D3DXVECTOR3(120,120,0.0f),3,YELLOW(1.0));
							pGetScore->AddScore(150);
							CManager::AddScore(CManager::MODE_TRASHGAME,150);
						}
						//�I�u�W�F�N�g�̈ʒu����ʊO�� -> ��ʊO����ŏ���
						pScene->SetPosition(D3DXVECTOR3(100.0f,1000.0f,0.0f));
						
					}
				}
			}
			else if(type == CScene::OBJTYPE_POINT2D)
			{//�}�E�X�̈ʒu�Ƀe�N�X�`��
				
				//������
				/*if( CManager::GetInputMouse()->GetMouseLeftTrigger() )
				{
					m_pMouse->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
				}*/

				D3DXVECTOR3 posMouse;
				posMouse = pScene->GetPosition();
				m_pMouse->SetPosition(posMouse);


				//��ʒ��S�Ƀe�N�X�`��
				m_pCenterPoint->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
				//�}�E�X�̈ʒu�Ɖ�ʒ����̊ԂɃe�N�X�`��
				D3DXVECTOR3 posMidpoint;
				posMidpoint= D3DXVECTOR3( (posMouse.x + SCREEN_WIDTH/2)/2,(posMouse.y + SCREEN_HEIGHT/2)/2,0.0f);
				m_pMidpoint->SetPosition(posMidpoint);
				//�N���b�N���ĂȂ��Ƃ��͉�ʊO��
				if(!CManager::GetInputMouse()->GetMouseLeftPress())
				{
					m_pCenterPoint->SetPosition(D3DXVECTOR3(-100,-100,0.0f));
					m_pMidpoint->SetPosition(D3DXVECTOR3(-100,-100,0.0f));
					m_pMouse->SetPosition(D3DXVECTOR3(-100,-100,0.0f));
				}
			}
		}
	}
	//�ϐg���O
	if(pTime->GetTime() == 11)
	{
		pAnimPlayer->SetColor(RED(1.0));
		if(pExplosion == NULL)
		{
			//��
			//pExplosion = CTrashGameExplosion::Create(D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 400.0f, 400.0f, 0.0f));
			//pExplosion->ChangeTextureAnime(0, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),
											//D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));

		}
	}
	
	if(pTime->GetTime() <= 11 && pTime->GetTime() >= 10)
	{
		
	}
	//�c�莞�Ԃ��P�O�ɂȂ�����
	if(pTime->GetTime() == 10)
	{
		pAnimPlayer->SetColor(WHITE(1.0));
		//player�̃|�C���^�����
		//CPlayer2D* pPlayer;
		//for(int nCntScene = 0;nCntScene < MAX_SCENE;nCntScene++)
		//{
		//	CScene *pScene;
		//	pScene = CScene::GetScene(nCntScene);
		//	if(pScene != NULL)
		//	{
		//		CScene::OBJTYPE type;
		//		type = pScene->GetObjType();
		//		if(type == CScene::OBJTYPE_PLAYER)
		//		{
		//			if( ((CPlayer2D*)pScene)->GetGorillaMode() == false )
		//			{
		//				//�S�������[�h��
		//				((CPlayer2D*)pScene)->SetGorillaMode();
		
		//�S�������[�h�ɂ���
		if( pAnimPlayer->GetGorillaMode() == false )
		{
			pTime->StopTime();
			CChange::Create(TEXTURENAME,GORILLA_GORILLA,STAND_GORILLA);

			//pAnimPlayer->Uninit();
			//pAnimPlayer = NULL;
			//pAnimPlayer = CTrashPlayer::Create(D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f),TEXTURE_GORILLA);
			pAnimPlayer->SetGorillaMode();

			//�S�~�𕡐�����
			//CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_LEFTTRASH);
			//CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_RIGHTTRASH);
		}
						/*			}
				}
			}
			break;
		}*/
	}

	if(pAnimPlayer->GetGorillaMode() == true && CChange::GetState() == false)
	{
		pAnimPlayer->Uninit();
		pAnimPlayer = NULL;
		pAnimPlayer = CTrashPlayer::Create(D3DXVECTOR3( 150.0f, 580.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f),TEXTURE_GORILLA);
		pAnimPlayer->SetGorillaMode();
		//�S�~�𕡐�����
		//CTrash::Create(D3DXVECTOR3(100.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_LEFTTRASH);
		//CTrash::Create(D3DXVECTOR3(300.0f, 370.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_RIGHTTRASH);
	
		CChange::changeState();
		pTime->StopTime();
	}

	if(pTime != NULL && pTime->GetTime() == 1)
	{
		if(bMessageFlag == false)
		{
			CMessage::Create(D3DXVECTOR3(SCREEN_WIDTH + 100,100,0),D3DXVECTOR3(200,200,0),TEXTURE_FINISH);
			bMessageFlag = true;
		}
	}
	//���Ԃ��O�ɂȂ�����
	if(pTime != NULL && pTime->GetTime() == 0)
	{
		if(bMessageFlag == false)
		{
			CMessage::Create(D3DXVECTOR3(SCREEN_WIDTH + 100,100,0),D3DXVECTOR3(200,200,0),TEXTURE_FINISH);
			bMessageFlag = true;
		}
		for(int nCntScene = 0;nCntScene < MAX_SCENE;nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene);
			if(pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene->GetObjType();
				if(type == CScene::OBJTYPE_TRASH || type == CScene::OBJTYPE_LEFTTRASH || type == CScene::OBJTYPE_RIGHTTRASH)
				{
					((CTrash*)pScene)->TrashEnd();
				}
			}
		}

		//pTime->Uninit();
		//SaveScore(GAME_TRASH,);
		SetNextScene( MODE_TRASHGAMERESULT);
		//pTime->Uninit();
		//return;
		//pTime->StopTime();
		//pTime->Uninit();
		//pTime = NULL;

	}
#ifdef _DEBUG
	//�V�[���̐؂�ւ�
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_ZEBRAGAME);
	}

	//�V�[���̐؂�ւ�
	if( pInputKeyboard->GetKeyTrigger(DIK_E))
	{
		SetNextScene( MODE_RESULT);
	}
#endif

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CTrashGame::Draw()
{
	CManager::Draw();
}
//���ɓ�����S�~�̃|�C���^���Z�b�g
void CTrashGame::SetTrashPointer(CTrash *pTrash)
{
	m_pTrash = pTrash;
}

int CTrashGame::GetTrashGameCnt(void)
{
	return m_nTrashGameCnt;
}