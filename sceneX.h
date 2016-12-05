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

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	D3DXVECTOR3 GetRot(void);

protected:
	//�֐�
	D3DXVECTOR3 Get2VecRotAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);
	void UpdateModelMove(int nUp, int nDown, int nLeft, int nRight);
	void UpdateModelMove2(int nUp, int nDown, int nLeft, int nRight);

private:
	//�ϐ�
	LPDIRECT3DTEXTURE9	m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH  m_pD3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER  m_pD3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD	m_nNumMat;					// �}�e���A�����̐�

	D3DXVECTOR3 m_pos;					// ���f���̈ʒu
	D3DXVECTOR3 m_rot;					// ���f���̌���(��])
	D3DXVECTOR3 m_scl;					// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3 m_move;					// ���f���̈ړ���
	float m_speed;						// ���f���̃X�s�[�h

	D3DXVECTOR3 m_rotTarget;			// ���f���̌���(��])
	D3DXVECTOR3 m_rotAngle;				// ���f���̌���(��])

	//�L�[�t���C��
	//D3DXVECTOR3 posChild;				//�q���W
	//D3DXVECTOR3 posChildTarget;		//�q���W�̖ڕW
	//D3DXVECTOR3 rotChild;				//�q���W�̌���
	//D3DXVECTOR3 rotChildAngle;		//�q���W�̖���̉�]��
	//D3DXVECTOR3 rotChildTarget;		//�q���W�̌����̖ڕW

	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X


	D3DXVECTOR3 m_size;
};

#endif
