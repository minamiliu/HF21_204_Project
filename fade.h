//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: fade.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/19
//
//============================================

#ifndef _FADE_H_
#define _FADE_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================

//============================================
//�}�N����`
//============================================

//============================================
//�\���̒�`
//============================================

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_CHANGE,
		FADE_OUT,
		FADE_MAX
	}FADE;

	CFade();
	virtual ~CFade();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

	static void SetFade(void);
	
private:
	//�֐�
	static void SetAlpha(int alpha);

	//�ϐ�
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	static int m_nAlpha;
	static FADE m_state;
};

#endif
