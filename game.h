//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: game.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _GAME_H_
#define _GAME_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "manager.h"

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================

//============================================
//�\���̒�`
//============================================

class CGame : public CManager
{
public:

	CGame();
	virtual ~CGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif