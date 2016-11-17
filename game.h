//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: game.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/17
//
//============================================

#ifndef _GAME_H_
#define _GAME_H_

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

	CManager();
	virtual ~CManager();
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	//�����_���[
	static CRenderer *GetRenderer(void);

	//���͏���
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);

	//�J����
	static CCamera *GetCamera(void);

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


};

#endif
