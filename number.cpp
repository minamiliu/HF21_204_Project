//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: bullet2D.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/11
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"


//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/number000.png"

#define	TEX_PATTERN_DIVIDE_X		(10)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
//#define	TIME_CHANGE_PATTERN			(5)								// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CNumber::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta)
{
	m_nMaxKeta = maxKeta;
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;

	m_ppPolygon = new CScene2D*[maxKeta];

	//������
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = new CScene2D;
		m_ppPolygon[cntKeta]->Init( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		tmpPos.x -= ketaSize.x;
	}

	//�^�C�}�[��������
	m_nCntFrame = 0;
	m_nCntTime = 0;
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CNumber::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//�������̔j��
		m_ppPolygon[cntKeta]->Uninit();
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;
	
	//number�{�̂̔j��
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CNumber::Update(void)
{
	m_nCntFrame++;

	if( m_nCntFrame >= 60)
	{
		m_nCntFrame = 0;
		m_nCntTime++;
		this->SetNumber(m_nCntTime);
	}

	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		m_ppPolygon[nKeta]->Draw();
	}
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	pNumber->Init(pos, size, 6);

	//�e�N�X�`���̓ǂݍ���
	pNumber->Load();

	for(int cntKeta = 0; cntKeta < pNumber->m_nMaxKeta; cntKeta++)
	{
		//�e�N�X�`���̊��蓖��
		pNumber->m_ppPolygon[cntKeta]->BindTexture( m_pTexture);
	}
	
	return pNumber;
}

//=============================================================================
//
//=============================================================================
HRESULT CNumber::Load(void)
{
	if( m_pTexture == NULL)
	{
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, TEXTURENAME, &m_pTexture);
	}

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CNumber::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//
//=============================================================================
void CNumber::SetNumber(const int score)
{
	int number;

	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		//��ԉE�̐��������
		number = int(score % (int)powf( 10.0f, float(nKeta+1)) / powf( 10.0f, float(nKeta)));

		//�e�N�X�`�������炷
		m_ppPolygon[nKeta]->ChangeTextureAnime( number, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), D3DXVECTOR2( TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));
	}
}

