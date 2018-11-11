/**
@file Geometry.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Geometry.h"





namespace sw {
namespace gui
{


// ================================ //
//
Geometry::Geometry		( bool sharedBuffer )
	:	m_sharedBuffer( sharedBuffer )
{}


// ================================ //
//
void			Geometry::InvalidateGeometry		()
{
	m_invalidateGeometry = true;
}

// ================================ //
//
void			Geometry::InvalidateConstants		()
{
	m_invalidateConstants = true;
}

// ================================ //
//
void			Geometry::InvalidateShader			()
{
	m_invalidateShader = true;
}

// ================================ //
//
void			Geometry::ShaderUpdated				()
{
	m_invalidateShader = false;
}

// ================================ //
//
void			Geometry::GeometryUpdated			()
{
	m_invalidateGeometry = true;
}

// ================================ //
//
void			Geometry::ConstantsUpdated			()
{
	m_invalidateConstants = true;
}


}	// gui
}	// sw
