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

	virtual HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col);
	static HRESULT Load(void);
	static void Unload(void);

	void SetNumber(int score); //���������̂܂ܕ\������
	void SetColor(const D3DXCOLOR &col); //�S���̐F����C�ɕύX

protected:
	void BindAllTexture(void);

private:
	//�֐�
	void SetKetaTexture(const int keta, const int texNo);

	//�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2D **m_ppPolygon;
	int m_nMaxKeta;
};

#endif
