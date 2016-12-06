//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: sceneX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME "data/MODEL/player.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// ��]��

//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSceneX::CSceneX()
{
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�

	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// ���f���̈ʒu
	m_rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// ���f���̌���(��])
	m_scl = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);		// ���f���̑傫��(�X�P�[��)
	m_move = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);	// ���f���̈ړ���

	m_rotTarget = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_rotAngle = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);

	D3DXMatrixIdentity( &m_mtxWorld);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CSceneX::Init(void)
{
	return S_OK;
}

//=============================================================================
//
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	m_pos = pos;
	m_rot = rot;
	m_scl = scl;
	m_speed = speed;

	// ���f���Ɋւ���ϐ��̏�����							
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;		// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(
		MODEL_FILENAME,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
		pDevice,					// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&m_pD3DXBuffMat,		// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&m_nNumMat,			// D3DXMATERIAL�\���̂̐�
		&m_pD3DXMesh			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		)))
	{
		return E_FAIL;
	}	


	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CSceneX::Uninit(void)
{
	// �e�N�X�`���̊J��
	if(m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���b�V���̊J��
	if(m_pD3DXMesh != NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// �}�e���A���̊J��
	if(m_pD3DXBuffMat != NULL)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//
//=============================================================================
void CSceneX::Update(void)
{
	CDebugProc::Print("\nposX = %f\n", m_pos.x);
	CDebugProc::Print("posZ = %f\n", m_pos.z);
	CDebugProc::Print("rotY = %f\n", m_rot.y);
}

//=============================================================================
//
//=============================================================================
void CSceneX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// �X�P�[���𔽉f
	D3DXMatrixScaling( &mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl);
	
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot);
	
	// �ړ��𔽉f
	D3DXMatrixTranslation( &mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	
	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();
	for(int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial( &pD3DXMat[nCntMat].MatD3D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture( 0, m_pTexture);
		// �`��
		m_pD3DXMesh->DrawSubset( nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial( &matDef);
}

//=============================================================================
//
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CSceneX *pSceneX;
	pSceneX = new CSceneX;
	pSceneX->Init(pos, rot, scl, speed);

	return pSceneX;
}

//=============================================================================
// ��]�p�x���擾
//=============================================================================
D3DXVECTOR3 CSceneX::Get2VecRotAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget)
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

void CSceneX::UpdateModelMove(int nUp, int nDown, int nLeft, int nRight)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	D3DXVECTOR3 rotCamera = CManager::GetCamera()->GetCameraRot();


	//�ړ�����
	bool isKeyPressed = false;
	//�΂߈ړ�
	if( (pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nUp)) ) //�E��
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(45.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if((pInputKeyboard->GetKeyPress(nRight) && pInputKeyboard->GetKeyPress(nDown)) ) //�E��
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(135.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft)  && pInputKeyboard->GetKeyPress(nUp))  ) //����
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(-45.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if((pInputKeyboard->GetKeyPress(nLeft) && pInputKeyboard->GetKeyPress(nDown)) ) //����
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(-135.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nUp) )
	{
		m_rotTarget.y = rotCamera.y;
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nDown) )
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(180.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nLeft) )
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(-90.0f);
		if( m_rotTarget.y < -D3DX_PI)
		{
			m_rotTarget.y += D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}
	else if(pInputKeyboard->GetKeyPress(nRight) )
	{
		m_rotTarget.y = rotCamera.y + D3DXToRadian(90.0f);
		if( m_rotTarget.y > D3DX_PI)
		{
			m_rotTarget.y -= D3DX_PI * 2.0f;
		}
		isKeyPressed = true;
	}

	if(isKeyPressed == true)
	{
		//�ړ������̏�����
		m_move = D3DXVECTOR3( m_speed, 0.0f, m_speed);

		//���v���A�܂��͋t���v�������߂�
		m_rotAngle =  Get2VecRotAngle( m_rot, m_rotTarget);
	}

	//��]����
	m_rotAngle.y *= 0.999f;

	//���̉�]�ʒu�ɓ���������
	float diff = abs(m_rot.y - m_rotTarget.y);
	if( diff > D3DX_PI)
	{
		diff -= D3DX_PI*2;
	}

	if(diff < VALUE_ROTATE)
	{
		m_rot.y = m_rotTarget.y;
		m_rotAngle.y = 0;
	}
	else //���̉�]�ʒu�ɂ܂��������ĂȂ�
	{
		m_rot.y += m_rotAngle.y;

		//���f���p�x�C��
		if( m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI*2;
		}
		else if(m_rot.y <= -D3DX_PI)
		{
			m_rot.y += D3DX_PI*2;
		}
	}	


	//��]���Ă��Ȃ���
	if( m_rotAngle.y == 0)
	{
		//�ړ�
		m_pos.x += m_move.x * sinf( m_rot.y);
		m_pos.z += m_move.z * cosf( m_rot.y);

		//��������
		m_move -= m_move * 0.25f;	
	}
}


D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

D3DXVECTOR3 CSceneX::GetSize(void)
{
	return m_size;
}
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}