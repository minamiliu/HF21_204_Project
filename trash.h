//============================================
//
// �^�C�g��:	 HF
// �v���O������: trash.h
// �쐬��:		 HAL�����Q�[���w�ȁ@yamaga keisuke
// �쐬��:       2016/11/10
//
//============================================

#ifndef _TRASH_H_
#define _TRASH_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene2D.h"

//============================================
//�}�N����`
//============================================
#define MAX_TRASH (256)
//============================================
//�\���̒�`
//============================================

class CTrash : public CScene2D
{
public:
	typedef enum
	{
		TRASHTYPE_NORMAL = 0,
		TRASHTYPE_LIGHT,
		TRASHTYPE_HEAVY,
		TRASHTYPE_MAX
	}TRASHTYPE;
	CTrash();
	virtual ~CTrash();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTrash *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName,OBJTYPE type);
	D3DXVECTOR3 GetSpeed(void);
	void SetSpeed(D3DXVECTOR3 speed);
	void ReverseMove(void);
	TRASHTYPE GetTrashType(void);
	void TrashEnd(void);
private:
	D3DXVECTOR3 m_speed;
	bool m_fallFlag;//�����t���O
	bool m_apFlag;//�o���t���O
	static int m_cnt;//�o���^�C�~���O�J�E���^�[
	float m_gravityCoefficient;//�d�͌W��
	static LPDIRECT3DTEXTURE9 m_pTexture;
	TRASHTYPE m_TrashType;
};

#endif
