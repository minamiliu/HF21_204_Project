//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: scene2D.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _CHANGETEX_H_
#define _CHANGETEX_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D_CHANGETEX	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)


//============================================
//�\���̒�`
//============================================
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D_CHANGETEX;

class CChangeTex : public CScene
{
public:

	CChangeTex();
	virtual ~CChangeTex();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);//�p�^�[���̂���e�N�X�`����p
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//�e�N�X�`���֘A
	HRESULT Load(LPCSTR strFileName);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(int patX,int patY,int animPat);
	void ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide); //�A�j���[�V����

	//���_�f�[�^�֘A
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetColor(const D3DXCOLOR &col); //�F��ύX
	static CChangeTex *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName);
	void SetTexture(LPCSTR strFileName);
	void SetAlpha(int alpha);
	void SetSize(D3DXVECTOR3 size);
private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	bool m_bLoadTexture;					// �e�N�X�`����ǂݍ��񂾂��ǂ���

	D3DXVECTOR3			m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3			m_size;				// �|���S���̃T�C�Y
};

#endif
