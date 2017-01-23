//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: playerX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

#ifndef _TOY_H_
#define _TOY_H_

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

class CToy : public CSceneX
{
public:

	CToy();
	virtual ~CToy();
	typedef enum
	{
			TYPE_ROBOT,
			TYPE_BLOCK,
			TYPE_CAR,
			TYPE_BEAR,
			TOYTYPE_MAX
	}TOYTYPE;
	#define MAX_TOYTYPE (TOYTYPE_MAX)
	#define MAX_TOY (15)
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CToy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	static HRESULT CToy::Load(void);
	void CToy::BindXfile( int type);

	void CToy::ChangePicked(bool pick, bool zebra);
	void GetBoxpos(void);

	static int m_nNumber;
private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[MAX_TOYTYPE];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_pD3DXMesh		[MAX_TOYTYPE];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pD3DXBuffMat	[MAX_TOYTYPE];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat		[MAX_TOYTYPE];		// �}�e���A�����̐�
	bool m_bPicked;
	bool m_bZebra;
	bool m_bBack;

	D3DXVECTOR3 m_Move;
	float m_gravity;
	int m_Timecnt;
	D3DXVECTOR3 m_oldpos;

	static D3DXVECTOR3 Toyboxpos;
	static D3DXVECTOR3 Bookboxpos;
};

#endif
