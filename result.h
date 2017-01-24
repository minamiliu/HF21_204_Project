//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: result.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _RESULT_H_
#define _RESULT_H_

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
class CSound;
//============================================
//�\���̒�`
//============================================
class CScore;
class CScene2D;
class CResult : public CManager
{
public:

	CResult();
	virtual ~CResult();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_resultCnt;
	static CScore *m_pTrashGameScore;
	static CScore *m_pZebraGameScore;
	static CScore *m_pLionGameScore;
	static CScene2D *m_pRank[3];
	int m_nTrashGameScore;
	int m_nZebraGameScore;
	int m_nLionGameScore;
	int m_nTargetScore[3];

	CSound *m_pSound;
};

#endif
