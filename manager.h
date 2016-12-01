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
class CSound;

//============================================
//�\���̒�`
//============================================

class CManager
{
public:
	typedef enum
	{
		MODE_NONE = -1,
		MODE_LOADING, // ���[�f�B���O
		MODE_LOGO, // ���S�\��
		MODE_TITLE, // �^�C�g��
		MODE_MANUAL, //�}�j���A��
		MODE_SELECT, // �Z���N�g
		MODE_GAME, // �Q�[��
		MODE_TRASHGAME,//�S�~�����Q�[��
		MODE_ENDING, // �G���f�B���O
		MODE_STAFFROLL, // �X�^�b�t���[��
		MODE_RESULT, // ���U���g
		MODE_QUIT, // �I��
		MODE_MAX,	//�ő�l
	} MODE;

	CManager();
	CManager(MODE type);
	virtual ~CManager();
	
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CManager *Create( MODE type, HINSTANCE hInstance, HWND hWnd, bool bWindow);
	static void UpdateAll(void);
	static void DrawAll(void);
	static void Release(void);

	//�����_���[
	static CRenderer *GetRenderer(void);

	//���͏���
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

	//�T�E���h
	static CSound *GetSound(void);

	//�J����
	static CCamera *GetCamera(void);

	//��ʑJ��
	static CManager *SetScene(MODE mode); //�t�F�[�h�Ȃ�
	static MODE GetNextScene(void); 
	static void SetNextScene(MODE mode); //�t�F�[�h����

protected:
	//�J����
	static CCamera *m_pCamera;

private:
	//�����_���[
	static CRenderer *m_pRenderer;

	//���͏���
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;

	//�T�E���h
	static CSound *m_pSound;

	//��ʑJ��
	static CManager *m_pSceneManager;
	static MODE m_modeNow;
	static MODE m_modeNext;

};

#endif
