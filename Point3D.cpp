//============================================
//
// �^�C�g��:	 HF
// �v���O������: trash.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@yamaga keisuke
// �쐬��:       2016/11/10
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "manager.h"
#include "input.h"
#include "point3D.h"
#include "debugproc.h"
#include "mousePick.h"
#include "toy.h"
#include "book.h"
//============================================
// �}�N����`
//============================================
#define GRAVITY_POINT (0.98f)
#define TEXTURENAME "data/TEXTURE/player000.png"
#define	TEX_PATTERN_DIVIDE_X		(2)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�w����)
#define	TEX_PATTERN_DIVIDE_Y		(1)								// �A�j���[�V�����p�^�[���̃e�N�X�`�����ł̕�����(�x����)

#define	TEX_PATTERN_SIZE_X			(1.0f/TEX_PATTERN_DIVIDE_X)								// �P�p�^�[���̃e�N�X�`���T�C�Y(�w����)(1.0f/X����������)
#define	TEX_PATTERN_SIZE_Y			(1.0f/TEX_PATTERN_DIVIDE_Y)								// �P�p�^�[���̃e�N�X�`���T�C�Y(�x����)(1.0f/Y����������)

//=============================================================================
// �\���̒�`
//=============================================================================
//bool PointFlag = false;
CScene *pScenePick = NULL;

 bool CPoint3D::m_zebra = false;
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPoint3D::CPoint3D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPoint3D::~CPoint3D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CPoint3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	m_hwnd=hwnd;
	CScene2D::Init(pos, size);
	CScene2D::Load(TEXTURENAME);
	CScene2D::SetObjType(OBJTYPE_POINT);
	CScene2D::ChangeTextureAnime(1,D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),D3DXVECTOR2(1,1));
	m_startPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_endPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//m_zebra = false;
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPoint3D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPoint3D::Update(void)
{
	//// �}�E�X���W�̎擾
	POINT po;
	GetCursorPos(&po);
	
	ScreenToClient(m_hwnd,&po);
	ShowCursor(FALSE);
	D3DXVECTOR3 pos ;
	m_3Dpos = CMousePick::GetWorldPos(po);
	CDebugProc::Print("\n�J�[�\���̏ꏊ3D.x.y.z:%f,%f,%f",m_3Dpos.x,m_3Dpos.y,m_3Dpos.z);
	
	
	if(CManager::GetInputMouse()->GetMouseLeftTrigger())
	{
		CScene2D::ChangeTextureAnime(1,D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),D3DXVECTOR2(2,1));
		//�g�C�̏ꏊ�擾
		for(int Cnt=0; Cnt<MAX_SCENE ; Cnt++)
		{
			CScene *pScene ;
			pScene = CScene::GetScene(Cnt);
			if(pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene -> GetObjType();
				if(type == CScene::OBJTYPE_TOY )
				{
					D3DXVECTOR3 PosToy;
					D3DXVECTOR3 SizeToy = D3DXVECTOR3(50,50,50);
					PosToy = pScene ->GetPosition();

					//��������
					if(	   m_3Dpos.x > PosToy.x - SizeToy.x/2.0f 
						&& m_3Dpos.x < PosToy.x + SizeToy.x/2.0f 
						&& m_3Dpos.z > PosToy.z - SizeToy.z/2.0f  
						&& m_3Dpos.z < PosToy.z + SizeToy.z/2.0f 
						)
					{
						pScenePick = pScene;
						((CToy*)pScene)->ChangePicked(true,m_zebra);
						
						return;
					}
					
				}
				if(type == CScene::OBJTYPE_BOOK )
				{
					D3DXVECTOR3 PosToy;
					D3DXVECTOR3 SizeToy = D3DXVECTOR3(50,50,50);
					PosToy = pScene ->GetPosition();

					//��������
					if(	   m_3Dpos.x > PosToy.x - SizeToy.x/2.0f 
						&& m_3Dpos.x < PosToy.x + SizeToy.x/2.0f 
						&& m_3Dpos.z > PosToy.z - SizeToy.z/2.0f  
						&& m_3Dpos.z < PosToy.z + SizeToy.z/2.0f 
						)
					{
						pScenePick = pScene;
						((CBook*)pScene)->ChangePicked(true,m_zebra);
						
						return;
					}
					
				}
			}
			
		}
		
	}
	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
		
		CScene2D::ChangeTextureAnime(1,D3DXVECTOR2(TEX_PATTERN_SIZE_X,TEX_PATTERN_SIZE_Y),D3DXVECTOR2(1,1));
			if(pScenePick != NULL)
			{
	
				((CToy*)pScenePick)->ChangePicked(false,m_zebra);
				pScenePick = NULL;
				return;
	
			}
		
	}
	if(CManager::GetInputMouse()->GetMouseRightTrigger())
	{
		ChangeZebra();

	}
	if(m_zebra == true)
	{
		CDebugProc::Print("\n�[�u��");
	}
	pos.x = po.x;
	pos.y = po.y;
	CPoint3D::SetPosition(D3DXVECTOR3(pos.x,pos.y,0.0f));
	CScene2D::Update();
	float print = CManager::GetInputMouse()->GetMouseAxisX();
	CDebugProc::Print("\n�J�[�\���̏ꏊ.x.y:%f,%f",pos.x,pos.y);
	
	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPoint3D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CPoint3D *CPoint3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	CPoint3D *pPoint3D;
	pPoint3D = new CPoint3D;
	pPoint3D->Init(pos, size,hwnd);
	
	return pPoint3D;
}
//=============================================================================
// �|���S���̍��W�擾
//=============================================================================
D3DXVECTOR3 CPoint3D::Get3DPosition(void)
{
	return m_3Dpos;
}

//=============================================================================
//�[�u�����[�h
//=============================================================================
void CPoint3D::ChangeZebra(void)
{
	m_zebra = !m_zebra;
}
