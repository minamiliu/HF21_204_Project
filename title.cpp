//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: title.cpp
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "scene2D.h"

//#include "zebra.h"
//#include "gorira.h"
//#include "lion.h"
#include "titleObj.h"
#include "sound.h"
//============================================
// �}�N����`
//============================================
//#define TEXTURE_BG "data/TEXTURE/�T�o���i�^�C�g���p/�w�i/titleBg.png"

#define LOGO_ROTATE (100)
//============================================
// �ÓI�����o�[�ϐ��̏�����
//============================================


//============================================
//�R���X�g���N�^
//============================================
CTitle::CTitle() : CManager(MODE_TITLE)
{
	
}

CTitle::~CTitle()
{
	
}

HRESULT CTitle::Init(void)
{

	//�I�u�W�F�N�g�̐���(2D�|���S��)
	//CScene2D::Create( D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), TEXTURE_BG);

	//
	//CZebra::Create(D3DXVECTOR3( SCREEN_WIDTH + 600, SCREEN_HEIGHT-250, 0.0f), D3DXVECTOR3(300, 200, 0.0f));
	//CGorira::Create(D3DXVECTOR3( SCREEN_WIDTH + 300, SCREEN_HEIGHT-230, 0.0f), D3DXVECTOR3(160, 140, 0.0f));
	//CLion::Create(D3DXVECTOR3( SCREEN_WIDTH + 900, SCREEN_HEIGHT-225, 0.0f), D3DXVECTOR3(230, 220, 0.0f));

	//�w�i
	CTitleObj::Create(CTitleObj::TITLE_BG,D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f),D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//���S
	CTitleObj::Create(CTitleObj::TITLE_LOGO,D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT/4, 0.0f),D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(7.5*LOGO_ROTATE, 1.45*LOGO_ROTATE, 0.0f));
	//��������
	CTitleObj::Create(CTitleObj::TITLE_ZEBRA,D3DXVECTOR3( SCREEN_WIDTH + 600, SCREEN_HEIGHT-250, 0.0f),D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(300, 200, 0.0f));
	CTitleObj::Create(CTitleObj::TITLE_GORIRA,D3DXVECTOR3( SCREEN_WIDTH + 300, SCREEN_HEIGHT-230, 0.0f),D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(160, 140, 0.0f));
	CTitleObj::Create(CTitleObj::TITLE_LION,D3DXVECTOR3( SCREEN_WIDTH + 900, SCREEN_HEIGHT-225, 0.0f),D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(230, 220, 0.0f));
	
	CTitleObj::Create(CTitleObj::TITLE_START,D3DXVECTOR3( SCREEN_WIDTH/2, SCREEN_HEIGHT*6/7, 0.0f),D3DXVECTOR3(0, 0, 0.0f), D3DXVECTOR3(13.7* LOGO_ROTATE/3, 3 * LOGO_ROTATE/3, 0.0f));

	//BGM
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

void CTitle::Uninit()
{
	//BGM
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

	CManager::Uninit();
}

void CTitle::Update()
{
	//���͂Ȃǂ̍X�V�A�e�V�[����Update�̍ŏ��ɌĂяo��
	CManager::Update();

	//�V�[���X�L�b�v
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	if( pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputMouse->GetMouseLeftTrigger())
	{
		SetNextScene( MODE_STAGE_START);
	}

	//�V�[�����؂�ւ���Ƃ���A�e�V�[����Update�̍Ō�ɒu���Ƃ�
	CManager::SceneChange();
}
void CTitle::Draw()
{
	CManager::Draw();
}
