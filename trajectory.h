//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: trajectory.h
// �쐬��:		 HAL�����Q�[���w�ȁ@�R�ƌ[��
// �쐬��:       2016/10/21
//
//============================================

#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene2D.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CTrajectory : public CScene2D
{
public:

	CTrajectory();
	virtual ~CTrajectory();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrajectory *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	

private:
	int m_nTrajectoryCnt;
};

#endif
