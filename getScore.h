//============================================
//
// �^�C�g��:	 �����n���W�`�[��204
// �v���O������: getScore.h
// �쐬��:		 HAL�����Q�[���w�ȁ@�R�ƌ[��
// �쐬��:       2016/12/13
//
//============================================

#ifndef _GETSCORE_H_
#define _GETSCORE_H_

//============================================
//�C���N���[�h�t�@�C��
//============================================
#include "scene.h"

//============================================
//�}�N����`
//============================================

//============================================
//�O���錾
//============================================
class CNumber;

//============================================
//�\���̒�`
//============================================

class CGetScore : public CScene
{
public:

	CGetScore();
	virtual ~CGetScore();
	virtual HRESULT Init(void);
	virtual HRESULT Init(D3DXVECTOR3 numberPos, D3DXVECTOR3 numberSize, int maxKeta, const D3DXCOLOR &col);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CGetScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int maxKeta, const D3DXCOLOR &col);
	HRESULT Load(void);
	void Unload(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetScore(int score); //���������̂܂ܕ\������
	void SetColor(const D3DXCOLOR &col); //�S���̐F����C�ɕύX
	void AddScore(int score); //���_���グ��

protected:
	void BindAllTexture(void);

private:
	//�֐�
	void SetKetaTexture(const int keta, const int texNo);

	//�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;
	CNumber **m_ppPolygon;	//�������Ǘ�����|�C���^�[
	int m_nMaxKeta;			//����
	int m_nValue;			//�X�R�A
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	int m_nApCnt;//�������ĉ�F�o������
};

#endif