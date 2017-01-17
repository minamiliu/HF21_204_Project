//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _TRASHGAMEEXPLOSION_H_
#define _TRASHGAMEEXPLOSION_H_

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

class CTrashGameExplosion : public CScene2D
{
public:
	CTrashGameExplosion();
	virtual ~CTrashGameExplosion();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrashGameExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	
	
private:
	
	int m_nAnimCnt;
	int m_nPatternAnim;

};

#endif
