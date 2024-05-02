////////////////////////////////////////////////////////////////////////////////
// Filename: pointlightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POINTLIGHTCLASS_H_
#define _POINTLIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h> 

using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: PointLightClass
////////////////////////////////////////////////////////////////////////////////
class PointLightClass
{
public:
	PointLightClass();
	PointLightClass(const PointLightClass&);
	~PointLightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetPosition(float, float, float);

	XMFLOAT4 GetDiffuseColor();
	XMFLOAT4 GetPosition();

private:
	XMFLOAT4 m_diffuseColor;
	XMFLOAT4 m_position;
};

#endif