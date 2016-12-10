//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: playerX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "cubeX.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME "data/MODEL/cube2.x"

//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCubeX::CCubeX()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCubeX::~CCubeX()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CCubeX::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen)
{
	CSceneX::Init( pos, rot, scl, MODEL_FILENAME);
	m_sideLen = sideLen;
	
	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CCubeX::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CCubeX::Update(void)
{

}

//=============================================================================
//
//=============================================================================
void CCubeX::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CCubeX *CCubeX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen)
{
	CCubeX *pCube;
	pCube = new CCubeX;
	pCube->Init(pos, rot, scl, sideLen);

	return pCube;
}

D3DXVECTOR3 CCubeX::GetSideMin(void)
{
	D3DXVECTOR3 sideMin = this->GetPosition();
	sideMin.x -= m_sideLen.x / 2;
	sideMin.y -= m_sideLen.y / 2;
	sideMin.z -= m_sideLen.z / 2;

	return sideMin;
}

D3DXVECTOR3 CCubeX::GetSideMax(void)
{
	D3DXVECTOR3 sideMax = this->GetPosition();
	sideMax.x += m_sideLen.x / 2;
	sideMax.y += m_sideLen.y / 2;
	sideMax.z += m_sideLen.z / 2;

	return sideMax;
}

float CCubeX::GetDistanceBoxPoint(D3DXVECTOR3 point)
{
	float distance = 0.0f;   // �����ׂ̂���̒l���i�[

	D3DXVECTOR3 sideMin = GetSideMin();
	D3DXVECTOR3 sideMax = GetSideMax();
	
	for(int xyz = 0; xyz < 3; xyz++)
	{
		float tpoint;
		float min, max; 

		switch( xyz)
		{
		case 0:
			tpoint = point.x;
			min = sideMin.x;
			max = sideMax.x;
			break;

		case 1:
			tpoint = point.y;
			min = sideMin.y;
			max = sideMax.y;
			break;

		case 2:
			tpoint = point.z;
			min = sideMin.z;
			max = sideMax.z;
			break;
		}

		//�������v�Z
		if( tpoint < min)
		{
			distance += (tpoint - min) * (tpoint - min);
		}
		if( tpoint > max)
		{
			distance += (tpoint - max) * (tpoint - max);
		}
	}

	distance = sqrtf(distance);

	return distance;
}