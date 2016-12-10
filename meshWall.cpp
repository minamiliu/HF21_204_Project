//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene3D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "meshWall.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//============================================
// �}�N����`
//============================================

#define TEXTURENAME "data/TEXTURE/wall000.jpg"


//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMeshWall::CMeshWall()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMeshWall::~CMeshWall()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CMeshWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CScene3D::Init( pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);
	return S_OK;
}
void CMeshWall::Uninit(void)
{
	CScene3D::Uninit();
}

void CMeshWall::Update(void)
{
	
}

void CMeshWall::Draw(void)
{
	CScene3D::Draw();
}

CMeshWall *CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CMeshWall *pMeshWall;
	pMeshWall = new CMeshWall;

	rot.x = D3DXToRadian(90.0f); //�ǂ𗧂Ă�

	pMeshWall->Init(pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);
	
	return pMeshWall;
}

bool CMeshWall::HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint)
{
	return CScene3D::HitCheck( tNowPos, tNextPos, wall_nor, HitPoint);
}
