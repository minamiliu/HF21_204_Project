//============================================
//
// �^�C�g��:	 HF
// �v���O������: trash.h
// �쐬��:		 HAL�����Q�[���w�ȁ@yamaga keisuke
// �쐬��:       2016/11/10
//
//============================================

#ifndef _POINT3D_H_
#define _POINT3D_H_

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

class CPoint3D : public CScene2D
{
public:

	CPoint3D();
	virtual ~CPoint3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPoint3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CPoint3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HWND hwnd);
	D3DXVECTOR3 Get3DPosition(void);

private:
	D3DXVECTOR3 m_startPos;//�x�N�g���̎n�_
	D3DXVECTOR3 m_endPos;//�x�N�g���̏I�_
	D3DXVECTOR3 m_speed;
	D3DXVECTOR3 m_3Dpos;
	HWND m_hwnd;
	bool m_zebra;
};

#endif