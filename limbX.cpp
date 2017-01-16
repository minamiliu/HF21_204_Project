//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: limbX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/16
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "limbX.h"
#include "renderer.h"
#include "manager.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME_L_HAND	"data/MODEL/mom_L_hand.x"
#define MODEL_FILENAME_R_HAND	"data/MODEL/mom_R_hand.x"
#define MODEL_FILENAME_L_FOOT	"data/MODEL/mom_L_foot.x"
#define MODEL_FILENAME_R_FOOT	"data/MODEL/mom_R_foot.x"
#define MAX_MOTION (2)

//=============================================================================
// �\���̒�`
//=============================================================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
CLimbX::MOTION *CLimbX::m_pMotionPara = NULL;
LPDIRECT3DTEXTURE9	CLimbX::m_pTexture		[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			CLimbX::m_pD3DXMesh		[TYPE_MAX] = {};		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		CLimbX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// �}�e���A�����ւ̃|�C���^
DWORD				CLimbX::m_nNumMat		[TYPE_MAX] = {};		// �}�e���A�����̐�

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CLimbX::CLimbX()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CLimbX::~CLimbX()
{

}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CLimbX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	//���[�V����
	m_pMotionPara = new MOTION[MAX_MOTION];
	
	m_pMotionPara[0].nFrame = 30;
	m_pMotionPara[0].rotX = D3DXToRadian(-60.0f);

	m_pMotionPara[1].nFrame = 30;
	m_pMotionPara[1].rotX = D3DXToRadian(60.0f);

	//TYPE���Ƃ̏�����
	LPCSTR strFileName;
	switch(type)
	{
	case TYPE_L_HAND:
		strFileName = MODEL_FILENAME_L_HAND;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( 8, -15, 0);
		m_nMotionNow = 0;
		break;
	case TYPE_R_HAND:
		strFileName = MODEL_FILENAME_R_HAND;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(-30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( -8, -15, 0);
		m_nMotionNow = 1;
		break;
	case TYPE_L_FOOT:
		strFileName = MODEL_FILENAME_L_FOOT;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(-30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( 4, -35, 0);
		m_nMotionNow = 1;
		break;
	case TYPE_R_FOOT:
		strFileName = MODEL_FILENAME_R_FOOT;
		m_rotLocal = D3DXVECTOR3( D3DXToRadian(30.0f), 0.0f, 0.0f);
		m_posLocal = D3DXVECTOR3( -4, -35, 0);
		m_nMotionNow = 0;
		break;
	}

	//�����ݒ�
	D3DXVECTOR3 tPos = pos + m_posLocal;
	D3DXVECTOR3 tRot = rot + m_rotLocal;
	D3DXVECTOR3 tScl = scl;
	CPartX::Init( tPos, tRot, tScl);

	m_type = type;
	m_nCntFrame = 0;
	m_rotXTurn = m_pMotionPara[m_nMotionNow].rotX / m_pMotionPara[m_nMotionNow].nFrame;
	

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CLimbX::Uninit(void)
{
	CPartX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CLimbX::Update(void)
{
	//CDebugProc::Print("\nposX = %f\n", m_pos.x);
	//CDebugProc::Print("posZ = %f\n", m_pos.z);
	//CDebugProc::Print("rotY = %f\n", m_rot.y);

	//���[�J�����W�̍X�V
	D3DXVECTOR3 tPos = this->GetPosition();
	tPos.x +=  m_posLocal.x * sinf(this->GetRot().y + D3DX_PI / 2.0f);
	tPos.z +=  m_posLocal.x * cosf(this->GetRot().y + D3DX_PI / 2.0f);
	tPos.y += m_posLocal.y;
	this->SetPosition( tPos);

	//����
	D3DXVECTOR3 tRot = this->GetRot();
	m_rotLocal.x += m_rotXTurn;
	tRot += m_rotLocal;
	this->SetRot( tRot);

	//���[�V�����X�V����
	m_nCntFrame++;
	if( m_nCntFrame >= m_pMotionPara[m_nMotionNow].nFrame)
	{
		m_nMotionNow = (m_nMotionNow + 1) % MAX_MOTION;
		m_rotXTurn = m_pMotionPara[m_nMotionNow].rotX / m_pMotionPara[m_nMotionNow].nFrame;
		m_nCntFrame = 0;
	}
}

//=============================================================================
//
//=============================================================================
void CLimbX::Draw(void)
{
	CPartX::Draw();
}

//=============================================================================
//
//=============================================================================
CLimbX *CLimbX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CLimbX *pSceneX;
	pSceneX = new CLimbX;
	pSceneX->Init(pos, rot, scl, type);
	
	//X�t�@�C���̊��蓖��
	pSceneX->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pSceneX;
}

//=============================================================================
//XFILE�̃��[�h
//=============================================================================
HRESULT CLimbX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_L_HAND:
			strFileName = MODEL_FILENAME_L_HAND;
			break;
		case TYPE_R_HAND:
			strFileName = MODEL_FILENAME_R_HAND;
			break;
		case TYPE_L_FOOT:
			strFileName = MODEL_FILENAME_L_FOOT;
			break;
		case TYPE_R_FOOT:
			strFileName = MODEL_FILENAME_R_FOOT;
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
void CLimbX::Unload(void)
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
