//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: cubeX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

#ifndef _CUBEX_H_
#define _CUBEX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "sceneX.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CCubeX : public CSceneX
{
public:
	CCubeX();
	virtual ~CCubeX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	float GetDistanceBoxPoint(D3DXVECTOR3 point);

	static CCubeX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 sideLen);

protected:
	D3DXVECTOR3 GetSideMin(void);
	D3DXVECTOR3 GetSideMax(void);

private:
	D3DXVECTOR3 m_sideLen;
};

#endif
