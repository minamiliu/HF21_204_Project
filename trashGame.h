//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: game.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _TRASHGAME_H_
#define _TRASHGAME_H_

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
class CTrash;
class CTrashBox;
class CScene2D;
class CScore;
//============================================
//�\���̒�`
//============================================

class CTrashGame : public CManager
{
public:

	CTrashGame();
	virtual ~CTrashGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetTrashPointer(CTrash *pTrash);
private:
	static CTrash *m_pTrash;
	static CScene2D *m_pTrashBox;
	static CScore *m_pScore;
	static CScene2D *m_pPoint2D;
	static CScene2D *m_pMouse;
	static CScene2D *m_pMidpoint;
};

#endif
