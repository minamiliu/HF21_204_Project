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
#include "debugproc.h"

//============================================
// �}�N����`
//============================================
#define CAMERA_DISTANCE	(200.0f)
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================


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

	//�I�u�W�F�N�g�̐���(3D�|���S��)
	CScene3D::Create( D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 10, 10, 100.0f, 100.0f);

	//�E�H�[��
	CMeshWall::Load();
	m_nNumWall = 0;
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, 500.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 11, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 500.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), 11, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( -500.0f, 100.0f, 0.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(-90.0f), 0.0f), 11, 4, 100.0f, 100.0f);
	m_pMeshWall[m_nNumWall++] = CMeshWall::Create( D3DXVECTOR3( 0.0f, 100.0f, -500.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(180.0f), 0.0f), 11, 4, 100.0f, 100.0f);


	//�I�u�W�F�N�g�̐���(Xfile)
	m_player = CPlayerX::Create( D3DXVECTOR3( -100.0f, 0.0f, -100.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), 5.0f);
	
	m_nNumCube = 0;
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 50.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 100.0f, 100.0f, 300.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 300.0f, 50.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 100.0f, 100.0f, 300.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( -300.0f, 50.0f, 0.0f), D3DXVECTOR3( 0.0f, 0.0f, 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 100.0f, 100.0f, 300.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 50.0f, 300.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 300.0f, 100.0f, 100.0f));
	m_cube[m_nNumCube++] = CCubeX::Create( D3DXVECTOR3( 0.0f, 50.0f, -300.0f), D3DXVECTOR3( 0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3( 1.0f, 1.0f, 1.0f), D3DXVECTOR3( 300.0f, 100.0f, 100.0f));

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

	{//�J�����Ǐ]
		CCamera *pCamera = GetCamera();

		//�����_
		pCamera->SetPosR( m_player->GetPosition());

		//���_
		D3DXVECTOR3 posV = pCamera->GetPosV();
		posV.x = pCamera->GetPosR().x - CAMERA_DISTANCE * sinf(pCamera->GetRot().y);
		posV.z = pCamera->GetPosR().z - CAMERA_DISTANCE * cosf(pCamera->GetRot().y);
		pCamera->SetPosV( posV);

		//����
		pCamera->SetRot( m_player->GetRot());
	}

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



	//�ړ�
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
