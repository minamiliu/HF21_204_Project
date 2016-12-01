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
#include "point2D.h"
#include "debugproc.h"
//============================================
// �}�N����`
//============================================
#define GRAVITY_POINT (0.98f)

//=============================================================================
// �\���̒�`
//=============================================================================
bool PointFlag = false;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPoint2D::CPoint2D()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPoint2D::~CPoint2D()
{
	
}


//=============================================================================
// �|���S���̏���������
//=============================================================================

HRESULT CPoint2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	m_hwnd=hwnd;
	CScene2D::Init(pos, size);
	m_startPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_endPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}




//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPoint2D::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CPoint2D::Update(void)
{
	//// �}�E�X���W�̎擾
	POINT po;
	GetCursorPos(&po);
	ScreenToClient(m_hwnd,&po);
	ShowCursor(FALSE);
	D3DXVECTOR3 pos ;
	if(CManager::GetInputMouse()->GetMouseLeftPress())
	{
	}

	if(CManager::GetInputMouse()->GetMouseLeftRelease())
	{
	}
	pos.x = po.x;
	pos.y = po.y;
	CPoint2D::SetPosition(D3DXVECTOR3(pos.x,pos.y,0.0f));
	CScene2D::Update();
	float print = CManager::GetInputMouse()->GetMouseAxisX();
	CDebugProc::Print("\n�J�[�\���̏ꏊ.x.y:%f,%f",pos.x,pos.y);
	//PrintDebugProc("\nm_startPos.y:%f",m_startPos.y);
	//PrintDebugProc("\nm_speed.x:%f",m_speed.x);
	//PrintDebugProc("\nm_speed.y:%f",m_speed.y);
	//PrintDebugProc("\nprint:%f",print);
	
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CPoint2D::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CPoint2D *CPoint2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,HWND hwnd)
{
	CPoint2D *pPoint2D;
	pPoint2D = new CPoint2D;
	pPoint2D->Init(pos, size,hwnd);
	
	return pPoint2D;
}

