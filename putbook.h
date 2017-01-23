//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: playerX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

#ifndef _PUTBOOK_H_
#define _PUTBOOK_H_

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

class CPutBook : public CSceneX
{
public:

	CPutBook();
	virtual ~CPutBook();
	typedef enum
	{
			TYPE_RED,
			TYPE_GREEN,
			TYPE_BLUE,
			TYPE_YELLOW,
			BOOKTYPE_MAX
	}BOOKTYPE;
	#define MAX_BOOKTYPE (BOOKTYPE_MAX)
	#define MAX_BOOK (15)
	//HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl,int type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	
	static HRESULT Load(void);
	void CPutBook::BindXfile( int type);

	//static CPutBook *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	static CPutBook *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int type);
	static void InitPubBookPos(void);

	static int m_nNumber;
private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[MAX_BOOKTYPE];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_pD3DXMesh		[MAX_BOOKTYPE];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pD3DXBuffMat	[MAX_BOOKTYPE];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat		[MAX_BOOKTYPE];		// �}�e���A�����̐�
	
	int m_Timecnt;
	
	static D3DXVECTOR3 m_PutBookPos[MAX_BOOK];
	
};

#endif
