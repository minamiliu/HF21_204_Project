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
#include "time.h"


//============================================
// �}�N����`
//============================================

//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTime::CTime()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTime::~CTime()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CTime::Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col)
{
	CScore::Init( numberPos, numberSize, maxKeta, col);
	CScore::SetScore(startTime);

	m_nCntFrame = 0;
	m_nTime = 0;
	m_nTime = startTime;
	m_bCountDown = bCountDown;
	m_useFlag = true;
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTime::Uninit(void)
{
	CScore::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTime::Update(void)
{
	if(m_useFlag == true)
	{
		m_nCntFrame++;

		if( m_nCntFrame >= 60)
		{
			if( m_bCountDown == true)
			{
				if( m_nTime > 0) m_nTime--;
			}
			else
			{
				m_nTime++;
			}

			m_nCntFrame = 0;
			this->SetScore(m_nTime);
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTime::Draw(void)
{
	CScore::Draw();
}

CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col)
{
	CTime *pTime;
	pTime = new CTime;
	pTime->Init(pos, numberSize, maxKeta, startTime, bCountDown, col);

	//�e�N�X�`���̓ǂݍ���
	pTime->Load();

	//�����̃e�N�X�`���̊��蓖��
	pTime->BindAllTexture();
	
	return pTime;
}



bool CTime::TimeUp(void)
{
	if(m_bCountDown == true && m_nTime == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int CTime::GetTime(void)
{
	return m_nTime;
}

void CTime::StopTime(void)
{
	if(m_useFlag == true)
		m_useFlag = false;
	else if(m_useFlag == false)
		m_useFlag = true;
}

bool CTime::GetTimeFlag(void)
{
	return m_useFlag;
}