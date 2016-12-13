//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: game.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _ZEBRAGAME_H_
#define _ZEBRAGAME_H_

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
class CZebra;
class CZebraBox;
class CScene2D;
class CScore;
//============================================
//�\���̒�`
//============================================

class CZebraGame : public CManager
{
public:

	CZebraGame();
	virtual ~CZebraGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetZebraPointer(CScene2D *pZebra);
	static CScore *GetScoreP(void);
private:
	static CScene2D *m_pZebra;
	CScene2D *m_pZebraBox;
	static CScore *m_score;
};

#endif
