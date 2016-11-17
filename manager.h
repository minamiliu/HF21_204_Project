//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: manager.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/01
//
//============================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CCamera;
class CLight;

//============================================
//�\���̒�`
//============================================

class CManager
{
public:
	typedef enum
	{
		TYPE_LOADING = 0, // ���[�f�B���O
		TYPE_LOGO, // ���S�\��
		TYPE_TITLE, // �^�C�g��
		TYPE_MANUAL, //�}�j���A��
		TYPE_SELECT, // �Z���N�g
		TYPE_GAME, // �Q�[��
		TYPE_ENDING, // �G���f�B���O
		TYPE_STAFFROLL, // �X�^�b�t���[��
		TYPE_RESULT, // ���U���g
		TYPE_QUIT, // �I��
		TYPE_MAX,	//�ő�l
	} TYPE;

	CManager();
	virtual ~CManager();
	
	virtual HRESULT InitProgram(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	virtual HRESULT Init(void);
	virtual void UninitProgram(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�����_���[
	static CRenderer *GetRenderer(void);

	//���͏���
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

	//�J����
	static CCamera *GetCamera(void);

	//��ʑJ��
	static CManager *SetScene(TYPE type);

private:
	//�����_���[
	static CRenderer *m_pRenderer;

	//���͏���
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;

	//���C�g
	static CLight *m_pLight;

	//�J����
	static CCamera *m_pCamera;

	//��ʑJ��
	static CManager *m_pSceneNow;
	static TYPE m_type;
};

#endif
