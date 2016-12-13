//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: mousePick.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/06
//
//============================================

#ifndef _MOUSEPICK_H_
#define _MOUSEPICK_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CMousePick
{
public:

	CMousePick();
	virtual ~CMousePick();

	static D3DXVECTOR3 GetWorldPos( POINT pos);

private:

	// �X�N���[�����W�����[���h���W�ɕϊ�
	static D3DXVECTOR3 *CalcScreenToWorld(
		D3DXVECTOR3* pout,
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

	// XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
	static D3DXVECTOR3 *CMousePick::CalcScreenToXZ(
		D3DXVECTOR3* pout,
		int Sx,
		int Sy,
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

};

#endif
