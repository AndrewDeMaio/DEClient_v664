//----------------------------------------------------------------------
// CD3DTextureEffect.h
//----------------------------------------------------------------------
// Using CDirect3D
// An effect is implemented by applying a texture to a rectangular area in a 2D Coordinate Space.
//
// When Draw() is executed,
// BeginScene() must already have been called,
// and it is assumed that an arbitrary Texture is already set.
//----------------------------------------------------------------------

#ifndef __CD3DTEXTUREEFFECT_H__
#define __CD3DTEXTUREEFFECT_H__

#include "CDirect3D.h"

class CD3DTextureEffect {
	public :
		CD3DTextureEffect();
		~CD3DTextureEffect();

		void		DrawEffect2D(RECT* pRect);

	protected :
		D3DTLVERTEX					m_TextureVertices[4];
};

#endif


