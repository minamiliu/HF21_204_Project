/*******************************************************************************
* �^�C�g��:		�^�C�g���I�u�W�F�N�g
* �v���O������:	titleObj.h
* �쐬��:		���ї�Y
* �쐬��:		2017/01/09
********************************************************************************
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#ifndef _TITLEOBJ_H_
#define _TITLEOBJ_H_
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
class CTitleObj : public CScene2D
{
public:
	typedef enum
	{
		TITLE_BG = 0,
		TITLE_LOGO,
		TITLE_GORIRA,
		TITLE_ZEBRA,
		TITLE_LION,
		TITLE_START,
		MAX_TITLE_OBJ,
	}TITLE_OBJ_TYPE;

	CTitleObj();
	~CTitleObj();
	static CTitleObj* Create(TITLE_OBJ_TYPE nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 size);
	HRESULT Init(TITLE_OBJ_TYPE nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TITLE_OBJ];
	D3DXVECTOR3 m_move;//�ړ���
	int m_time;
	int m_animPat;
	int m_type;
	static char *g_TitleObjTex[MAX_TITLE_OBJ];
	static bool bScl;
	static int alpha;
};
#endif