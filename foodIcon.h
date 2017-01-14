//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: food2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/11
//
//============================================

#ifndef _FOODICON_H_
#define _FOODICON_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene2D.h"

//============================================
//�}�N����`
//============================================
#define MAX_ICON (10)
//============================================
//�\���̒�`
//============================================

class CFoodIcon : public CScene2D
{
public:
	CFoodIcon();
	virtual ~CFoodIcon();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�֐�
	static CFoodIcon *Create(D3DXVECTOR3 size, LPDIRECT3DTEXTURE9, int id);
	//static void CreateAllFoodIcon(void);
	//static HRESULT Load(void);
	//static void Unload(void);

private:

	//static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	static D3DXVECTOR3 m_posInit[MAX_ICON];
};

#endif
