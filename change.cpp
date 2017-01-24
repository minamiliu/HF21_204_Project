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
#include "change.h"
#include "trashGameExplosion.h"
#include "effectBG.h"
#include "scene2D.h"
#include "changeTex.h"
#include "sound.h"

//============================================
// �}�N����`
//============================================
#define TEXTURE_BG "data/TEXTURE/effectBG.png"

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
CScene2D *CChange::m_pChamgeBg = NULL;
CTrashGameExplosion *pExplosion = NULL;
CChangeTex *pPlayer = NULL;
CChangeTex *pAnimal = NULL;
CChangeTex *pAnimalPlayer = NULL;
bool CChange::m_bAnimalPlayerFlag = false;
bool CChange::m_bState = true;
int CChange::changeCnt = 0;
CEffectBG *pEffect = NULL;
LPCSTR CChange::m_StrAnimalPlayerFileName;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CChange::CChange()
{
	m_pChamgeBg = NULL;
	pPlayer = NULL;
	pAnimal = NULL;
	pAnimalPlayer = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CChange::~CChange()
{
	
}

//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CChange::Init( LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName)
{
	pEffect = CEffectBG::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT/2, 0.0f));	
	//pAnimalPlayer = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(300,300,0),strAnimalPlayerFileName);
	pPlayer = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(300,300,0),strPlayerFileName);
	pAnimal = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH+100, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(300,300,0),strAnimalFileName);
	
	changeCnt = 0;
	m_bState = true;
	m_bAnimalPlayerFlag = false;
	pAnimalPlayer = NULL;
	m_StrAnimalPlayerFileName = strAnimalPlayerFileName;

	//SE
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_SE_CHANGE);
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CChange::Uninit(void)
{
	pExplosion = NULL;

	//pAnimalPlayer->Uninit();
	pAnimalPlayer = NULL;

	pEffect->Uninit();
	pEffect = NULL;
	//�I�u�W�F�N�g�̔j��
	Release();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CChange::Update(void)
{
	changeCnt++;
	//�����G�̍X�V
	D3DXVECTOR3 pos;
	if(pAnimal != NULL)
	{
		pos = pAnimal->GetPosition();
		pos.x-=8;
		pAnimal->SetPosition(pos);
	}
	
	if(pAnimal != NULL && pPlayer != NULL)
	{
		D3DXVECTOR3 playerPos = pPlayer->GetPosition();
		if(pos.x <= playerPos.x)
		{
			pPlayer->Uninit();
			pPlayer = NULL;
			pAnimal->Uninit();
			pAnimal = NULL;
			pExplosion = CTrashGameExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3( 400.0f, 400.0f, 0.0f));
			pExplosion->ChangeTextureAnime(0, D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),
									D3DXVECTOR2(TEX_PATTERN_DIVIDE_X,TEX_PATTERN_DIVIDE_Y));
			changeCnt = 0;
		}
	}

	if(pExplosion != NULL)
	{
		if(changeCnt == 8 * 10)
		{
			m_bAnimalPlayerFlag = true;
			pAnimalPlayer = CChangeTex::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(160,300,0),m_StrAnimalPlayerFileName);
		}
	}

	if(m_bAnimalPlayerFlag == true)
	{
		D3DXVECTOR3 animalPlayerPos = pAnimalPlayer->GetPosition();
		animalPlayerPos.x-=8;
		pAnimalPlayer->SetPosition(animalPlayerPos);
		if(animalPlayerPos.x  <= -100)
		{
			m_bState = false;
			if(pAnimalPlayer != NULL)
			{
				pAnimalPlayer->Uninit();
			}
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CChange::Draw(void)
{

}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CChange *CChange::Create(LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName)
{
	CChange *pChange;
	pChange = new CChange;
	pChange->Init(strPlayerFileName, strAnimalFileName,strAnimalPlayerFileName);
	
	return pChange;
}
//�ϐg���o�̏�Ԃ�Ԃ�
bool CChange::GetState(void)
{
	return m_bState;
}

void CChange::changeState(void)
{
	if(m_bState == true)
	{
		m_bState = false;
	}
	else if(m_bState == false)
	{
		m_bState = true;
	}
}

D3DXVECTOR3 CChange::GetPosition(void)
{
	return D3DXVECTOR3(0,0,0);
}
D3DXVECTOR3 CChange::GetSize(void)
{
	return D3DXVECTOR3(0,0,0);
}
void CChange::SetPosition(D3DXVECTOR3 pos)
{

}