//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: partX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/04
//
//============================================

#ifndef _PARTX_H_
#define _PARTX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CPartX
{
public:

	CPartX();
	virtual ~CPartX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPartX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	HRESULT LoadXfile(LPCSTR strFileName);
	
	void BindXfile( LPDIRECT3DTEXTURE9	pTexture,		// �e�N�X�`���ւ̃|�C���^
					LPD3DXMESH			pD3DXMesh,		// ���b�V�����ւ̃|�C���^
					LPD3DXBUFFER		pD3DXBuffMat,	// �}�e���A�����ւ̃|�C���^
					DWORD				nNumMat);		// �}�e���A�����̐�


	//��{���̐ݒ�A�擾
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	D3DXVECTOR3 GetRot(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetRot(D3DXVECTOR3 rot); 

private:

	//�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH  m_pD3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER  m_pD3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD	m_nNumMat;					// �}�e���A�����̐�

	D3DXVECTOR3 m_pos;					// ���f���̈ʒu
	D3DXVECTOR3 m_rot;					// ���f���̌���(��])
	D3DXVECTOR3 m_scl;					// ���f���̑傫��(�X�P�[��)

	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_size;
	bool m_bLoadXfile;

};

#endif
