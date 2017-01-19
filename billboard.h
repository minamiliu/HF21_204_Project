//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: billboard.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene3D.h"

//============================================
//�}�N����`
//============================================
class CBillBoard : public CScene3D
{
public:

	CBillBoard();
	CBillBoard(LAYER layer);
	virtual ~CBillBoard();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBillBoard *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

private:

};

#endif
