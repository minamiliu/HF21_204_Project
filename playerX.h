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

//============================================
//�O���錾
//============================================
class CShadow;
//============================================
//�\���̒�`
//============================================

class CPlayerX : public CSceneX
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_CRASH,
		STATE_MAX,
	}STATE;

	CPlayerX();
	virtual ~CPlayerX();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed);
	D3DXVECTOR3 GetFront(void);

	void SetState(STATE state);
	STATE GetState(void);

protected:
	void UpdateRot(void);
	void CalcNextPos(void);
	bool isKeyUse(int nUp, int nDown, int nLeft, int nRight);
	bool isMouseUse(void);

private:
	D3DXVECTOR3 m_move;			// ���f���̈ړ���
	float m_fSpeed;				// ���f���̃X�s�[�h
	float m_fAccel;				// �����x
	D3DXVECTOR3 m_front;		// �O�i�x�N�g��

	D3DXVECTOR3 m_rotTarget;	// ���f���̌���(��])
	D3DXVECTOR3 m_rotAngle;		// ���f���̌���(��])

	bool m_isGoAhead;			//�O�i�t���O
	bool m_isGoBack;			//��ރt���O

	STATE m_state;				//���
	int m_nCntState;			//��Ԃ̃J�E���^�[
	CShadow *m_shadow;			//�e
};

#endif
