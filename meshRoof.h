//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: meshRoof.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2017/01/11
//
//============================================

#ifndef _MESHROOF_H_
#define _MESHROOF_H_

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

class CMeshRoof : public CScene3D
{
public:
	typedef enum
	{
		TYPE_GREEN = 0,
		TYPE_WHITE,
		TYPE_MAX,
	}TYPE;

	CMeshRoof();
	virtual ~CMeshRoof();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshRoof *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ, TYPE type);

	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
};

#endif
