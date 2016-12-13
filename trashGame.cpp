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
//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
#define TEXTURE_POINT "data/TEXTURE/redPoint.png"
#define TEXTURE_TRASH "data/TEXTURE/�y�b�g�{�g��.png"
#define TEXTURE_TRASHBOX "data/TEXTURE/�S�~��(�D�F).png"
#define TEXTURE_GORILLA "data/TEXTURE/�S����.png"
#define TEXTURE_BGPOLYGON "data/TEXTURE/rendering003-16.png"

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
CTime *pTime = NULL;
CPlayer2D *pPlayer2D = NULL;
int CTrashGame::m_nTrashGameCnt = 0;
//============================================
//�R���X�g���N�^
//============================================
CTrashGame::CTrashGame() : CManager(MODE_GAME)
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

	//�I�u�W�F�N�g�̐���(3D�|���S��)
	//CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//�I�u�W�F�N�g�̐���(Xfile)
	//CPlayerX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);

	//�w�i
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f),TEXTURE_BGPOLYGON);
	//�I�u�W�F�N�g�̐���(2D�|���S��)
	pPlayer2D = CPlayer2D::Create( D3DXVECTOR3( 150.0f, 480.0f, 0.0f), D3DXVECTOR3( 200.0f, 200.0f, 0.0f));
	//�S�~
	m_pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CScene::OBJTYPE_TRASH);
	//�X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(150, 50.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f), 6, BLUE(1.0f));
	//�S�~��
	m_pTrashBox = CScene2D::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), D3DXVECTOR3(400.0f, 500.0f, 0.0f),TEXTURE_TRASHBOX);
	//�^�C��
	pTime = CTime::Create(D3DXVECTOR3(600, 50.0f, 0.0f),D3DXVECTOR3(100, 100.0f, 0.0f),3,15,true,D3DXCOLOR(255,255,255,255));
	//�}�E�X�̈ʒu�𓾂�
	CPoint2D::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f),0);
	//�˂ɒ�����
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(70.0f, 70.0f, 0.0f),TEXTURE_POINT);
	//�����ƌ��݈ʒu�̒��ԂɃe�N�X�`��
	m_pMidpoint = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f),TEXTURE_POINT);
	//�}�E�X�̈ʒu�Ƀe�N�X�`��
	m_pMouse = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f),TEXTURE_POINT);
	return S_OK;
}

void CTrashGame::Uninit()
{
	CManager::Uninit();
}

void CTrashGame::Update()
{
	m_nTrashGameCnt++;

	D3DXVECTOR3 posTrashBox;
	D3DXVECTOR3 sizeTrashBox;
	posTrashBox = m_pTrashBox->GetPosition();
	sizeTrashBox = m_pTrashBox->GetSize();
	//D3DXVECTOR3 posMouse;

	//posMouse = m_pPoint2D->GetPosition();
	//pMouse->SetPosition(posMouse); 
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_RESULT);
	}

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
					(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrashBox.x*0.6/2) &&
					(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrashBox.x*0.6/2))
				{
					D3DXVECTOR3 speed;
					speed = ((CTrash*)pScene)->GetSpeed();
					if(speed.x > 0 &&
						//(posTrash.x - sizeTrash.x/2) < (posTrashBox.x - sizeTrashBox.x) //&&
						(posTrash.y - sizeTrash.y/2) > (posTrashBox.y - sizeTrashBox.y/2) )//||
						//(posTrash.x < (posTrashBox.x - sizeTrashBox.x/2)))
					{//�O���̉E�[�ł͂���
						((CTrash*)pScene)->ReverseMove();
					}
					else
					{//���S�ɓ����Ă�
						//�X�R�A�ǉ�
						if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_NORMAL)
						{
							m_pScore->AddScore(100);
						}
						else if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_LIGHT)
						{
							m_pScore->AddScore(180);
						}
						else if(((CTrash*)pScene)->GetTrashType() == CTrash::TRASHTYPE_HEAVY)
						{
							m_pScore->AddScore(150);
						}
						//�I�u�W�F�N�g�̈ʒu����ʊO�� -> ��ʊO����ŏ���
						pScene->SetPosition(D3DXVECTOR3(100.0f,1000.0f,0.0f));
					}
				}
				if(m_nTrashGameCnt % 5 == 0)
				{
					CTrajectory::Create(D3DXVECTOR3(posTrash.x,posTrash.y,0.0f),D3DXVECTOR3(50,50,0.0f));
				}
			}
			else if(type == CScene::OBJTYPE_POINT2D)
			{//�}�E�X�̈ʒu�Ƀe�N�X�`��
				D3DXVECTOR3 posMouse;
				posMouse = pScene->GetPosition();
				m_pMouse->SetPosition(posMouse);
				
				D3DXVECTOR3 posMidpoint;
				posMidpoint= D3DXVECTOR3( (posMouse.x + SCREEN_WIDTH/2)/2,(posMouse.y + SCREEN_HEIGHT/2)/2,0.0f);
				m_pMidpoint->SetPosition(posMidpoint);
			}
		}
	}

	if(pTime->GetTime() == 10)
	{
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
		if( pPlayer2D->CPlayer2D::GetGorillaMode() == false )
		{
			pPlayer2D->CPlayer2D::SetGorillaMode();
						//�S�~�𕡐�����
						CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_LEFTTRASH);
						CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f),TEXTURE_TRASH,CTrash::OBJTYPE_RIGHTTRASH);
		}
						/*			}
				}
			}
			break;
		}*/
	}
	if(pTime->GetTime() == 0)
	{
		pTime->Uninit();
		SetNextScene( MODE_RESULT);
	}
	CManager::Update();
}
void CTrashGame::Draw()
{
	CManager::Draw();
}
void CTrashGame::SetTrashPointer(CTrash *pTrash)
{
	m_pTrash = pTrash;
}

int CTrashGame::GetTrashGameCnt(void)
{
	return m_nTrashGameCnt;
}