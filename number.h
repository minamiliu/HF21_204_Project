//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: number.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/10/21
//
//============================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene2D.h"

//============================================
//�}�N����`
//============================================

class CNumber
{
public:

	CNumber();
	virtual ~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);//�p�^�[���̂���e�N�X�`����p
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//�e�N�X�`���֘A
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);
	void ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide); //�A�j���[�V����

	//���_�f�[�^�֘A
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetColor(const D3DXCOLOR &col); //�F��ύX

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);

private:

	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	bool m_bLoadTexture;					// �e�N�X�`����ǂݍ��񂾂��ǂ���

	D3DXVECTOR3			m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3			m_size;				// �|���S���̃T�C�Y
};

#endif
