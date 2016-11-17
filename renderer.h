//============================================
//
// �^�C�g��:	 CL25�ۑ�
// �v���O������: renderer.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/19
//
//============================================

#ifndef _RENDERER_H_
#define _RENDERER_H_

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CRenderer
{
public:

	CRenderer();
	virtual ~CRenderer();

	LPDIRECT3DDEVICE9 GetDevice();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont;		// �t�H���g�ւ̃|�C���^
};

#endif