/*******************************************************************************
* �^�C�g��:		�^�C�g���I�u�W�F�N�g
* �v���O������:	titleObj.cpp
* �쐬��:		���ї�Y
* �쐬��:		2017/01/09
********************************************************************************
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "titleObj.h"
#include "manager.h"
#include "scene2D.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/

/*******************************************************************************
* �N���X��`
*******************************************************************************/
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �ÓI
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitleObj::m_pTexture[MAX_TITLE_OBJ] = {};

char *CTitleObj::g_TitleObjTex[MAX_TITLE_OBJ] = 
{
	{"data/TEXTURE/�T�o���i�^�C�g���p/�w�i/titleBg.png"},
	{"data/TEXTURE/�T�o���i�^�C�g���p/���S/logo.png"},
	{"data/TEXTURE/�T�o���i�^�C�g���p/�S����/gori.png"},
	{"data/TEXTURE/�T�o���i�^�C�g���p/�V�}�E�}/zebra.png"},
	{"data/TEXTURE/�T�o���i�^�C�g���p/���C�I��/lion.png"},
	{"data/TEXTURE/�T�o���i�^�C�g���p/�X�^�[�g/start.png"}
};

bool CTitleObj::bScl = false;
int CTitleObj::alpha = 0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleObj :: CTitleObj()
{
	m_time = 0;
	m_animPat = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleObj :: ~CTitleObj()
{
}
CTitleObj* CTitleObj::Create(TITLE_OBJ_TYPE nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 size)
{
	CTitleObj *pTitleObj;
	pTitleObj = new CTitleObj;
	pTitleObj->Init(nType,pos,rot,size);

	//�e�N�X�`���̊��蓖��
	pTitleObj->Load(g_TitleObjTex[nType]);
	return pTitleObj;
}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTitleObj :: Init(void)
{
	CScene2D::Init();

	return S_OK;
}
//=============================================================================
// �|���S���̏���������(�I�[�o�[���[�h)
//=============================================================================
HRESULT CTitleObj :: Init(TITLE_OBJ_TYPE nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size,D3DXVECTOR2(1,1));
	m_type = nType;

	return S_OK;
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTitleObj :: Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTitleObj :: Update(void)
{
	D3DXVECTOR3 pos = GetPosition();//�|�W�V�����󂯎��
	D3DXVECTOR3 size = GetSize();

	m_time ++;

	switch(m_type)
	{
	case TITLE_BG:
		if(bScl == true)
		{
			CScene2D::Scl(0.001,CScene2D::SCL_LEFT);
		}
		break;
	case TITLE_LOGO:
		if(bScl == false)
		{
			alpha = 0;
		}
		else
		{
			if(alpha < 255)
			{
				alpha += 5;
			}
			if(alpha > 255)
			{
				alpha = 255;
			}
		}
		CScene2D::SetAlpha(alpha);
		break;
	case TITLE_GORIRA:
		if(m_time%20 == 0)
		{
			m_animPat++;
		}
		if(pos.x > 340)
		{
			pos.x-=2;
		}
		CScene2D::SetTexture(4,1,m_animPat);
		break;
	case TITLE_ZEBRA:
		if(m_time%8 == 0)
		{
			m_animPat++;
		}
		if(pos.x > 640)
		{
			pos.x-=2;
		}
		CScene2D::SetTexture(7,1,m_animPat);
		break;
	case TITLE_LION:
		if(m_time%15 == 0)
		{
			m_animPat++;
		}
		if(pos.x > 940)
		{
			pos.x-=2;
		}
		else
		{
			bScl = true;
		}
		CScene2D::SetTexture(4,1,m_animPat);
		break;
	case TITLE_START:
		if(bScl == false)
		{
			alpha = 0;
		}
		else
		{
			if(alpha < 255)
			{
				alpha += 5;
			}
			if(alpha > 255)
			{
				alpha = 255;
			}
		}
		if(alpha == 255)
		{
			if(m_time%15 == 0)
			{
				m_animPat++;
			}
		}
		CScene2D::SetTexture(1,4,m_animPat);
		break;
	}

	this->CTitleObj::SetPosition(pos);//�|�W�V�����Ԃ�
}
//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTitleObj :: Draw(void)
{
	CScene2D::Draw();
}