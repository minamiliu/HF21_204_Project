//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: playerX.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

#ifndef _PLAYERX_H_
#define _PLAYERX_H_

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

class CPlayerX : public CSceneX
{
public:
	typedef enum
	{
		TYPE_HUMAN = 0,
		TYPE_LION,
		TYPE_MAX,
	}TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_HIT,
		STATE_UPGRADE,
		STATE_LION,
		STATE_GOAL,
		STATE_FINISH,
		STATE_MAX,
	}STATE;

	CPlayerX();
	virtual ~CPlayerX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state);
	STATE GetState(void);
	int GetFoodNum(void);
	void BindXfile(TYPE type);
	D3DXVECTOR3 GetFront(void);

	static CPlayerX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed, TYPE type);
	static HRESULT Load(void);
	static void Unload(void);


protected:
	void UpdateRot(void);
	void CalcFront(void);
	bool isKeyUse(int nUp, int nDown, int nLeft, int nRight);
	bool isMouseUse(void);
	bool isCollision(void);
	D3DXVECTOR3 Get2RotDiffAngle( D3DXVECTOR3 rot, D3DXVECTOR3 rotTarget);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture		[TYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_pD3DXMesh		[TYPE_MAX];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pD3DXBuffMat	[TYPE_MAX];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat		[TYPE_MAX];		// �}�e���A�����̐�

	float m_fSpeed;				// ���f���̃X�s�[�h
	float m_fAccel;				// �����x
	D3DXVECTOR3 m_front;		// �O�i�x�N�g��

	D3DXVECTOR3 m_rotTarget;	// ���f���̌���(��])
	D3DXVECTOR3 m_rotAngle;		// ���f���̌���(��])

	bool m_isGoAhead;			//�O�i�t���O
	bool m_isGoBack;			//��ރt���O

	STATE m_state;				//���
	int m_nCntState;			//��Ԃ̃J�E���^�[
	CShadow *m_pShadow;			//�e

	CLimbX *m_pLimb[MAX_LIMB];	//�葫x4
	
	int m_nNumFoodGet; //�W�߂��H�ނ̐�
};

#endif
