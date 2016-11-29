//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: number.h
// �쐬��:		 HAL�����Q�[���w�ȁ@����G
// �쐬��:       2016/11/25
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

//============================================
//�\���̒�`
//============================================

class CNumber : public CScene2D
{
public:

	CNumber();
	virtual ~CNumber();

	HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	void SetNumber(const int score); //���������̂܂ܕ\������
	//void SetColor(const D3DXCOLOR &col); //�S���̐F����C�ɕύX

private:
	//�֐�
	void SetKetaTexture(const int keta, const int texNo);

	//�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D **m_ppPolygon;
	int m_nMaxKeta;

	int m_nCntFrame;
	int m_nCntTime;
};

#endif
