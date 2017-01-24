//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: effect3D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/19
//
//============================================

#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "billboard.h"

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================

//============================================
//�\���̒�`
//============================================
class CEffect3D : public CBillBoard
{
public:
	typedef enum 
	{
		TYPE_MARU = 0,
		TYPE_MAX,
	}TYPE;

	CEffect3D();
	virtual ~CEffect3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col, float fPercent);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, float fPercent, bool bRainbow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type, const D3DXCOLOR &col, float fPercent);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float fPercent, bool bRainbow);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];

	TYPE m_type;
	D3DXCOLOR m_col;
	float m_fPercent;

	bool bRainbow;
	static D3DXCOLOR m_paraColor[];
	static int m_nColorID;
};

#endif
