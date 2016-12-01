//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene3D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/10
//
//============================================

#ifndef _SCENE3D_H_
#define _SCENE3D_H_

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

class CScene3D : public CScene
{
public:

	CScene3D();
	virtual ~CScene3D();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

private:
	//�֐�
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	//�ϐ�

	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXVECTOR3		m_rot;					// ����
	D3DXMATRIX		m_mtxWorld;				// ���[���h�}�g���b�N�X

	int m_nNumBlockX, m_nNumBlockZ;			// �u���b�N��
	int m_nNumVertex;						// �����_��
	int m_nNumVertexIndex;					// ���C���f�b�N�X��
	int m_nNumPolygon;						// ���|���S����
	float m_fSizeBlockX, m_fSizeBlockZ;		// �u���b�N�T�C�Y

	D3DXVECTOR3 m_size;
};

#endif
