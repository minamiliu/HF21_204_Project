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
#include "renderer.h"
#include "input.h"
#include "trashplayer.h"
#include "debugproc.h"

//============================================
// �}�N����`
//============================================

#define TEXTURE_PLAYER "data/TEXTURE/throwingMother.png"
#define	TEX_PATTERN_DIVIDE_X		(5)												// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)												// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f / TEX_PATTERN_DIVIDE_X)					// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f / TEX_PATTERN_DIVIDE_Y)					// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)
#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X * TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
#define	TIME_CHANGE_PATTERN			(5)											// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)

#define TEXTURE_GORILLA "data/TEXTURE/throwingGorilla.png"
//============================================

LPDIRECT3DTEXTURE9 CTrashPlayer::m_pTexture[2] = {NULL,NULL};

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTrashPlayer::CTrashPlayer()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTrashPlayer::~CTrashPlayer()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CTrashPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_nAnimCnt = 0;
	m_nPatternAnim = 0;
	m_bGorillaMode = false;;
	ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y), D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTrashPlayer::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTrashPlayer::Update(void)
{
	CScene2D::Update();
	if(CManager::GetInputMouse()->GetMouseLeftPress() || m_nPatternAnim >= 3)
	{
		//�A�j���[�V����
		m_nAnimCnt++;
		if((m_nAnimCnt % TIME_CHANGE_PATTERN) == 0)
		{
			//�A�j���[�V������r���Ŏ~�߂�
			if( m_nPatternAnim == (3 -1) )
			{
				return;
			}
			// �p�^�[���̐؂�ւ�
			m_nPatternAnim = (m_nPatternAnim + 1) % NUM_ANIM_PATTERN;
			ChangeTextureAnime(m_nPatternAnim, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y), D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
		}
	}

	//�}�E�X��b������A�j���[�V�������X�V
	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
		m_nPatternAnim = 3;
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTrashPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CTrashPlayer *CTrashPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName)
{
	CTrashPlayer *pTrashBox2D;
	pTrashBox2D = new CTrashPlayer;
	pTrashBox2D->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	//pTrashBox2D->Load( TEXTURE_PLAYER);
	if(strFileName == TEXTURE_PLAYER)
	{
		pTrashBox2D->BindTexture(m_pTexture[0]);
	}
	else if(strFileName == TEXTURE_GORILLA)
	{
		pTrashBox2D->BindTexture(m_pTexture[1]);
	}

	return pTrashBox2D;
}

bool CTrashPlayer::GetGorillaMode(void)
{
	return m_bGorillaMode;
}

void CTrashPlayer::SetGorillaMode(void)
{
	m_bGorillaMode = true;
}

void CTrashPlayer::Load(void)
{
	if(m_pTexture[0] == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice,TEXTURE_PLAYER, &m_pTexture[0]);
	}

	if(m_pTexture[1] == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice,TEXTURE_GORILLA, &m_pTexture[1]);
	}
}