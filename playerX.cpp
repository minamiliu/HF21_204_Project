//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: playerX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "playerX.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "collision.h"
#include "score.h"
#include "lionGame.h"
#include "shadow.h"
#include "food.h"
#include "foodIcon.h"
#include "limbX.h"
#include "meshWall.h"
#include "cubeX.h"
#include "enemyX.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME_BODY		"data/MODEL/mom_body.x"
#define VALUE_ROTATE	(1.0f) 	// ��]��

#define PLAYER_RADIUS	(15.0f)
#define CAMERA_DISTANCE	(200.0f)
//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayerX::CPlayerX()
{
	m_pShadow = NULL;

	//�葫
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb] = NULL;
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPlayerX::~CPlayerX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CPlayerX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CSceneX::Init( pos, rot, scl);

	m_isGoAhead = false;
	m_isGoBack = false;
	
	m_fSpeed = 0.0f;
	m_fAccel = speed;

	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	m_state = STATE_NORMAL;
	m_nCntState = 0;

	//�葫
	m_pLimb[0] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_L_HAND);
	m_pLimb[1] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_R_HAND);
	m_pLimb[2] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_L_FOOT);
	m_pLimb[3] = CLimbX::Create( pos, rot, scl, CLimbX::TYPE_R_FOOT);

	//�e�̐���
	m_pShadow = CShadow::Create( pos, D3DXVECTOR2( 50.0f, 50.0f));

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Uninit(void)
{
	//�葫
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->Uninit();
	}

	//�{��
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Update(void)
{
	//�ړ�����
	bool isMoved = false;
	bool bHitWall = false;
	bool bHitCube = false;
	int nHitCubeID = 0;
	D3DXVECTOR3 wall_nor;
	D3DXVECTOR3 posPlayer = GetPosition();
	D3DXVECTOR3 rotPlayer = GetRot();


	isMoved = isKeyUse(DIK_W, DIK_S, DIK_A, DIK_D);
	//isMoved = isMouseUse();
	if( isMoved == true)
	{
		UpdateRot();
	}

	//�O�i�x�N�g���̍X�V
	CalcNextPos();


	{//�J�����Ǐ]
		CCamera *pCamera = CManager::GetCamera();

		//�����_
		pCamera->SetPosR( this->GetPosition());

		//���_
		D3DXVECTOR3 posV = pCamera->GetPosV();
		posV.x = pCamera->GetPosR().x - CAMERA_DISTANCE * sinf(pCamera->GetRot().y);
		posV.z = pCamera->GetPosR().z - CAMERA_DISTANCE * cosf(pCamera->GetRot().y);
		pCamera->SetPosV( posV);

		//����
		pCamera->SetRot( this->GetRot());
	}

	//�����蔻��̑O����
	D3DXVECTOR3 posLside = posPlayer;
	posLside.x = posPlayer.x +  PLAYER_RADIUS * sinf(rotPlayer.y + D3DXToRadian(-90.0f));
	posLside.z = posPlayer.z +  PLAYER_RADIUS * cosf(rotPlayer.y + D3DXToRadian(-90.0f));

	D3DXVECTOR3 posRside = posPlayer;
	posRside.x = posPlayer.x +  PLAYER_RADIUS * sinf(rotPlayer.y + D3DXToRadian(90.0f));
	posRside.z = posPlayer.z +  PLAYER_RADIUS * cosf(rotPlayer.y + D3DXToRadian(90.0f));

	//�����蔻��
	for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene( nCntScene);
		
		if( pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();

			//�H�ނƂ̂����蔻��
			if (type == CScene::OBJTYPE_L_FOOD)
			{
				D3DXVECTOR3 posFood;
				posFood = pScene->GetPosition();

				if (CCollision::HitCheckCircleXZ(posPlayer, PLAYER_RADIUS, posFood, 10.f))
				{
					CFood *pFood = ((CFood*)pScene);

					//�A�C�R���̐F��ς���
					CFoodIcon *pFoodIcon = pFood->GetIcon();
					pFoodIcon->SetColor(WHITE(1.0f));

					//�H�ރQ�b�g
					pFood->SetClear();

					//�H�ނ̔j��
					pScene->Uninit();

					//�X�R�A
					CLionGame::GetScore()->AddScore(100);

					//return;
				}
			}

			//�G�Ƃ̓����蔻��
			else if( type == CScene::OBJTYPE_L_ENEMY && m_state != STATE_HIT)
			{
				D3DXVECTOR3 posEnemy;
				posEnemy = pScene->GetPosition();

				if( CCollision::HitCheckBall( posPlayer, PLAYER_RADIUS, posEnemy, PLAYER_RADIUS))
				{
					switch(m_state)
					{
					case STATE_NORMAL:
						m_state = STATE_HIT;
						m_nCntState = 60;
						m_fSpeed = -2.0f;
						m_isGoBack = true;
						//�O�i�x�N�g���̍X�V
						CalcNextPos();
						break;
					case STATE_LION:
						CEnemyX *pEnemy = (CEnemyX*)pScene;
						pEnemy->SetState(CEnemyX::STATE_STUN, 60);
						break;
					}
			
				}
			}

			//�ǂƂ̂����蔻��
			else if( type == CScene::OBJTYPE_WALL)
			{
				CMeshWall *pWall = (CMeshWall*)pScene;

				D3DXVECTOR3 tSphere;
				D3DXVec3Normalize( &tSphere, &m_front);
				tSphere *= PLAYER_RADIUS;

				if( pWall->HitCheck( posPlayer, posPlayer + tSphere, &wall_nor, NULL) ||
					pWall->HitCheck( posLside, posLside + tSphere, &wall_nor, NULL) ||
					pWall->HitCheck( posRside, posRside + tSphere, &wall_nor, NULL))
				{
					bHitWall = true;
				}
			}

			//�I�Ƃ̂����蔻��
			else if( type == CScene::OBJTYPE_CUBE)
			{
				CCubeX *pCube = (CCubeX*)pScene;

				//�����蔻��
				float len = pCube->GetDistanceBoxPoint( posPlayer + m_front);
				if( len < PLAYER_RADIUS)
				{
					//���W
					if(pCube->GetType() == CCubeX::TYPE_1X1)
					{
						if(CFood::isAllClear() == true)
						{
							CManager::SetNextScene( CManager::MODE_RESULT);
						}
					}

					nHitCubeID = nCntScene;
					bHitCube = true;
				}	
				
			}
		}
	}

	//�C�������O�i�x�N�g����������x�����蔻����Ƃ�
	if( bHitWall == true)
	{
		bHitWall = false;

		//�O�i�����̏C��
		CCollision::GetWallScratchVector( &m_front, m_front, wall_nor);

		//�����蔻��(����)
		for( int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene *pScene;
			pScene = CScene::GetScene( nCntScene);
		
			if( pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene->GetObjType();

				//�ǂƂ̂����蔻��(����)
				if( type == CScene::OBJTYPE_WALL)
				{
					CMeshWall *pWall = (CMeshWall*)pScene;

					D3DXVECTOR3 tSphere;
					D3DXVec3Normalize( &tSphere, &m_front);
					tSphere *= PLAYER_RADIUS;
				
					if( pWall->HitCheck( posPlayer, posPlayer + tSphere, &wall_nor, NULL) ||
						pWall->HitCheck( posLside, posLside + tSphere, &wall_nor, NULL) ||
						pWall->HitCheck( posRside, posRside + tSphere, &wall_nor, NULL))
					{
						bHitWall = true;
					}
				
				}	
			}		
		}
	}
	else if( bHitCube == true)
	{
		//�O�i�����̏C��
		D3DXVECTOR3 vecX = D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vecZ = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
		CCollision::GetWallScratchVector( &vecX, m_front, vecX);
		CCollision::GetWallScratchVector( &vecZ, m_front, vecZ);

		//�����蔻��(����)
		CScene *pScene;
		pScene = CScene::GetScene( nHitCubeID);
		
		if( pScene != NULL)
		{
			CScene::OBJTYPE type;
			type = pScene->GetObjType();

			//�I�Ƃ̂����蔻��(����)
			if( type == CScene::OBJTYPE_CUBE)
			{
				CCubeX *pCube = (CCubeX*)pScene;

				if( pCube->GetDistanceBoxPoint( posPlayer + vecX) >= PLAYER_RADIUS)
				{
					bHitCube = false;
					m_front = vecX;
				}
				if( pCube->GetDistanceBoxPoint( posPlayer + vecZ) >= PLAYER_RADIUS)
				{
					bHitCube = false;
					m_front = vecZ;
				}
			}	
		}		
	}

	//���W�X�V����
	if( bHitWall == false && bHitCube == false)
	{
		SetPosition( posPlayer + m_front);
	}

	//��ԍX�V
	switch( m_state)
	{
	case STATE_HIT:
		m_nCntState--;
		if( m_nCntState <= 0)
		{
			m_state = STATE_NORMAL;
		}
		break;
	}

	//�葫
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->SetPosition(this->GetPosition());
		m_pLimb[cntLimb]->SetRot(this->GetRot());
		m_pLimb[cntLimb]->Update();
	}

	//�e�̍X�V����
	m_pShadow->SetPosition( this->GetPosition());

}

//=============================================================================
//
//=============================================================================
void CPlayerX::Draw(void)
{
	//�葫
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->Draw();
	}

	//�{��
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CPlayerX *CPlayerX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CPlayerX *pPlayerX;
	pPlayerX = new CPlayerX;
	pPlayerX->Init(pos, rot, scl, speed);

	//X�t�@�C���̓ǂݍ���
	pPlayerX->LoadXfile(MODEL_FILENAME_BODY);

	return pPlayerX;
}


void CPlayerX::UpdateRot(void)
{
	D3DXVECTOR3 rotPlayer = GetRot();

	//��]����
	m_rotAngle.y *= 0.999f;

	//���̉�]�ʒu�ɓ���������
	float diff = fabsf(rotPlayer.y - m_rotTarget.y);
	if( diff > D3DX_PI)
	{
		diff -= D3DX_PI*2;
	}

	if(diff < VALUE_ROTATE)
	{
		rotPlayer.y = m_rotTarget.y;
		m_rotAngle.y = 0;
	}
	else //���̉�]�ʒu�ɂ܂��������ĂȂ�
	{
		rotPlayer.y += m_rotAngle.y;

		//���f���p�x�C��
		if( rotPlayer.y > D3DX_PI)
		{
			rotPlayer.y -= D3DX_PI*2;
		}
		else if(rotPlayer.y <= -D3DX_PI)
		{
			rotPlayer.y += D3DX_PI*2;
		}
	}	

	//�f�[�^�̍X�V
	SetRot(rotPlayer);
}

bool CPlayerX::isKeyUse(int nUp, int nDown, int nLeft, int nRight)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetRot();
	D3DXVECTOR3 rotPlayer = GetRot();

	//������
	m_isGoAhead = false;
	m_isGoBack = false;


	//�΂߈ړ�
	if( (pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nUp)) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nDown)) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft)  && pInputKeyboard->GetKeyPress(nUp))  ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft) && pInputKeyboard->GetKeyPress(nDown)) ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if(pInputKeyboard->GetKeyPress(nUp) )
	{
		m_isGoAhead = true;
	}
	else if(pInputKeyboard->GetKeyPress(nDown) )
	{
		m_isGoBack = true;
	}
	else if(pInputKeyboard->GetKeyPress(nLeft) )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputKeyboard->GetKeyPress(nRight) )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		return true;
	}

	//���삵����
	if( m_isGoAhead || m_isGoBack)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CPlayerX::isMouseUse(void)
{
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetRot();
	D3DXVECTOR3 rotPlayer = GetRot();

	const int nDeadZone = 0;

	//������
	m_isGoAhead = false;
	m_isGoBack = false;


	//�΂߈ړ�
	if( (pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseLeftPress()) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseRightPress()) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone  && pInputMouse->GetMouseLeftPress())  ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone && pInputMouse->GetMouseRightPress()) ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if(pInputMouse->GetMouseLeftPress() )
	{
		m_isGoAhead = true;
	}
	else if(pInputMouse->GetMouseRightPress() )
	{
		m_isGoBack = true;
	}
	else if(pInputMouse->GetMouseAxisX() < -nDeadZone )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-VALUE_ROTATE);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputMouse->GetMouseAxisX() > nDeadZone )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(VALUE_ROTATE);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		return true;
	}

	//���삵����
	if( m_isGoAhead || m_isGoBack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPlayerX::CalcNextPos(void)
{
	D3DXVECTOR3 posPlayer = GetPosition();
	D3DXVECTOR3 rotPlayer = GetRot();

	if(m_isGoAhead == true)
	{
		m_fSpeed += m_fAccel;
		if( m_fSpeed > 10.0f)
		{
			m_fSpeed = 10.0f;
		}

		//�ړ������̏�����
		m_move = D3DXVECTOR3( m_fSpeed, 0.0f, m_fSpeed);

	}
	else if(m_isGoBack == true)
	{
		m_fSpeed -= m_fAccel;

		if( m_fSpeed < -10.0f)
		{
			m_fSpeed = -10.0f;
		}

		//�ړ������̏�����
		m_move = D3DXVECTOR3( m_fSpeed, 0.0f, m_fSpeed);	
	}
	else
	{
		m_fSpeed -= m_fSpeed * 0.25f;
	}


	//��]���Ă��Ȃ���
	if( m_rotAngle.y == 0)
	{
		//�ړ�
		m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
		m_front.x = m_move.x * sinf( rotPlayer.y);
		m_front.z = m_move.z * cosf( rotPlayer.y);

		//��������
		m_move -= m_move * 0.05f;
	}
}

D3DXVECTOR3 CPlayerX::GetFront(void)
{
	return m_front;
}

//=============================================================================
// �X�e�[�g��ݒ�
//=============================================================================
void CPlayerX::SetState(STATE state)
{
	m_state = state;
}
//=============================================================================
// �X�e�[�g���擾
//=============================================================================
CPlayerX::STATE CPlayerX::GetState(void)
{
	return m_state;
}