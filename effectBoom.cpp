//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: bg.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/07
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "effectBoom.h"
#include "effect3D.h"
//============================================
// �}�N����`
//============================================

//=============================================================================
// �\���̒�`
//=============================================================================
D3DXCOLOR CEffectBoom::m_paraColor[] =
{
	WHITE(1.0f),
	RED(1.0f),
	ORANGE(1.0f),
	YELLOW(1.0f),
	GREEN(1.0f),
	SYAN(1.0f),	
	BLUE(1.0f),	
	MASENTA(1.0f),	
	PINK(1.0f),
	PURPLE(1.0f),
	LIME(1.0f),
	SUN(1.0f),	
	SKY(1.0f),
	BIAGE(1.0f),
};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CEffectBoom::CEffectBoom() : CScene(LAYER_EFFECT)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffectBoom::~CEffectBoom()
{
	
}


//=============================================================================
// �w�i�̏���������
//=============================================================================
HRESULT CEffectBoom::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed)
{	
	m_pos = pos;
	m_size = size;
	m_fSpeed = speed;

	float fAngle = D3DX_PI*2 / MAX_EFFECT;
	for(int cntEffect = 0; cntEffect < MAX_EFFECT; cntEffect++)
	{	
		//start
		m_posNow[cntEffect] = pos;

		//Goal
		m_posGoal[cntEffect].x = pos.x + m_size.x * cosf(fAngle * cntEffect);
		m_posGoal[cntEffect].z = pos.z + m_size.z * sinf(fAngle * cntEffect);
		m_posGoal[cntEffect].y = size.y;

		//front vector
		D3DXVECTOR3 vec = m_posGoal[cntEffect] - pos;
		D3DXVec3Normalize(&vec, &vec);
		m_front[cntEffect] = vec * speed;
	}

	return S_OK;
}

//=============================================================================
// �w�i�̏I������
//=============================================================================
void CEffectBoom::Uninit(void)
{
	//�Q�d�Ǘ��̂Ȃ��悤�ɒ���

	//�I�u�W�F�N�g�̔j��
	Release();
}


//=============================================================================
// �w�i�̍X�V����
//=============================================================================
void CEffectBoom::Update(void)
{
	bool bGoal = false;

	//�Q�d�Ǘ��̂Ȃ��悤�ɒ���
	for(int cntEffect = 0; cntEffect < MAX_EFFECT; cntEffect++)
	{
		//�G�t�F�N�g
		CEffect3D::Create( m_posNow[cntEffect], D3DXVECTOR2( 15.0f, 15.0f), CEffect3D::TYPE_MARU, m_paraColor[cntEffect], 0.125f);

		m_posNow[cntEffect] += m_front[cntEffect];

		if( m_posNow[cntEffect] == m_posGoal[cntEffect] || m_posNow[cntEffect].y >= m_posGoal[cntEffect].y)
		{
			bGoal = true;
		}
	}

	if(bGoal == true) this->Uninit();
}

//=============================================================================
// �w�i�̕`�揈��
//=============================================================================
void CEffectBoom::Draw(void)
{
	//�Q�d�Ǘ��̂Ȃ��悤�ɒ���
}

//=============================================================================
// �w�i�̐�������
//=============================================================================
CEffectBoom *CEffectBoom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed)
{
	CEffectBoom *pEffect;
	pEffect = new CEffectBoom;
	pEffect->Init(pos, size, speed);

	return pEffect;
}
//=============================================================================
//���W���擾
//=============================================================================
D3DXVECTOR3 CEffectBoom::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
//�T�C�Y���擾
//=============================================================================
D3DXVECTOR3 CEffectBoom::GetSize(void)
{
	return m_size;
}
//=============================================================================
//���W��ݒ�
//=============================================================================
void CEffectBoom::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}