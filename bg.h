//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: bg.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/07
//
//============================================

#ifndef _BG_H_
#define _BG_H_

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
class CBg : public CScene2D
{
public:

	CBg();
	virtual ~CBg();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName, float speed);

private:
	float m_fSpeed;
};

#endif
