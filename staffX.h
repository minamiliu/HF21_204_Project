//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: staffX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/23
//
//============================================

#ifndef _STAFF_H_
#define _STAFF_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "sceneX.h"

//============================================
//�}�N����`
//============================================
#define MAX_LIMB (4)
//============================================
//�O���錾
//============================================
class CShadow;

//============================================
//�\���̒�`
//============================================
class CStaffX : public CSceneX
{
public:

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_000,
		TYPE_MAX,
	}TYPE;

	CStaffX();
	virtual ~CStaffX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStaffX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	//���f���֌W
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat		[TYPE_MAX];		// �}�e���A�����̐�	

	CShadow *m_pShadow;			//�e
};

#endif
