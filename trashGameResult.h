//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: trashGameResult.h
// �쐬��:		 HAL�����Q�[���w�ȁ@�R�ƌ[��
// �쐬��:       2016/12/13
//
//============================================

#ifndef _TRASHGAMERESULT_H_
#define _TRASHGAMERESULT_H_

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

class CTrashGameResult : public CManager
{
public:

	CTrashGameResult();
	virtual ~CTrashGameResult();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetTrashGameResultCnt(void);
private:
	static CScore *m_pScore;
	static int m_nTrashGameResultCnt;
};

#endif
