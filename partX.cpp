//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: partX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/04
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "partX.h"
#include "renderer.h"
#include "manager.h"
#include "playerX.h"

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
CPartX::MOTION *CPartX::m_pMotionPara = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPartX::CPartX()
{
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���f���̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���f���̌���(��])
	m_scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���f���̑傫��(�X�P�[��)

	D3DXMatrixIdentity(&m_mtxWorld);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPartX::~CPartX()
{

}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CPartX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���f���Ɋւ���ϐ��̏�����							
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�

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
	m_pos = pos + m_posLocal;
	m_rot = rot + m_rotLocal;
	m_scl = scl;
	m_type = type;
	m_nCntFrame = 0;
	m_rotXTurn = m_pMotionPara[m_nMotionNow].rotX / m_pMotionPara[m_nMotionNow].nFrame;
	
	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(
		strFileName,			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&m_pD3DXBuffMat,		// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&m_nNumMat,				// D3DXMATERIAL�\���̂̐�
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
HRESULT CPartX::LoadXfile(LPCSTR strFileName)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();


	// ���f���Ɋւ���ϐ��̏�����							
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pD3DXMesh = NULL;		// ���b�V�����ւ̃|�C���^
	m_pD3DXBuffMat = NULL;		// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;			// �}�e���A�����̐�
							// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(
		strFileName,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
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
void CPartX::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���b�V���̊J��
	if (m_pD3DXMesh != NULL)
	{
		m_pD3DXMesh->Release();
		m_pD3DXMesh = NULL;
	}
	// �}�e���A���̊J��
	if (m_pD3DXBuffMat != NULL)
	{
		m_pD3DXBuffMat->Release();
		m_pD3DXBuffMat = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	//Release();
}
//=============================================================================
// X�t�@�C�������蓖�Ă�
//=============================================================================
void CPartX::BindXfile(LPDIRECT3DTEXTURE9	pTexture,		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			pD3DXMesh,			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pD3DXBuffMat,		// �}�e���A�����ւ̃|�C���^
	DWORD				nNumMat
)					// �}�e���A�����̐�
{
	m_pTexture = pTexture;
	m_pD3DXMesh = pD3DXMesh;
	m_pD3DXBuffMat = pD3DXBuffMat;
	m_nNumMat = nNumMat;
}
//=============================================================================
//
//=============================================================================
void CPartX::Update(void)
{
	//CDebugProc::Print("\nposX = %f\n", m_pos.x);
	//CDebugProc::Print("posZ = %f\n", m_pos.z);
	//CDebugProc::Print("rotY = %f\n", m_rot.y);

	//���[�J�����W�̍X�V
	m_pos.x +=  m_posLocal.x * sinf(this->GetRot().y + D3DX_PI / 2.0f);
	m_pos.z +=  m_posLocal.x * cosf(this->GetRot().y + D3DX_PI / 2.0f);
	m_pos.y += m_posLocal.y;

	//����
	m_rotLocal.x += m_rotXTurn;
	m_rot += m_rotLocal;

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
void CPartX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL *)m_pD3DXBuffMat->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
		// �`��
		m_pD3DXMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//
//=============================================================================
CPartX *CPartX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	CPartX *pSceneX;
	pSceneX = new CPartX;
	pSceneX->Init(pos, rot, scl, type);

	return pSceneX;
}

D3DXVECTOR3 CPartX::GetPosition(void)
{
	return m_pos;
}

D3DXVECTOR3 CPartX::GetSize(void)
{
	return m_size;
}
D3DXVECTOR3 CPartX::GetRot(void)
{
	return m_rot;
}

void CPartX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CPartX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CPartX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
