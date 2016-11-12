//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: bullet.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/11
//
//============================================

#ifndef _BULLET2D_H_
#define _BULLET2D_H_

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

class CBullet2D : public CScene2D
{
public:

	CBullet2D();
	virtual ~CBullet2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
};

#endif
