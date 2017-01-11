//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: lionGame.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _LIONGAME_H_
#define _LIONGAME_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "manager.h"

//============================================
//�}�N����`
//============================================
#define MAX_WALL (5)
#define MAX_CUBE (20)
//============================================
//�O���錾
//============================================
class CPlayerX;
class CMeshWall;
class CCubeX;
class CScore;
//============================================
//�\���̒�`
//============================================

class CLionGame : public CManager
{
public:

	CLionGame();
	virtual ~CLionGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//�X�R�A
	static CScore *GetScore(void);

private:
	CPlayerX *m_player;
	CMeshWall *m_pMeshWall[MAX_WALL];
	int m_nNumWall;

	CCubeX *m_cube[MAX_CUBE];
	int m_nNumCube;

	//static CScore *m_score;
};

#endif
