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
#include "debugproc.h"
#include "game.h"
#include "renderer.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "meshWall.h"
#include "playerX.h"
#include "collision.h"
#include "cubeX.h"
#include "itemX.h"
#include "score.h"
#include "enemyX.h"
#include "time.h"

//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CScore *CGame::m_score = NULL;

//============================================
//�R���X�g���N�^
//============================================
CGame::CGame() : CManager(MODE_GAME)
{

}

CGame::~CGame()
{
	
}

HRESULT CGame::Init(void)
{
	m_pCamera->Init();

	//��
	CScene3D::Create( D3DXVECTOR3( 1000.0f, 0.0f, 750.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 20, 15, 100.0f, 100.0f);

	//�E�H�[��
	CMeshWall::Load();
	m_nNumWall = 0;
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 1000.0f, 100.0f, 1500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 21, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 1000.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 21, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 2000.0f, 100.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 16, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 750.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 16, 4, 100.0f, 100.0f);
	
	//�I
	m_nNumCube = 0;
	//m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 200.0f, 100.0f, 100.0f));
	
	//��ԉ� �U��
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 250.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 550.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 850.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1150.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1450.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1750.0f, 50.0f, 1100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 400.0f), CCubeX::TYPE_1X4);

	//2�i�ځ@�U��
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 250.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 550.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 850.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1150.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1450.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1750.0f, 50.0f, 600.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 200.0f), CCubeX::TYPE_1X2);

	//���W�@�T��
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 350.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 650.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 950.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1250.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3(1550.0f, 50.0f, 250.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 100.0f, 100.0f, 100.0f), CCubeX::TYPE_1X1);
	


	//�v���C���[
	m_player = CPlayerX::Create( D3DXVECTOR3( 50.0f, 30.0f, 50.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 0.10f);

	//�A�C�e��
	CItemX::Create( D3DXVECTOR3( -200.0f, 30.0f, -200.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	CItemX::Create( D3DXVECTOR3( -100.0f, 30.0f, 100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	CItemX::Create( D3DXVECTOR3( 100.0f, 30.0f, -100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	CItemX::Create( D3DXVECTOR3( 100.0f, 30.0f, 100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));

	//�X�R�A
	m_score = CScore::Create( D3DXVECTOR3(150, 100.0f, 0.0f), D3DXVECTOR3( 300, 50.0f, 0.0f), 6, RED(1.0f)); 

	//�^�C��
	//CTime::Create( D3DXVECTOR3(SCREEN_WIDTH/2, 100.0f, 0.0f), D3DXVECTOR3(150, 100.0f, 0.0f), 2, 10, true, BLUE(1.0f));

	//�G
	CEnemyX::Create( D3DXVECTOR3( 50, 30.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	CEnemyX::Create( D3DXVECTOR3(350, 30.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	CEnemyX::Create( D3DXVECTOR3(650, 30.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	CEnemyX::Create( D3DXVECTOR3(950, 30.0f, 600.0f), D3DXVECTOR3( 0.0f, D3DX_PI/2, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f));

	return S_OK;
}

void CGame::Uninit()
{
	CManager::Uninit();
}

void CGame::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();


	//�ǂƂ̓����蔻��
	bool bHit = false;
	D3DXVECTOR3 front = m_player->GetFront();
	D3DXVECTOR3 posP = m_player->GetPosition();
	D3DXVECTOR3 wall_nor;
	for(int cntWall = 0; cntWall < m_nNumWall; cntWall++)
	{
		if( m_pMeshWall[cntWall]->HitCheck( posP,  posP + front, &wall_nor, NULL))
		{
			bHit = true;
			break;
		}
	}

	//�L���[�u�Ƃ̓����蔻��
	bool bHitCube = false;
	int nIDCube = 0;
	for(int cntCube = 0; cntCube < m_nNumCube; cntCube++)
	{
		float len = m_cube[cntCube]->GetDistanceBoxPoint( m_player->GetPosition() + front);
		if( len < 15.0f)
		{
			bHitCube = true;
			bHit = true;
			nIDCube = cntCube;
			break;
		}	
	}



	//�����蔻���̃v���C���[�ړ�
	if( bHit == false)
	{
		m_player->SetPosition( posP + front);
	}
	else
	{
		if( bHitCube == true)
		{
			D3DXVECTOR3 vecX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vecZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
			CCollision::GetWallScratchVector( &vecX, front, vecX);
			CCollision::GetWallScratchVector( &vecZ, front, vecZ);
			

			if( m_cube[nIDCube]->GetDistanceBoxPoint( m_player->GetPosition() + vecX) >= 15.0f)
			{
				m_player->SetPosition( posP + vecX);
			}
			if( m_cube[nIDCube]->GetDistanceBoxPoint( m_player->GetPosition() + vecZ) >= 15.0f)
			{
				m_player->SetPosition( posP + vecZ);
			}
		}
		else
		{
			bHit = false;

			//�O�i�����̏C��
			CCollision::GetWallScratchVector( &front, front, wall_nor);

			//�ǂƂ̓����蔻��(2���)
			for(int cntWall = 0; cntWall < m_nNumWall; cntWall++)
			{
				if( m_pMeshWall[cntWall]->HitCheck( posP,  posP + front, &wall_nor, NULL))
				{
					bHit = true;
					break;
				}
			}
			//�ړ�
			if( bHit == false)
			{
				m_player->SetPosition( posP + front);
			}		
		}
	}



	//�X�L�b�v�V�[��
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		SetNextScene( MODE_TRASHGAME);
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CGame::Draw()
{
	CManager::Draw();
}

CScore *CGame::GetScore(void)
{
	return m_score;
}