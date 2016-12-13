//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: sceneX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

#ifndef _SCENEX_H_
#define _SCENEX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CSceneX : public CScene
{
public:

	CSceneX();
	virtual ~CSceneX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, LPCSTR strFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, LPCSTR strFileName);
	HRESULT LoadXfile(LPCSTR strFileName);
	HRESULT LoadXfile(LPCSTR strFileName, int nCnt);
	void BindXfile( LPDIRECT3DTEXTURE9	pTexture,		// �e�N�X�`���ւ̃|�C���^
					LPD3DXMESH			pD3DXMesh,		// ���b�V�����ւ̃|�C���^
					LPD3DXBUFFER		pD3DXBuffMat,	// �}�e���A�����ւ̃|�C���^
					DWORD				nNumMat);		// �}�e���A�����̐�
	//���f���֘A
	//HRESULT Load(LPCSTR strFileName);
	//void BindXFile( LPDIRECT3DTEXTURE9 pTexture);

	//��{���̐ݒ�A�擾
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	D3DXVECTOR3 GetRot(void);
	void SetPosition( D3DXVECTOR3 pos);
	void SetSize( D3DXVECTOR3 size);
	void SetRot( D3DXVECTOR3 rot);private:

	//�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH  m_pD3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER  m_pD3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD	m_nNumMat;					// �}�e���A�����̐�

	D3DXVECTOR3 m_pos;					// ���f���̈ʒu
	D3DXVECTOR3 m_rot;					// ���f���̌���(��])
	D3DXVECTOR3 m_scl;					// ���f���̑傫��(�X�P�[��)

	//�L�[�t���C��
	//D3DXVECTOR3 posChild;				//�q���W
	//D3DXVECTOR3 posChildTarget;		//�q���W�̖ڕW
	//D3DXVECTOR3 rotChild;				//�q���W�̌���
	//D3DXVECTOR3 rotChildAngle;		//�q���W�̖���̉�]��
	//D3DXVECTOR3 rotChildTarget;		//�q���W�̌����̖ڕW

	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X


	D3DXVECTOR3 m_size;
	bool m_bLoadXfile;
};

#endif
