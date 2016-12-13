//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: playerX.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/15
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "toy.h"
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "mousePick.h"
#include "point3D.h"
#include "score.h"
#include "zebragame.h"
//============================================
// �}�N����`
//============================================
#define MODEL_BOOK "data/MODEL/book.x"
#define MODEL_TOY_CAR "data/MODEL/toy_car.x"
#define MODEL_FILENAME "data/MODEL/player.x"
#define VALUE_ROTATE	(D3DX_PI * 0.1f) 	// ��]��

//============================================
// �ÓI�����o�ϐ��̏�����
//============================================
LPDIRECT3DTEXTURE9	CToy::m_pTexture[] ={};
LPD3DXMESH			CToy::m_pD3DXMesh[]={};			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		CToy::m_pD3DXBuffMat	[]={};		// �}�e���A�����ւ̃|�C���^
DWORD				CToy::m_nNumMat		[]={};					// �}�e���A�����̐�
//HRESULT CToy::LoadXfile(LPCSTR strFileName, int nCnt);
int CToy::m_nNumber = 0;
//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CToy::CToy()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CToy::~CToy()
{
	
}


//=============================================================================
//
//=============================================================================
HRESULT CToy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	m_nNumber++;
	CSceneX::Init( pos, rot, scl, MODEL_FILENAME);

	LoadXfile(MODEL_FILENAME,TYPE_ROBOT);
	LoadXfile(MODEL_BOOK,TYPE_BLOCK);
	LoadXfile(MODEL_TOY_CAR,TYPE_CAR);
	LoadXfile(MODEL_FILENAME,TYPE_BEAR);
	// += m_nNumber%4;
	BindXfile(m_nNumber%4);
	SetObjType(OBJTYPE_TOY); ;
	m_bPicked = false;
	m_bZebra= false;
	return S_OK;
}

//=============================================================================
//x�t�@�C���̐ݒ�
//=============================================================================
void CToy::BindXfile(int type)	
{
	CSceneX::BindXfile( m_pTexture	[type],
					 m_pD3DXMesh	[type],	
					 m_pD3DXBuffMat[type],	
					 m_nNumMat		[type]
	);
}
//=============================================================================
//(�I�[�o�[���[�h
//=============================================================================
HRESULT CToy::LoadXfile(LPCSTR strFileName, int nCnt)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	
	// ���f���Ɋւ���ϐ��̏�����							
	CToy::m_pTexture[nCnt] = NULL;		// �e�N�X�`���ւ̃|�C���^
	CToy::m_pD3DXMesh[nCnt] = NULL;		// ���b�V�����ւ̃|�C���^
	CToy::m_pD3DXBuffMat[nCnt] = NULL;		// �}�e���A�����ւ̃|�C���^
	CToy::m_nNumMat[nCnt] = 0;			// �}�e���A�����̐�
	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(
		MODEL_FILENAME,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
		pDevice,					// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		&m_pD3DXBuffMat[nCnt],		// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		&m_nNumMat[nCnt],			// D3DXMATERIAL�\���̂̐�
		&m_pD3DXMesh[nCnt]			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		)))
	{
		return E_FAIL;
	}	


	return S_OK;
}

//=============================================================================
//x�t�@�C���̐ݒ�
//=============================================================================
void CToy::ChangePicked(bool pick, bool zebra)	
{
	m_bPicked = pick;
	m_bZebra = zebra ;
}
//=============================================================================
//
//=============================================================================
void CToy::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
//
//=============================================================================
void CToy::Update(void)
{
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	CScore *pScore;
	pScore = CZebraGame::GetScoreP();
	CDebugProc::Print("\n�g�C�̏ꏊ.x.y.z:%f,%f,%f",pos.x,pos.y,pos.z);
	if(m_bPicked == true && m_bZebra == false)
	{
		//�J�[�\���̈ʒu���擾
		for(int Cnt=0; Cnt<MAX_SCENE ; Cnt++)
		{
			CScene *pScene;
			pScene = CScene::GetScene(Cnt);
			if(pScene != NULL)
			{
				CScene::OBJTYPE type;
				type = pScene -> GetObjType();
				if(type == CScene::OBJTYPE_POINT)
				{
					D3DXVECTOR3 Cursorpos;
					Cursorpos = ((CPoint3D*)pScene)->Get3DPosition();
					
					Cursorpos.y = 20.0f;
					pos = Cursorpos;
					CSceneX::SetPosition(pos);
					return;
				}
			}
		}	
	}

	if(m_bPicked == true && m_bZebra == true)
	{
		CDebugProc::Print("\n�[�u��");
	}
	else if(m_bPicked == false)
	{
		if(pos.y>=0.0f)
		{
			pos.y -= 3.0f;
			CSceneX::SetPosition(pos);
		}
		if(pos.z >200.0)
		{
			pScore ->AddScore (100);
			Uninit();
		}
	}
}

//=============================================================================
//
//=============================================================================
void CToy::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
//
//=============================================================================
CToy *CToy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float speed)
{
	CToy *pToy;
	pToy = new CToy;
	pToy->Init(pos, rot, scl, speed);

	return pToy;
}
