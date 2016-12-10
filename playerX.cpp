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
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME "data/MODEL/plain.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// ��]��

//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPlayerX::CPlayerX()
{

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
	CSceneX::Init( pos, rot, scl, MODEL_FILENAME);

	m_isGoAhead = false;
	m_isGoBack = false;
	m_speed = speed;
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);	
	
	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Update(void)
{
	bool isMoved;
	isMoved = isKeyUse(DIK_W, DIK_S, DIK_A, DIK_D);
	//isMoved = isMouseUse();
	if( isMoved == true)
	{
		UpdateRot();
	}
	CalcNextPos();

	D3DXVECTOR3 pos = GetPosition();
	CDebugProc::Print("\nplayer x:%f, y:%f, z%f",pos.x, pos.y, pos.z);
}

//=============================================================================
//
//=============================================================================
void CPlayerX::Draw(void)
{
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

	return pPlayerX;
}


void CPlayerX::UpdateRot(void)
{
	D3DXVECTOR3 rotPlayer = GetRot();

	//��]����
	m_rotAngle.y *= 0.999f;

	//���̉�]�ʒu�ɓ���������
	float diff = abs(rotPlayer.y - m_rotTarget.y);
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

	const float rotSpeed = 1.0f;

	//������
	m_isGoAhead = false;
	m_isGoBack = false;


	//�΂߈ړ�
	if( (pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nUp)) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nDown)) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft)  && pInputKeyboard->GetKeyPress(nUp))  ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft) && pInputKeyboard->GetKeyPress(nDown)) ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
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
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-1.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputKeyboard->GetKeyPress(nRight) )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(1.0f);
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

	const float rotSpeed = 1.0f;
	const int nDeadZone = 0;

	//������
	m_isGoAhead = false;
	m_isGoBack = false;


	//�΂߈ړ�
	if( (pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseLeftPress()) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() > nDeadZone && pInputMouse->GetMouseRightPress()) ) //�E��
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(rotSpeed);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		m_isGoBack = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone  && pInputMouse->GetMouseLeftPress())  ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		m_isGoAhead = true;
	}
	else if((pInputMouse->GetMouseAxisX() < -nDeadZone && pInputMouse->GetMouseRightPress()) ) //����
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-rotSpeed);
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
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(-1.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		return true;
	}
	else if(pInputMouse->GetMouseAxisX() > nDeadZone )
	{
		m_rotTarget.y = rotPlayer.y + D3DXToRadian(1.0f);
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
		//�ړ������̏�����
		m_move = D3DXVECTOR3( m_speed, 0.0f, m_speed);

		////���v���A�܂��͋t���v�������߂�
		//m_rotAngle =  Get2RotDiffAngle( m_rot, m_rotTarget);
	}

	if(m_isGoBack == true)
	{
		//�ړ������̏�����
		m_move = -D3DXVECTOR3( m_speed, 0.0f, m_speed);

		////���v���A�܂��͋t���v�������߂�
		//m_rotAngle =  Get2RotDiffAngle( m_rot, m_rotTarget);		
	}

	//��]���Ă��Ȃ���
	if( m_rotAngle.y == 0)
	{
		//�ړ�
		m_front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
		m_front.x = m_move.x * sinf( rotPlayer.y);
		m_front.z = m_move.z * cosf( rotPlayer.y);

		//��������
		m_move -= m_move * 0.25f;	
	}
}

D3DXVECTOR3 CPlayerX::GetFront(void)
{
	return m_front;
}

//=============================================================================
// ��]�p�x���擾
//=============================================================================
D3DXVECTOR3 CPlayerX::Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget)
{
	float tAngle[3];
	D3DXVECTOR3 re;

	tAngle[0] = rotTarget.x - rot.x;
	tAngle[1] = rotTarget.y - rot.y;
	tAngle[2] = rotTarget.z - rot.z;

	for(int cntXYZ = 0; cntXYZ < 3; cntXYZ++)
	{
		if(tAngle[cntXYZ] > D3DX_PI)
		{
			tAngle[cntXYZ] -= 2 * D3DX_PI;
		}
		if(tAngle[cntXYZ] < -D3DX_PI)
		{
			tAngle[cntXYZ] += 2 * D3DX_PI;
		}		

//		tAngle[cntXYZ] = tAngle[cntXYZ] / DIVIDE_ROTATE;
		tAngle[cntXYZ] = tAngle[cntXYZ] / abs(tAngle[cntXYZ]) * VALUE_ROTATE;

	}

	re.x = tAngle[0];
	re.y = tAngle[1];
	re.z = tAngle[2];

	return re;
}