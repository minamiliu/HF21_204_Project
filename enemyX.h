//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: enemyX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/12
//
//============================================

#ifndef _ENEMYX_H_
#define _ENEMYX_H_

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
class CLimbX;

//============================================
//�\���̒�`
//============================================
class CEnemyX : public CSceneX
{
public:
	typedef struct
	{
		int nFrame;
		D3DXVECTOR3 front;
		float rotY;
	}MOTION;

	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_000,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_STUN,
		STATE_MAX,
	}STATE;

	CEnemyX();
	virtual ~CEnemyX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state, int nCntState);
	STATE GetState(void);

	static CEnemyX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);
	static HRESULT LoadMotion(void);

protected:
	D3DXVECTOR3 Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);
	void UpdateMotion(void);

private:
	//���f���֌W
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat		[TYPE_MAX];		// �}�e���A�����̐�	

	//���[�V�����֌W
	static MOTION *m_pMotionPara;
	int m_nCntMotion;
	int m_nMotionNow;

	//��{���
	D3DXVECTOR3 m_front;
	float m_rotTurn;
	STATE m_state;
	int m_nCntState;
	D3DXVECTOR3 m_posInit;
	D3DXVECTOR3 m_rotInit;
	D3DXVECTOR3 m_sclInit;
	D3DXVECTOR3 m_rotSave;

	CShadow *m_pShadow;			//�e
	CLimbX *m_pLimb[MAX_LIMB];	//�葫x4
};

#endif
