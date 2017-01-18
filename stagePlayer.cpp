/*******************************************************************************
* �^�C�g��:		�S����
* �v���O������:	stagePlayer.cpp
* �쐬��:		���ї�Y
* �쐬��:		2016/12/03
********************************************************************************
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "stagePlayer.h"
#include "manager.h"
#include "scene2D.h"
#include "stageBg.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define STAGEPLAYER_TEX_NAME	"data/TEXTURE/�X�e�[�W�p/��i�����j.png"
#define ANIM_PAT_X (4)
#define ANIM_PAT_Y (1)
#define ANIM_CANGE_FRAME (20)
/*******************************************************************************
* �N���X��`
*******************************************************************************/
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX		(4)			// ���_��
#define NUM_POLYGON		(2)			// �|���S����
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


#define MOVE_TIME (60)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �ÓI
//*****************************************************************************
D3DXVECTOR3 CStagePlayer::m_startPos = D3DXVECTOR3(0,0,0);
D3DXVECTOR3 CStagePlayer::m_nextPos = D3DXVECTOR3(0,0,0);
CStagePlayer::STAGE_PLAYER_STATE CStagePlayer::m_state = STATE_NORMAL;
CStagePlayer::STAGE_PLAYER_STATE CStagePlayer::m_oldState = STATE_NORMAL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStagePlayer :: CStagePlayer()
{
	m_time = 0;
	m_animPat = 0;
	m_work = 0;
	m_animCnt = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStagePlayer :: ~CStagePlayer()
{
}
CStagePlayer* CStagePlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 nextPos,D3DXVECTOR3 size)
{
	CStagePlayer *pStagePlayer;
	pStagePlayer = new CStagePlayer;
	pStagePlayer->Init(pos,size);
	
	pStagePlayer->Load(STAGEPLAYER_TEX_NAME);

	m_startPos = pos;
	m_nextPos = nextPos;
	return pStagePlayer;
}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CStagePlayer :: Init(void)
{
	CScene2D::Init();


	return S_OK;
}
//=============================================================================
// �|���S���̏���������(�I�[�o�[���[�h)
//=============================================================================
HRESULT CStagePlayer :: Init(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size);

	CScene2D::SetTexture(ANIM_PAT_X,ANIM_PAT_Y,m_animPat);

	return S_OK;
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CStagePlayer :: Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CStagePlayer :: Update(void)
{
	D3DXVECTOR3 posStagePlayer = GetPosition();
	D3DXVECTOR3 sizeStagePlayer = GetSize();
	m_time++;
	m_animCnt++;
	if((posStagePlayer == m_startPos)||(m_time > MOVE_TIME))//�X�^�[�g�ʒu�ɂ��邩�A���[�u�^�C�����I�[�o�[������
	{
		m_state = STATE_NORMAL;
	}
	if((posStagePlayer == m_startPos)&&(m_time >60))
	{
		m_state = STATE_MOVE;
	}

	if(m_state != m_oldState)//�O�t���[���Ə�Ԃ��������
	{
		m_time = 0;//���Z�b�g
	}

	switch(m_state)
	{
	case STATE_NORMAL:
		if(m_animCnt%ANIM_CANGE_FRAME == 0)
		{
			m_work++;
		}
		//m_animPat = m_work%3;//�Î~���̉��̃A�j���[�V������
		CStageBg::SetScl(false);
		break;
	case STATE_MOVE:
		if(m_time < MOVE_TIME)
		{
			posStagePlayer += ((m_nextPos - m_startPos)/MOVE_TIME);
		}
		if(m_animCnt%ANIM_CANGE_FRAME == 0)
		{
			m_work++;
		}
		//m_animPat = 9+m_work%3;//�Î~���̉��̃A�j���[�V������ + �ړ����̃A�j���[�V������
		CStageBg::SetScl(true);
		break;
	}
	m_animPat = m_work%4;

	CScene2D::SetTexture(ANIM_PAT_X,ANIM_PAT_Y,m_animPat);

	m_oldState = m_state;
	this->CStagePlayer::SetPosition(posStagePlayer);
}
//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CStagePlayer :: Draw(void)
{
	CScene2D::Draw();
}