//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "trashGameExplosion.h"
#include "debugproc.h"

//============================================
// �}�N����`
//============================================

#define TEXTURE_EXPLOSION "data/TEXTURE/explosion000.png"
#define	TEX_PATTERN_DIVIDE_X		(8)												// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
#define	TIME_CHANGE_PATTERN			(10)											// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)
//============================================
//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTrashGameExplosion::CTrashGameExplosion()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTrashGameExplosion::~CTrashGameExplosion()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CTrashGameExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_nAnimCnt = 0;
	m_nPatternAnim = 0;
	ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y), D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTrashGameExplosion::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTrashGameExplosion::Update(void)
{
	CScene2D::Update();
	//�����A�j���[�V����
		m_nAnimCnt++;
		if((m_nAnimCnt % TIME_CHANGE_PATTERN) == 0)
		{
			if( m_nPatternAnim == ( NUM_ANIM_PATTERN -1) )
			{
				//g_explosion[nCntExplosion].bUse = false;//���g�p�ɕύX
				//CScene2D::Uninit();
				this->Uninit();
				return;
			}
			// �p�^�[���̐؂�ւ�
			m_nPatternAnim = (m_nPatternAnim + 1) % NUM_ANIM_PATTERN;
			ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),
												D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
		}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTrashGameExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CTrashGameExplosion *CTrashGameExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrashGameExplosion *pTrashBox2D;
	pTrashBox2D = new CTrashGameExplosion;
	pTrashBox2D->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pTrashBox2D->Load( TEXTURE_EXPLOSION);
	
	return pTrashBox2D;
}


