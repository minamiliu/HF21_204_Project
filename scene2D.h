//============================================
//
// 繧ｿ繧､繝医Ν:	 譛ｪ譚･蜑ｵ騾螻輔メ繝ｼ繝204
// 繝励Ο繧ｰ繝ｩ繝蜷・ scene2D.h
// 菴懈・閠・		 HAL譚ｱ莠ｬ繧ｲ繝ｼ繝蟄ｦ遘代蜉牙漉螳・
// 菴懈・譌･:       2016/10/21
//
//============================================

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//============================================
//繧､繝ｳ繧ｯ繝ｫ繝ｼ繝峨ヵ繧｡繧､繝ｫ
//============================================
#include "scene.h"

//============================================
//繝槭け繝ｭ螳夂ｾｩ
//============================================
// 鬆らせ繝輔か繝ｼ繝槭ャ繝・ 鬆らせ蠎ｧ讓兌2D] / 鬆らせ繧ｫ繝ｩ繝ｼ / 繝・け繧ｹ繝√Ε蠎ｧ讓・)
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define NUM_VERTEX (4)
#define NUM_POLYGON (2)


//============================================
//讒矩菴灘ｮ夂ｾｩ
//============================================
typedef struct
{
	D3DXVECTOR3 pos;	// 鬆らせ蠎ｧ讓・
	float rhw;			// 蠎ｧ讓吝､画鋤逕ｨ菫よ焚(1.0f縺ｧ蝗ｺ螳・
	D3DCOLOR col;		// 鬆らせ繧ｫ繝ｩ繝ｼ
	D3DXVECTOR2 tex;	// 繝・け繧ｹ繝√Ε蠎ｧ讓・
} VERTEX_2D;

class CScene2D : public CScene
{
public:

	CScene2D();
	CScene2D(LAYER layer);
	virtual ~CScene2D();

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 ptnSize);//繝代ち繝ｼ繝ｳ縺ｮ縺ゅｋ繝・け繧ｹ繝√Ε蟆ら畑
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//繝・け繧ｹ繝√Ε髢｢騾｣
	HRESULT Load(LPCSTR strFileName);
	void BindTexture( LPDIRECT3DTEXTURE9 pTexture);
	void SetTexture(int patX,int patY,int animPat);
	void ChangeTextureAnime( int nPatternAnim, D3DXVECTOR2 ptnSize, D3DXVECTOR2 ptnDivide); //繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ

	//鬆らせ繝・・繧ｿ髢｢騾｣
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);
	void SetColor(const D3DXCOLOR &col); //濶ｲ繧貞､画峩
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPCSTR strFileName);
	void SetTexture(LPCSTR strFileName);
	void SetAlpha(int alpha);
	void SetSize(D3DXVECTOR3 size);
		
	//繧ｹ繧ｯ繝ｭ繝ｼ繝ｫ逕ｨ
	typedef enum
	{
		SCL_UP = 0,
		SCL_DOWN,
		SCL_LEFT,
		SCL_RIGHT,
		SCL_MAX
	}SCL_TYPE;
	void Scl(float nValue,SCL_TYPE type);

private:

	LPDIRECT3DTEXTURE9		m_pTexture;		// 繝・け繧ｹ繝√Ε縺ｸ縺ｮ繝昴う繝ｳ繧ｿ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 鬆らせ繝舌ャ繝輔ぃ縺ｸ縺ｮ繝昴う繝ｳ繧ｿ
	bool m_bLoadTexture;					// 繝・け繧ｹ繝√Ε繧定ｪｭ縺ｿ霎ｼ繧薙□縺九←縺・°

	D3DXVECTOR3			m_pos;				// 繝昴Μ繧ｴ繝ｳ縺ｮ菴咲ｽｮ
	D3DXVECTOR3			m_size;				// 繝昴Μ繧ｴ繝ｳ縺ｮ繧ｵ繧､繧ｺ
};

#endif
