//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: shadow.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

#ifndef _SHADOW_H_
#define _SHADOW_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene3D.h"

//============================================
//�}�N����`
//============================================
class CShadow : public CScene3D
{
public:

	CShadow();
	virtual ~CShadow();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);

	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
