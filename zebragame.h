//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: game.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _ZEBRAGAME_H_
#define _ZEBRAGAME_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "manager.h"

//============================================
//�}�N����`
//============================================
#define MAX_WALL (5)
//============================================
//�O���錾
//============================================
class CZebra;
class CZebraBox;
class CScene2D;
class CMeshWall;
class CPoint3D;
class CScore;
class CTime;
class CScene2D;
class CChange;
class CSound;
//============================================
//�\���̒�`
//============================================

class CZebraGame : public CManager
{
public:
	typedef enum 
	{
		STATE_NORMAL = 0,
		STATE_UPGRADE,
		STATE_ZEBRA,
		STATE_BONUS,
		STATE_FINISH,
		STATE_MAX,
	}STATE;

	CZebraGame();
	virtual ~CZebraGame();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetZebraPointer(CScene2D *pZebra);
	static void PutObj(bool toy);
	static HRESULT LoadAll(void);
	static CScore *GetScore(void);

protected:
	void CalcBonus(void);

private:
	static CScene2D *m_pZebra;
	static CPoint3D *m_pPoint3D;
	static int m_PutToy;
	static int m_PutBook;
	static CScore *m_pScore;
	static CTime *m_pTime;
	STATE m_state;
	CChange *m_pChange; //�ϐg

	int m_nGameCnt;
	CScene2D *m_pTextureMlt;
	CScore *m_pTextureHd;
	CSound *m_pSound;
};

#endif
