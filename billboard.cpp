//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: billboard.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "billboard.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/tomato.png"

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBillBoard::CBillBoard()
{

}

CBillBoard::CBillBoard(LAYER layer) : CScene3D( layer)
{

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBillBoard::~CBillBoard()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CBillBoard::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CScene3D::Init( pos, D3DXVECTOR3(0,0,0), 1, 1, size.x, size.y, true);
	return S_OK;
}
//=============================================================================
//
//=============================================================================
void CBillBoard::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
//
//=============================================================================
void CBillBoard::Update(void)
{
	
}
//=============================================================================
//
//=============================================================================
void CBillBoard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX *mtxView = CManager::GetCamera()->GetMtxView();

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	CScene3D::Draw(mtxView);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
//
//=============================================================================
CBillBoard *CBillBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CBillBoard *pBoard;
	pBoard = new CBillBoard;

	pBoard->Init(pos, size);

	return pBoard;
}

