//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: meshDome.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/12
//
//============================================

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================

//============================================
//�\���̒�`
//============================================
class CMeshDome : public CScene
{
public:
	CMeshDome();
	virtual ~CMeshDome();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);

	static CMeshDome *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nNumBlockH, int nNumBlockV);
	HRESULT Load(void);
	void Unload(void);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffTop;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffTop;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	bool m_bLoadTexture;					// �e�N�X�`����ǂݍ��񂾂��ǂ���

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3 m_rot;						// �|���S���̉�]�p

	int m_nNumBlockH;						// �u���b�N��
	int m_nNumBlockV;						// �u���b�N��
	int m_nNumVertex;						// �����_��	
	int m_nNumVertexIndex;					// ���C���f�b�N�X��
	int m_nNumPolygon;						// ���|���S����
	float m_fRadius;						// ���a
};

#endif
