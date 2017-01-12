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
#include "bookbox.h"

//============================================
// �}�N����`
//============================================
#define MODEL_FILENAME_BOOKBOX "data/MODEL/booklack.x"
#define MODEL_FILENAME_TOYBOX "data/MODEL/cube200.x"
#define MODEL_FILENAME_1X4 "data/MODEL/tv_set.x"

//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBookBox::CBookBox()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBookBox::~CBookBox()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CBookBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type)
{
	//m_sideLen = sideLen;
	
	switch( type)
	{
	case TYPE_BOOKLACK:
		CSceneX::Init( pos, rot, scl,MODEL_FILENAME_BOOKBOX);
		SetObjType(OBJTYPE_TOYBOX);
		break;

	case TYPE_TOYBOX:
		CSceneX::Init( pos, rot, scl, MODEL_FILENAME_TOYBOX);
		SetObjType(OBJTYPE_TOYBOX);
		break;

	case TYPE_TVSET:
		CSceneX::Init( pos, rot, scl, MODEL_FILENAME_1X4);
		SetObjType(OBJTYPE_TOYBOX);
		break;
	}
	SetPosition(pos);
	return S_OK;
}

//=============================================================================
//
//=============================================================================
void CBookBox::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CBookBox::Update(void)
{

}

//=============================================================================
//
//=============================================================================
void CBookBox::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CBookBox *CBookBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,  TYPE type)
{
	CBookBox *pCube;
	pCube = new CBookBox;
	pCube->Init(pos, rot, D3DXVECTOR3( 10.0f, 10.0f, 10.0f),  type);
	
	return pCube;
}

//D3DXVECTOR3 CBookBox::GetSideMin(void)
//{
//	D3DXVECTOR3 sideMin = this->GetPosition();
//	sideMin.x -= m_sideLen.x / 2;
//	sideMin.y -= m_sideLen.y / 2;
//	sideMin.z -= m_sideLen.z / 2;
//
//	return sideMin;
//}
//
//D3DXVECTOR3 CBookBox::GetSideMax(void)
//{
//	D3DXVECTOR3 sideMax = this->GetPosition();
//	sideMax.x += m_sideLen.x / 2;
//	sideMax.y += m_sideLen.y / 2;
//	sideMax.z += m_sideLen.z / 2;
//
//	return sideMax;
//}
//
//float CBookBox::GetDistanceBoxPoint(D3DXVECTOR3 point)
//{
//	float distance = 0.0f;   // �����ׂ̂���̒l���i�[
//
//	D3DXVECTOR3 sideMin = GetSideMin();
//	D3DXVECTOR3 sideMax = GetSideMax();
//	
//	for(int xyz = 0; xyz < 3; xyz++)
//	{
//		float tpoint;
//		float min, max; 
//
//		switch( xyz)
//		{
//		case 0:
//			tpoint = point.x;
//			min = sideMin.x;
//			max = sideMax.x;
//			break;
//
//		case 1:
//			tpoint = point.y;
//			min = sideMin.y;
//			max = sideMax.y;
//			break;
//
//		case 2:
//			tpoint = point.z;
//			min = sideMin.z;
//			max = sideMax.z;
//			break;
//		}
//
//		//�������v�Z
//		if( tpoint < min)
//		{
//			distance += (tpoint - min) * (tpoint - min);
//		}
//		if( tpoint > max)
//		{
//			distance += (tpoint - max) * (tpoint - max);
//		}
//	}
//
//	distance = sqrtf(distance);
//
//	return distance;
//}