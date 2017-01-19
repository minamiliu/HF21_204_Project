//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: title.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _STAGE_H_
#define _STAGE_H_

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

class CStage : public CManager
{
public:
	typedef enum
	{
		MASU_START = 0,
		MASU_GORIRA,
		MASU_ZEBRA,
		MASU_LION,
		MASU_GOAL,
		MASU_MAX
	}MASU_TYPE;
	CStage();
	CStage::CStage(MASU_TYPE type);
	virtual ~CStage();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static D3DXVECTOR3 pos[MASU_MAX];
	static MASU_TYPE m_stageNow;
};

#endif
