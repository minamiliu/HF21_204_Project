//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: collison.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/12/02
//
//============================================

#ifndef _COLLISION_H_
#define _COLLISION_H_

//============================================
//�}�N����`
//============================================


//============================================
//�\���̒�`
//============================================

class CCollision
{
public:
	CCollision();
	virtual ~CCollision();

	// �|���S���Ɛ����Ƃ̓����蔻��
	static bool HitCheck(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 *hitPos);

	// �ǂ���x�N�g��
	static D3DXVECTOR3* GetWallScratchVector(D3DXVECTOR3 *out, D3DXVECTOR3 &front, D3DXVECTOR3 &normal);

	// ��_���擾
	static D3DXVECTOR3 GetHitPos(void);

	// �ۂ̓����蔻��
	static bool HitCheckBall( D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2);

	// ���ʂ̉~�̓����蔻��
	static bool HitCheckCircleXZ( D3DXVECTOR3 pos1, float radius1, D3DXVECTOR3 pos2, float radius2);

	// �Q�_�̌����x�N�g�����擾
	static D3DXVECTOR3 GetRotationAngle( D3DXVECTOR3 myPos, D3DXVECTOR3 target, D3DXVECTOR3 myRot);

	// ������̔���
	static bool HitCheckViewArea( D3DXVECTOR3 myPos, D3DXVECTOR3 tarPos, D3DXVECTOR3 myRot, float myView);

	// �Q�_�������擾
	static float GetDistanceXZ( D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);

private:

	// ����
	static float DotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr);

	// �O��
	static D3DXVECTOR3 CrossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr );
};

#endif