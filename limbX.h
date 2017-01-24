//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: limbX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/16
//
//============================================

#ifndef _LIMBX_H_
#define _LIMBX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "partX.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CLimbX : public CPartX
{
public:
	typedef struct
	{
		int nFrame;
		float rotX;
	}MOTION;

	typedef enum
	{
		TYPE_L_HAND = 0,
		TYPE_R_HAND,
		TYPE_L_FOOT,
		TYPE_R_FOOT,
		TYPE_LION_L_HAND,
		TYPE_LION_R_HAND,
		TYPE_LION_L_FOOT,
		TYPE_LION_R_FOOT,
		TYPE_MAX,
	}TYPE;

	CLimbX();
	virtual ~CLimbX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindXfile(TYPE type);

	static CLimbX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:

	//�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat		[TYPE_MAX];		// �}�e���A�����̐�

	TYPE m_type;

	//���[�V����
	static MOTION *m_pMotionPara;
	int m_nCntFrame;
	int m_nMotionNow;
	float m_rotXTurn;
	float m_rotXLocal;
	D3DXVECTOR3 m_posLocal;
	D3DXVECTOR3 m_rotLocal;

};

#endif
