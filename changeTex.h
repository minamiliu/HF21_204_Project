//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _CHANGETEX_H_
#define _CHANGETEX_H_

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
class CChangeTex : public CScene2D
{
public:

	CChangeTex();
	virtual ~CChangeTex();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CChangeTex *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName);
private:

};

#endif
