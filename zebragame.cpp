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
#include "meshField.h"
#include "playerX.h"
#include "toy.h"
#include "point3D.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "time.h"
#include "toybox.h"
#include "book.h"
#include "meshWall.h"
#include "putbook.h"
#include "effectBoom.h"
#include "mousePick.h"
#include "effect3D.h"

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
int CZebraGame::m_PutToy = 0;
int CZebraGame::m_PutBook = 0;
CPoint3D *CZebraGame:: m_pPoint3D= NULL;
CScore *CZebraGame::m_pScore = NULL;
//============================================
//�R���X�g���N�^
//============================================
CZebraGame::CZebraGame() : CManager(MODE_ZEBRAGAME)
{

}

CZebraGame::~CZebraGame()
{
	
}

HRESULT CZebraGame::Init(void)
{
	//�Q�[���f�[�^�����[�h
	LoadAll();

	//�J�����̈ʒu
	m_pCamera->Init();
	m_pCamera->SetPosV(D3DXVECTOR3(0.0f,300.0f,-500.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(0.0f,0.0f,400.0f));

	//��
	CMeshField::Create( D3DXVECTOR3( 0.0f,- 10.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f, CMeshField::TYPE_GREEN);

	//�E�H�[��
	CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 450.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( -450.0f, 100.0f, 200.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(270.0f), 0.0f), 10, 10, 100.0f, 100.0f);
	CMeshWall::Create( D3DXVECTOR3( 450.0f, 100.0f, 200.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 10, 10, 100.0f, 100.0f);

	//�J�����̈ʒu
	CManager::GetCamera() ->SetPosV(D3DXVECTOR3(0.0f,300.0f,-550.0f));
	CManager::GetCamera() ->SetPosR(D3DXVECTOR3(0.0f,0.0f,400.0f));

	//����
	unsigned int now = (unsigned int)time( 0 );
	srand(now);
	int varX,varZ,varR;
	//�I�u�W�F�N�g�̐���(3D)
	CBookBox::Create(D3DXVECTOR3(300.0f,0.0f,370.0f) , D3DXVECTOR3( 0.0f, 0.0f, 0.0f),CBookBox::TYPE_TOYBOX);
	CBookBox::Create(D3DXVECTOR3(-300.0f,0.0f,370.0f) , D3DXVECTOR3( 0.0f,D3DXToRadian(90.0f), 0.0f),CBookBox::TYPE_BOOKBOX);
	for(int nCnt = 0 ; nCnt < MAX_TOY ;nCnt++)
	{
		varX = rand() % 101 ;
		varZ = rand() % 101 ;
		varR = rand() % 101 ;
		//�I�u�W�F�N�g�̐���(Xfile)
		CToy::Create( D3DXVECTOR3( 5.0f*varX-350.0f, 10.0f, 5.0f*varZ-300.0f), D3DXVECTOR3( 0.0f,D3DXToRadian(30*varR), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	}


	for(int nCnt = 0 ; nCnt < MAX_BOOK ;nCnt++)
	{
		varX = rand() % 101 ;
		varZ = rand() % 101 ;
		varR = rand() % 101 ;
		//�I�u�W�F�N�g�̐���(Xfile)
		CBook::Create( D3DXVECTOR3( 5.0f*varX-350.0f, 10.0f, 5.0f*varZ-300.0f), D3DXVECTOR3( 0.0f,D3DXToRadian(30*varR), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	}

	
	
	//�I�u�W�F�N�g�̐���(2D�|���S��)
	//�^�C��
	CTime::Create(D3DXVECTOR3(600, 50.0f, 0.0f),D3DXVECTOR3(100, 100.0f, 0.0f), 3, 0, false,D3DXCOLOR(255,255,255,255));

	//�X�R�A
	m_pScore = CScore::Create( D3DXVECTOR3( 150.0f, 30.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	//�I�u�W�F�N�g�̐���(2D�|���S��)
	m_pPoint3D = CPoint3D::Create( D3DXVECTOR3( 300.0f, 500.0f, 0.0f), D3DXVECTOR3( 60.0f, 60.0f, 0.0f),0);

	return S_OK;
}

void CZebraGame::Uninit()
{
	//�_����ۑ�
	CManager::SaveScore( MODE_ZEBRAGAME, m_pScore->GetValue());

	CManager::Uninit();
}

void CZebraGame::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();

#ifdef _DEBUG
	//�X�L�b�v�V�[��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_STAGE_ZEBRA);
	}

	POINT mPos;
	GetCursorPos(&mPos);
	D3DXVECTOR3 pos = CMousePick::GetWorldPos(mPos);
	
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	if( pInputMouse->GetMouseLeftTrigger())
	{
		CEffectBoom::Create( pos, D3DXVECTOR3(100, 20, 100), 5);
	}
#endif

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CZebraGame::Draw()
{
	CManager::Draw();
}

void CZebraGame :: PutObj(bool toy)
{
	if(toy == true)
	{
		m_PutToy++;
	}
	if(toy == false)
	{
		m_PutBook++;
	}
	if( m_PutToy + m_PutBook == 20)
	{
		m_pPoint3D -> ChangeZebra();
	}
	if (m_PutToy + m_PutBook == MAX_TOY + MAX_BOOK)
	{
		SetNextScene( MODE_STAGE_ZEBRA);
	}
}
//=============================================================================
//
//=============================================================================
CScore *CZebraGame::GetScore(void)
{
	return m_pScore;
}
//=============================================================================
//�Q�[���������オ��Ƃ��A���̂ݑS�����[�h����
//=============================================================================
HRESULT CZebraGame::LoadAll(void)
{
	CMeshField::Load();
	CMeshWall::Load();
	CPutBook::Load();
	CToy::Load();
	CBook::Load();
	CEffect3D::Load();

	return S_OK;
}
