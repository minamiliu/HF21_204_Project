//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: score.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/30
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "number.h"


//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/number001.png"

#define	TEX_PATTERN_DIVIDE_X		(10)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)
#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)		// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)

#define	NUM_ANIM_PATTERN			(TEX_PATTERN_DIVIDE_X*TEX_PATTERN_DIVIDE_Y)	// �A�j���[�V�����̃p�^�[����(X�����������~Y����������)
//#define	TIME_CHANGE_PATTERN			(5)								// �A�j���[�V�����̐؂�ւ��^�C�~���O(�t���[����)

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore()
{
	m_ppPolygon = NULL;
	m_pTexture = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScore::Init(void)
{
	return S_OK;
}
HRESULT CScore::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col)
{
	//�����l��ݒ�
	m_nMaxKeta = maxKeta;
	m_nValue = 0;
	m_pos = numberPos;
	m_size = numberSize;

	//Number�|�C���^�[�z��̐���
	m_ppPolygon = new CNumber*[maxKeta];

	//�X�^�[�g�ʒu(�E)�ƌ��T�C�Y�̌v�Z
	D3DXVECTOR3 rightPos = numberPos;
	D3DXVECTOR3 ketaSize = numberSize;
	ketaSize.x /= maxKeta;
	rightPos.x = numberPos.x + ketaSize.x * (maxKeta - 1) / 2.0f;
	
	//������Number�̐���
	D3DXVECTOR3 tmpPos = rightPos;
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta] = CNumber::Create( tmpPos , ketaSize, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y));
		tmpPos.x -= ketaSize.x;
	}

	//�F��ݒ�
	SetColor( col);

	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScore::Uninit(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//�������̔j��
		m_ppPolygon[cntKeta]->Uninit();
	}

	delete[] m_ppPolygon;
	m_ppPolygon = NULL;

	//�e�N�X�`���̔j��
	this->Unload();
	
	//�I�u�W�F�N�g�̔j��
	Release();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScore::Update(void)
{
	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		m_ppPolygon[nKeta]->Draw();
	}
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init(pos, size, maxKeta, col);

	//�e�N�X�`���̓ǂݍ���
	pScore->Load();

	//�����̃e�N�X�`���̊��蓖��
	pScore->BindAllTexture();
	
	return pScore;
}

//=============================================================================
//
//=============================================================================
HRESULT CScore::Load(void)
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
void CScore::Unload(void)
{
	//�e�N�X�`���̔j��
	if( m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//���������̂܂ܕ\������
//=============================================================================
void CScore::SetScore(int score)
{
	int number;

	//�͈̓`�F�b�N
	int maxScore = powf( 10.0f, m_nMaxKeta) -1;
	if(score >  maxScore) score = maxScore;
	else if(score < 0) score = 0;

	//�l���X�V
	m_nValue = score;

	for(int nKeta = 0; nKeta < m_nMaxKeta; nKeta++)
	{
		//��ԉE�̐��������
		number = int(score % (int)powf( 10.0f, float(nKeta+1)) / powf( 10.0f, float(nKeta)));

		//�e�N�X�`�������炷
		m_ppPolygon[nKeta]->ChangeTextureAnime( number, D3DXVECTOR2( TEX_PATTERN_SIZE_X, TEX_PATTERN_SIZE_Y), D3DXVECTOR2( TEX_PATTERN_DIVIDE_X, TEX_PATTERN_DIVIDE_Y));
	}
}

//=============================================================================
//�����̃e�N�X�`���̊��蓖��
//=============================================================================
void CScore::BindAllTexture(void)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		//�e�N�X�`���̊��蓖��
		m_ppPolygon[cntKeta]->BindTexture( m_pTexture);
	}
}

//=============================================================================
//�S���̐F����C�ɕύX
//=============================================================================
void CScore::SetColor(const D3DXCOLOR &col)
{
	for(int cntKeta = 0; cntKeta < m_nMaxKeta; cntKeta++)
	{
		m_ppPolygon[cntKeta]->SetColor( col);
	}
}

//=============================================================================
//���_���グ��
//=============================================================================
void CScore::AddScore(int score)
{
	m_nValue += score;
	SetScore( m_nValue);
}
//=============================================================================
//���W���擾
//=============================================================================
D3DXVECTOR3 CScore::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//�T�C�Y���擾
//=============================================================================
D3DXVECTOR3 CScore::GetSize(void)
{
	return m_size;
}