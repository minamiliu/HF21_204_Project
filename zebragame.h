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
//============================================
//�\���̒�`
//============================================

class CZebraGame : public CManager
{
public:

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

private:
	static CScene2D *m_pZebra;
	CScene2D *m_pZebraBox;
	static CPoint3D *m_pPoint3D;
	static int m_PutToy;
	static int m_PutBook;
	CMeshWall *m_pMeshWall[MAX_WALL];
	int m_nNumWall;
	static CScore *m_pScore;
};

#endif
