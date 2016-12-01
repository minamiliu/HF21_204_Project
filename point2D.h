//============================================
//
// �^�C�g��:	 HF
// �v���O������: trash.h
// �쐬��:		 HAL�����Q�[���w�ȁ@yamaga keisuke
// �쐬��:       2016/11/10
//
//============================================

#ifndef _POINT2D_H_
#define _POINT2D_H_

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

class CPoint2D : public CScene2D
{
public:

	CPoint2D();
	virtual ~CPoint2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPoint2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CPoint2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HWND hwnd);


private:
	D3DXVECTOR3 m_startPos;//�x�N�g���̎n�_
	D3DXVECTOR3 m_endPos;//�x�N�g���̏I�_
	D3DXVECTOR3 m_speed;
	HWND m_hwnd;
};

#endif
