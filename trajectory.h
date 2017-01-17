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
	typedef enum
	{
		TJRTYPE_NORMAL = 0,
		TJRTYPE_GORILLA,
		TJRTYPE_ALLDIRECTION,
		TJRTYPE_MAX
	}TJRTYPE;
	CTrajectory();
	virtual ~CTrajectory();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Load(void);
	static CTrajectory *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,TJRTYPE type,float angle);
	

private:
	int m_nTrajectoryCnt;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	float m_alpha;
	TJRTYPE m_tjrType;
	float m_angle;
};

#endif
