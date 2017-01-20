/*******************************************************************************
* �^�C�g��:		sun
* �v���O������:	sun.h
* �쐬��:		���ї�Y
* �쐬��:		2016/12/03
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#ifndef _SUN_H_
#define _SUN_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "scene2D.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
/*******************************************************************************
* �N���X��`
*******************************************************************************/
//�N���X�錾
class CSun : public CScene2D
{
public:

	CSun();
	~CSun();
	//static CSun* Create(D3DXVECTOR3 pos,D3DXVECTOR3 nextPos,D3DXVECTOR3 size,bool move);
	//HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size);
	static CSun* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,float fRot);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size,float fRot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_time;
	int m_animPat;
	int m_animCnt;
	static bool m_bMove;
	float m_fRot;
	static D3DXVECTOR3 center;
};
#endif