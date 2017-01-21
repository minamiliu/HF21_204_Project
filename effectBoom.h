//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: effectBoom.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/20
//
//============================================

#ifndef _EFFECTBOOM_H_
#define _EFFECTBOOM_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================
#define MAX_EFFECT (14)
//============================================
//�O���錾
//============================================
class CEffect3D;

//============================================
//�\���̒�`
//============================================
class CEffectBoom : public CScene
{
public:

	CEffectBoom();
	virtual ~CEffectBoom();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);

	static CEffectBoom *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed);

private:
	float m_fSpeed;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;

	D3DXVECTOR3 m_posNow[MAX_EFFECT];
	D3DXVECTOR3 m_posGoal[MAX_EFFECT];
	D3DXVECTOR3 m_front[MAX_EFFECT];

	static D3DXCOLOR m_paraColor[];
};

#endif
