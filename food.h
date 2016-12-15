//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: food.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

#ifndef _FOOD_H_
#define _FOOD_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "billboard.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CFood : public CBillBoard
{
public:

	CFood();
	virtual ~CFood();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFood *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
