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
#include "trash.h"
#include "debugproc.h"
#include "score.h"
#include "trashBox.h"
#include "trashGame.h"
//============================================
// �}�N����`
//============================================
#define TEXTURENAME "data/TEXTURE/player000.png"
#define GRAVITY_POINT (0.98f)
#define WEIGHT_COEFFICIENT_LIGHT (0.5f)
#define WEIGHT_COEFFICIENT_HEAVY (3.0f)
//=============================================================================
// �\���̒�`
//=============================================================================


//�ÓI�����o�ϐ�
int CTrash::m_cnt = 0;


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTrash::CTrash()
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTrash::~CTrash()
{
	
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTrash::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	CScene2D::SetObjType(CScene::OBJTYPE_TRASH);
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fallFlag = false;
	m_cnt = 0;
	m_apFlag = false;
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTrash::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTrash::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//CTrash* pTrash;
	//CTrashBox2D* pTrashBox;
	D3DXVECTOR3 posTrash = GetPosition();
		//pTrash->GetPosition();
	//D3DXVECTOR3 sizeTrash = pTrash->GetSize();
	//D3DXVECTOR3 posTrashBox = GetPosition();
	//D3DXVECTOR3 sizeTrashBox = pTrashBox->GetSize();

	if(CManager::GetInputMouse()->GetMouseLeftPress() && m_fallFlag == false)
	{
		//�}�E�X�̈ړ��ʂ��擾
		m_speed.x -= CManager::GetInputMouse()->GetMouseAxisX()/3;
		m_speed.y += CManager::GetInputMouse()->GetMouseAxisY()/3;
	}

	if(CManager::GetInputMouse()->GetMouseLeftRelease() && m_fallFlag == false)
	{
		//�}�E�X��b�����痎���t���O���n�m
		m_fallFlag = true;
		//�o���t���O���n�m
		m_apFlag = true;
	}
	if(m_fallFlag == true)
	{
		//�������ړ�
		posTrash.x += m_speed.x / 10;
		m_speed.y -= GRAVITY_POINT * WEIGHT_COEFFICIENT_HEAVY;
		posTrash.y += -m_speed.y / 10;
	}
	if(m_apFlag == true)
	{
		//�o���^�C�~���O���J�E���g�Ōv��
		m_cnt++;
		if(m_cnt > 40)
		{
			//�V�����I�u�W�F�N�g�𐶐�
			CScene2D* pTrash;
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			//�J�E���g�����Z�b�g
			m_cnt = 0;
			//��x�̓����łQ��ȏ�o�����Ȃ��悤�Ƀt���O���Ǘ�
			m_apFlag = false;
		}
	}
	this->CTrash::SetPosition(posTrash);
	//�f�o�b�O�pprint
	/*PrintDebugProc("\nm_speed.x:%f",m_speed.x);
	PrintDebugProc("\nm_speed.y:%f",m_speed.y);
	PrintDebugProc("\nflag:%d",m_fallFlag);
	PrintDebugProc("\ncnt:%d",m_cnt);*/
	
	if(posTrash.y > SCREEN_HEIGHT)
	{//��ʊO����
		if(m_apFlag == true)//���̓����ɂ���čďo�����Ă��Ȃ��Ȃ�
		{
			CScene2D* pTrash;
			//����
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
			CTrashGame::SetTrashPointer(pTrash);
			//�ďo�����Ȃ��悤�Ƀ��Z�b�g
			m_cnt = 0;
			m_apFlag = false;
		}
		m_fallFlag = false;
		//CScore::ScoreUp(1);
		//�j��
		this->Uninit();
	}
	

	//�����蔻��
	/*if( (posTrash.y + sizeTrash.y/2 > posTrashBox.y - sizeTrash.y/2) &&
		(posTrash.y - sizeTrash.y/2 < posTrashBox.y + sizeTrash.y/2) &&
		(posTrash.x + sizeTrash.x/2 > posTrashBox.x - sizeTrash.x/2) &&
		(posTrash.x - sizeTrash.x/2 < posTrashBox.x + sizeTrash.x/2))
	{
		CScore::ScoreUp(1);
	}*/


	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTrash::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CTrash *CTrash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrash *pTrash;
	pTrash = new CTrash;
	pTrash->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pTrash->Load( TEXTURENAME);
	return pTrash;
}

