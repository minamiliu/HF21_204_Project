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
		TYPE_CABBAGE,
		TYPE_MEAT,
		TYPE_MAX,
	}TYPE;

	CFood();
	virtual ~CFood();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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
};

#endif
