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
#define MAX_CUBE (100)
//============================================
//�O���錾
//============================================
class CPlayerX;
class CMeshWall;
class CCubeX;
class CScore;
class CTime;
class CEffectBG;
class CChange;
class CScene2D;
//============================================
//�\���̒�`
//============================================

class CLionGame : public CManager
{
public:
	typedef enum 
	{
		STATE_NORMAL = 0,
		STATE_UPGRADE,
		STATE_LION,
		STATE_BONUS,
		STATE_FINISH,
		STATE_MAX,
	}STATE;

	CLionGame();
	virtual ~CLionGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//�ÓI
	static CScore *GetScore(void);
	static CPlayerX *GetPlayer(void);
	static HRESULT LoadAll(void);
protected:
	void CreateStageLiu(void);
	void CreateStageUsukura(void);
	void CalcBonus(void);
private:

	STATE m_state;
	int m_nCntState;	//��Ԃ̃J�E���^�[

	CChange *m_pChange; //�ϐg
	CTime *m_pTime;
	static CPlayerX *m_pPlayer;
	static CScore *m_pScore;

	int m_nGameCnt;
	CScene2D *m_pTextureMlt;
	CScore *m_pTextureHd;
};

#endif
