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
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//============================================
//�\���̒�`
//============================================
//�R�c�|���S��
typedef struct
{
	D3DXVECTOR3 vtx; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR	col; //���_�J���[
	D3DXVECTOR2	tex; //�e�N�X�`�����W
}VERTEX_3D;

class CScene3D : public CScene
{
public:

	CScene3D();
	CScene3D(LAYER layer);
	virtual ~CScene3D();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, bool bUseYnotZ);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Draw(const D3DXMATRIX *mtxView);

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, bool bUseYnotZ);

	HRESULT Load(LPCSTR strFileName);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetColor(const D3DXCOLOR &col); //�F��ύX
	
protected:
	virtual bool HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint);

private:
	//�֐�
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	//�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	bool m_bLoadTexture;					// �e�N�X�`����ǂݍ��񂾂��ǂ���

	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXVECTOR3		m_rot;					// ����
	D3DXMATRIX		m_mtxWorld;				// ���[���h�}�g���b�N�X

	int m_nNumBlockX, m_nNumBlockZ;			// �u���b�N��
	int m_nNumVertex;						// �����_��
	int m_nNumVertexIndex;					// ���C���f�b�N�X��
	int m_nNumPolygon;						// ���|���S����
	float m_fSizeBlockX, m_fSizeBlockZ;		// �u���b�N�T�C�Y

	D3DXVECTOR3 m_size;
	bool m_bUseYnotZ;
};

#endif
