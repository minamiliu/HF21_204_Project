//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: enemyX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/12
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "enemyX.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "collision.h"
#include "shadow.h"
#include "limbX.h"

//============================================
// �}�N����`
//============================================
#define MODEL_ENEMY000 "data/MODEL/enemy_body.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// ��]��
#define MAX_MOTION (4)

//=============================================================================
// �\���̒�`
//=============================================================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CEnemyX::MOTION *CEnemyX::m_pMotionPara = NULL;
LPDIRECT3DTEXTURE9	CEnemyX::m_pTexture		[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			CEnemyX::m_pD3DXMesh	[TYPE_MAX] = {};		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		CEnemyX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// �}�e���A�����ւ̃|�C���^
DWORD				CEnemyX::m_nNumMat		[TYPE_MAX] = {};		// �}�e���A�����̐�

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEnemyX::CEnemyX()
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
CEnemyX::~CEnemyX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CEnemyX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	CSceneX::Init( pos, rot, scl);
	SetObjType( OBJTYPE_L_ENEMY);

	m_nCntFrame = 0;
	m_nMotionNow = 0;

	m_pMotionPara = new MOTION[MAX_MOTION];

	m_pMotionPara[0].nFrame = 60;
	m_pMotionPara[0].front = D3DXVECTOR3( 100.0f, 0.0f, 0.0f);
	m_pMotionPara[0].rotY = 0.0f;
	
	m_pMotionPara[1].nFrame = 30;
	m_pMotionPara[1].front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_pMotionPara[1].rotY = D3DX_PI;

	m_pMotionPara[2].nFrame = 60;
	m_pMotionPara[2].front = D3DXVECTOR3( -100.0f, 0.0f, 0.0f);
	m_pMotionPara[2].rotY = 0.0f;

	m_pMotionPara[3].nFrame = 30;
	m_pMotionPara[3].front = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_pMotionPara[3].rotY = D3DX_PI;

	m_front = m_pMotionPara[0].front / m_pMotionPara[0].nFrame;
	m_rotTurn = m_pMotionPara[0].rotY / m_pMotionPara[0].nFrame;

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
void CEnemyX::Uninit(void)
{
	//�葫
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->Uninit();
	}

	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CEnemyX::Update(void)
{
	//�ړ�����
	D3DXVECTOR3 pos = this->GetPosition();
	pos += m_front;
	this->SetPosition( pos);

	//����
	D3DXVECTOR3 rot = this->GetRot();
	rot.y += m_rotTurn;
	if( rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	this->SetRot( rot);

	//���[�V�����X�V����
	m_nCntFrame++;
	if( m_nCntFrame >= m_pMotionPara[m_nMotionNow].nFrame)
	{
		m_nMotionNow = (m_nMotionNow + 1) % MAX_MOTION;
		m_front = m_pMotionPara[m_nMotionNow].front / m_pMotionPara[m_nMotionNow].nFrame;
		m_rotTurn = m_pMotionPara[m_nMotionNow].rotY / m_pMotionPara[m_nMotionNow].nFrame;
		m_nCntFrame = 0;
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
void CEnemyX::Draw(void)
{
	//�葫
	for(int cntLimb = 0; cntLimb < MAX_LIMB; cntLimb++)
	{
		m_pLimb[cntLimb]->Draw();
	}

	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CEnemyX *CEnemyX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CEnemyX *pEnemy;
	pEnemy = new CEnemyX;
	pEnemy->Init(pos, rot, scl);

	//Xfile�̊��蓖��
	pEnemy->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pEnemy;
}

//=============================================================================
// ��]�p�x���擾
//=============================================================================
D3DXVECTOR3 CEnemyX::Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget)
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
		tAngle[cntXYZ] = tAngle[cntXYZ] / fabsf(tAngle[cntXYZ]);

	}

	re.x = tAngle[0];
	re.y = tAngle[1];
	re.z = tAngle[2];

	return re;
}

//=============================================================================
//XFILE�̃��[�h
//=============================================================================
HRESULT CEnemyX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_000:
			strFileName = MODEL_ENEMY000;
			break;
		}

		if( m_pTexture[cntType] == NULL &&
			m_pD3DXMesh[cntType] == NULL &&
			m_pD3DXBuffMat[cntType] == NULL &&
			m_nNumMat[cntType] == 0
			)
		{
			// X�t�@�C���̓ǂݍ���
			if(FAILED(D3DXLoadMeshFromX(
				strFileName,			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
				D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
				pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
				NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				&m_pD3DXBuffMat[cntType],	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
				NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
				&m_nNumMat[cntType],	// D3DXMATERIAL�\���̂̐�
				&m_pD3DXMesh[cntType]	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
				)))
			{
				return E_FAIL;
			}
		
		}
	}

	return S_OK;
}

//=============================================================================
//XFILE�̃A�����[�h
//=============================================================================
void CEnemyX::Unload(void)
{
	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		// �e�N�X�`���̊J��
		if(m_pTexture[cntType] != NULL)
		{
			m_pTexture[cntType]->Release();
			m_pTexture[cntType] = NULL;
		}
		// ���b�V���̊J��
		if(m_pD3DXMesh[cntType] != NULL)
		{
			m_pD3DXMesh[cntType]->Release();
			m_pD3DXMesh[cntType] = NULL;
		}
		// �}�e���A���̊J��
		if(m_pD3DXBuffMat != NULL)
		{
			m_pD3DXBuffMat[cntType]->Release();
			m_pD3DXBuffMat[cntType] = NULL;
		}	
	}

}