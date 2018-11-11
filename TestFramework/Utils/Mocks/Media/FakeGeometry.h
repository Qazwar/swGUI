#pragma once
/**
@file FakeGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Media/Geometry/Geometry.h"


namespace sw {
namespace gui
{



/**@brief Mock geometry for tests.*/
class FakeGeometry : public Geometry
{
private:
protected:
public:
	explicit		FakeGeometry		() = default;
	virtual			~FakeGeometry		() = default;


public:

	virtual bool			HitTest			( const Point& point ) override;
	virtual bool			HitTest			( const Rect& rectangle ) override;

	virtual GeometryData	Generate		() override;
	virtual BufferRange		BufferData		() override;

	virtual std::wstring	ShaderFunctionFile	() override;
	virtual std::wstring	GeometryName		() override;
	virtual std::wstring	ConstantsName		() override;

};





}	// gui
}	// sw

