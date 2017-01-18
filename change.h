//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: player2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _CHANGE_H_
#define _CHANGE_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"
#include "scene2D.h"
//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CChange : public CScene
{
public:
	CChange();
	virtual ~CChange();

	HRESULT Init( LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CChange *Create( LPCSTR strPlayerFileName, LPCSTR strAnimalFileName, LPCSTR strAnimalPlayerFileName);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	static bool GetState(void);
	static void changeState(void);
private:
	static CScene2D *m_pChamgeBg;
	static int changeCnt;
	static bool m_bState;
	static bool m_bAnimalPlayerFlag;
};

#endif
