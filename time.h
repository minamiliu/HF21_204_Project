//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: time.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/29
//
//============================================

#ifndef _TIME_H_
#define _TIME_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "score.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CTime : public CScore
{
public:

	CTime();
	virtual ~CTime();

	HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTime *Create(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, int startTime, bool bCountDown, const D3DXCOLOR &col);
	bool TimeUp(void);
	void StopTime(void);
	int GetTime(void);
private:
	int m_nCntFrame;
	int m_nTime;
	bool m_bCountDown;
	bool m_useFlag;//�J�E���g��i�߂邩�ǂ���
};

#endif
