//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: food.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/15
//
//============================================

#ifndef _FOOD_H_
#define _FOOD_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "billboard.h"

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================
class CFoodIcon;

//============================================
//�\���̒�`
//============================================
class CFood : public CBillBoard
{
public:
	typedef enum 
	{
		TYPE_NONE = -1,
		TYPE_TOMATO,
		TYPE_CARROT, 
		TYPE_BANANA,
		TYPE_MILK,
		TYPE_CABBAGE,	
		TYPE_CURRY,
		TYPE_EGG,	
		TYPE_ONION,	
		TYPE_POTATO,	
		TYPE_MEAT,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_FLYING,
		STATE_MAX,
	}STATE;

	CFood();
	virtual ~CFood();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state, int nCntState);
	STATE GetState(void);

	CFoodIcon* GetIcon(void);
	void SetClear(void);

	static CFood *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	static bool isAllClear(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];

	CFoodIcon *m_pIcon;
	TYPE m_type;
	static bool bClear[TYPE_MAX];
	D3DXVECTOR3 m_posInit;
	float m_fAngle;
	float m_fTurn;
	float m_fMoveY;

	//���
	STATE m_state;
	int m_nCntState;
};

#endif