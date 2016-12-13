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
#include "player2D.h"
#include "trajectory.h"
//============================================
// �}�N����`
//============================================
#define TEXTURE_TRASH "data/TEXTURE/�y�b�g�{�g��.png"
#define TEXTURE_BANANA "data/TEXTURE/banana.png"
#define TEXTURE_PAPER "data/TEXTURE/paper.png"

#define GRAVITY_POINT (0.98f)
#define WEIGHT_COEFFICIENT_LIGHT (0.5f)
#define WEIGHT_COEFFICIENT_HEAVY (3.0f)
//=============================================================================
// �\���̒�`
//=============================================================================


//�ÓI�����o�ϐ�
int CTrash::m_cnt = 0;
LPDIRECT3DTEXTURE9 CTrash::m_pTexture = NULL;

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
	m_gravityCoefficient = 1.0;
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
	//m_gravityCoefficient = 1.0;//1.0+rand()%4;//1.0~4.0�̃����_���Ȓl
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
	D3DXVECTOR3 posTrash = GetPosition();

	CDebugProc::Print("\n�ړ���.x,.y:%f,%f",m_speed.x,m_speed.y);

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
		//�ړ��ʂ̍ő�i�ŏ��j�͈͂�ݒ�
		if(m_speed.x > 200)
		{
			m_speed.x = 200;
		}
		else if(m_speed.y < -200)
		{
			m_speed.y = -200;
		}

	}
	if(m_fallFlag == true)
	{
		//�������ړ�
		posTrash.x += m_speed.x / 10;
		m_speed.y -= GRAVITY_POINT * m_gravityCoefficient;
		posTrash.y += -m_speed.y / 10;
	}
	if(m_apFlag == true)
	{
		//�o���^�C�~���O���J�E���g�Ōv��
		m_cnt++;
		if(m_cnt > 20)
		{
			//�V�����I�u�W�F�N�g�𐶐�
			int nNum = rand()%3;//�O�`�Q�̃����_���Ȑ�
			CScene2D* pTrash;
			if(nNum == 0)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 1)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 2)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_RIGHTTRASH);
				}
			}
			//�J�E���g�����Z�b�g
			m_cnt = 0;
			//��x�̓����łQ��ȏ�o�����Ȃ��悤�Ƀt���O���Ǘ�
			m_apFlag = false;
		}
	}
	this->CTrash::SetPosition(posTrash);
	
	if(posTrash.y > SCREEN_HEIGHT || posTrash.x > SCREEN_WIDTH || posTrash.x < 0)
	{//��ʊO����
		if(m_apFlag == true)//���̓����ɂ���čďo�����Ă��Ȃ��Ȃ�
		{
			//����
			CTrash* pTrash;
			int nNum = rand()%3;//�O�`�Q�̃����_���Ȑ�
			if(nNum == 0)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_BANANA,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 1)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_TRASH,OBJTYPE_RIGHTTRASH);
				}
			}
			else if(nNum == 2)
			{
				if(GetObjType() == OBJTYPE_TRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_TRASH);
				}
				else if(GetObjType() == OBJTYPE_LEFTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(100.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_LEFTTRASH);
				}
				else if(GetObjType() == OBJTYPE_RIGHTTRASH)
				{
					pTrash = CTrash::Create(D3DXVECTOR3(300.0f, 270.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f),TEXTURE_PAPER,OBJTYPE_RIGHTTRASH);
				}
			}
			CTrashGame::SetTrashPointer(pTrash);
			//�ďo�����Ȃ��悤�Ƀ��Z�b�g
			m_cnt = 0;
			m_apFlag = false;
		}
		m_fallFlag = false;
		//�j��
		this->Uninit();
	}
	
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
CTrash *CTrash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,LPCSTR strFileName,OBJTYPE type)
{
	CTrash *pTrash;
	pTrash = new CTrash;
	pTrash->Init(pos, size);
	pTrash->SetObjType(type);
	if(strFileName == TEXTURE_TRASH)
	{
		pTrash->m_gravityCoefficient = 2.0;
		pTrash->m_TrashType = TRASHTYPE_HEAVY;
	}
	else if(strFileName == TEXTURE_BANANA)
	{
		pTrash->m_gravityCoefficient = 1.7;
		pTrash->m_TrashType = TRASHTYPE_NORMAL;
	}
	else if(strFileName == TEXTURE_PAPER)
	{
		pTrash->m_gravityCoefficient = 0.7;
		pTrash->m_TrashType = TRASHTYPE_LIGHT;
	}
	//�e�N�X�`���̊��蓖��
	pTrash->Load(strFileName);
	
	//pTrash->CScene2D::BindTexture(m_pTexture);

	return pTrash;
}

D3DXVECTOR3 CTrash::GetSpeed(void)
{
	return m_speed;
}

void CTrash::SetSpeed(D3DXVECTOR3 speed)
{
	m_speed = speed;
}
	
void CTrash::ReverseMove(void)
{
	m_speed.x *= -1;
}

CTrash::TRASHTYPE CTrash::GetTrashType(void)
{
	return m_TrashType;
}