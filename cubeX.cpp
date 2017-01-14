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
#include "cubeX.h"
#include "manager.h"
#include "renderer.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME_1X1 "data/MODEL/cashier.x"
#define MODEL_FILENAME_1X2 "data/MODEL/shelf200.x"
#define MODEL_FILENAME_1X4 "data/MODEL/shelf400.x"

//=============================================================================
// �\���̒�`
//=============================================================================


//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9	CCubeX::m_pTexture		[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			CCubeX::m_pD3DXMesh		[TYPE_MAX] = {};		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		CCubeX::m_pD3DXBuffMat	[TYPE_MAX] = {};		// �}�e���A�����ւ̃|�C���^
DWORD				CCubeX::m_nNumMat		[TYPE_MAX] = {};		// �}�e���A�����̐�

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCubeX::CCubeX()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCubeX::~CCubeX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CCubeX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen, TYPE type)
{
	m_sideLen = sideLen;
	m_type = type;
	
	switch( type)
	{
	case TYPE_1X1:
		CSceneX::Init( pos, rot, scl);
		break;

	case TYPE_1X2:
		CSceneX::Init( pos, rot, scl);
		break;

	case TYPE_1X4:
		CSceneX::Init( pos, rot, scl);
		break;
	}
	
	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CCubeX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CCubeX::Update(void)
{
	
}

//=============================================================================
//
//=============================================================================
void CCubeX::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CCubeX *CCubeX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 sideLen, TYPE type)
{
	CCubeX *pCube;
	pCube = new CCubeX;
	pCube->Init(pos, rot, D3DXVECTOR3( 1.0f, 1.0f, 1.0f), sideLen, type);

	//Xfile�̊��蓖��
	pCube->BindXfile( m_pTexture[type], m_pD3DXMesh[type], m_pD3DXBuffMat[type], m_nNumMat[type]);

	return pCube;
}

//=============================================================================
//
//=============================================================================
D3DXVECTOR3 CCubeX::GetSideMin(void)
{
	D3DXVECTOR3 sideMin = this->GetPosition();
	sideMin.x -= m_sideLen.x / 2;
	sideMin.y -= m_sideLen.y / 2;
	sideMin.z -= m_sideLen.z / 2;

	return sideMin;
}

//=============================================================================
//
//=============================================================================
D3DXVECTOR3 CCubeX::GetSideMax(void)
{
	D3DXVECTOR3 sideMax = this->GetPosition();
	sideMax.x += m_sideLen.x / 2;
	sideMax.y += m_sideLen.y / 2;
	sideMax.z += m_sideLen.z / 2;

	return sideMax;
}

//=============================================================================
//
//=============================================================================
float CCubeX::GetDistanceBoxPoint(D3DXVECTOR3 point)
{
	float distance = 0.0f;   // �����ׂ̂���̒l���i�[

	D3DXVECTOR3 sideMin = GetSideMin();
	D3DXVECTOR3 sideMax = GetSideMax();
	
	for(int xyz = 0; xyz < 3; xyz++)
	{
		float tpoint;
		float min, max; 

		switch( xyz)
		{
		case 0:
			tpoint = point.x;
			min = sideMin.x;
			max = sideMax.x;
			break;

		case 1:
			tpoint = point.y;
			min = sideMin.y;
			max = sideMax.y;
			break;

		case 2:
			tpoint = point.z;
			min = sideMin.z;
			max = sideMax.z;
			break;
		}

		//�������v�Z
		if( tpoint < min)
		{
			distance += (tpoint - min) * (tpoint - min);
		}
		if( tpoint > max)
		{
			distance += (tpoint - max) * (tpoint - max);
		}
	}

	distance = sqrtf(distance);

	return distance;
}

//=============================================================================
//
//=============================================================================
CCubeX::TYPE CCubeX::GetType(void)
{
	return m_type;
}

//=============================================================================
//
//=============================================================================
HRESULT CCubeX::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	for(int cntType = 0; cntType < TYPE_MAX; cntType++)
	{
		LPCSTR strFileName;
		switch( cntType)
		{
		case TYPE_1X1:
			strFileName = MODEL_FILENAME_1X1;
			break;

		case TYPE_1X2:
			strFileName = MODEL_FILENAME_1X2;
			break;

		case TYPE_1X4:
			strFileName = MODEL_FILENAME_1X4;
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
//
//=============================================================================
void CCubeX::Unload(void)
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