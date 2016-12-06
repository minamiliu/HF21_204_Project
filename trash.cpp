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
#define TEXTURE_TRASH "data/TEXTURE/�y�b�g�{�g��.png"
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
	m_gravityCoefficient = 1.0;//1.0+rand()%4;//1.0~4.0�̃����_���Ȓl
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
			CScene2D* pTrash;
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));
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
			CTrash* pTrash;
			//����
			pTrash = CTrash::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));
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
CTrash *CTrash::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTrash *pTrash;
	pTrash = new CTrash;
	pTrash->Init(pos, size);

	//�e�N�X�`���̊��蓖��
	pTrash->Load(TEXTURE_TRASH);
	
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

