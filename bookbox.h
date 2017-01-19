//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: BookBox.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

#ifndef _BOOKBOX_H_
#define _BOOKBOX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "sceneX.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CBookBox : public CSceneX
{
public:
	typedef enum
	{
		TYPE_BOOKLACK = 0,
		TYPE_TOYBOX,
		TYPE_TVSET,
		TYPE_MAX,
	}TYPE;

	CBookBox();
	virtual ~CBookBox();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//float GetDistanceBoxPoint(D3DXVECTOR3 point);

	static HRESULT Load(void);
	static void Unload(void);
	static CBookBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);

protected:
	//D3DXVECTOR3 GetSideMin(void);
	//D3DXVECTOR3 GetSideMax(void);

private:
	//D3DXVECTOR3 m_sideLen;
	TYPE m_type;
};

#endif
