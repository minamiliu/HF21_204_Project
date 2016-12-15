//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: meshWall.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/06
//
//============================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene3D.h"

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CMeshWall : public CScene3D
{
public:

	CMeshWall();
	virtual ~CMeshWall();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY);

	static HRESULT Load(void);
	static void Unload(void);
	
	bool HitCheck( D3DXVECTOR3 tNowPos, D3DXVECTOR3 tNextPos, D3DXVECTOR3 *wall_nor, D3DXVECTOR3 *HitPoint);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
