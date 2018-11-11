#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/TestFramework/TestFramework.h"

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"

#include "swGUI/TestFramework/Testers/Rendering/DrawingTester.h"
#include "swGUI/TestFramework/Utils/Mocks/Rendering/FakeDrawing.h"
#include "swGUI/TestFramework/Utils/Mocks/Media/FakeBrush.h"

using namespace sw;
using namespace sw::gui;


//====================================================================================//
//			Shaders updates	
//====================================================================================//

// ================================ //
// Tests Drawing class shader update functions (interface for derived classes).
// Shader should be loaded on first use and updated after flag NeedsShaderUpdate is set to true.
TEST_CASE( "GUI.Rendering.Drawing.Brush.UpdateShader", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();
	
	// Set first shader
	brush->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush.ps" );
	drawing->UpdateBrushShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	auto prevShader = renderingData.PixelShader;
	CHECK( renderingData.PixelShader != nullptr );

	// Change shader and check if ew shader was loaded.
	brush->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush2.ps" );
	REQUIRE( brush->NeedsShaderUpdate() == true );										// Update request should be set.

	drawing->UpdateBrushShader( framework.GetRenderingSystem()->GetShaderProvider(), brush.get() );
	CHECK( renderingData.PixelShader != nullptr );										// Shader was loaded.
	CHECK( renderingData.PixelShader != prevShader );									// Shader is different then previous shader.

	CHECK( brush->NeedsShaderUpdate() == false );										// Update function should reset update flag.
}

// ================================ //
// Tests Drawing class shader update functions (interface for derived classes).
// Shader should be loaded on first use and updated after flag NeedsShaderUpdate is set to true.
TEST_CASE( "GUI.Rendering.Drawing.Pen.UpdateShader", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();
	
	// Set first shader
	pen->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush.ps" );
	drawing->UpdatePenShader( framework.GetRenderingSystem()->GetShaderProvider(), pen.get() );

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	auto prevShader = renderingData.PixelShader;
	CHECK( renderingData.PixelShader != nullptr );

	// Change shader and check if ew shader was loaded.
	pen->SetShaderFunction( "WorkingDir-RenderingSystem/shaders/FakeBrush2.ps" );
	REQUIRE( pen->NeedsShaderUpdate() == true );										// Update request should be set.

	drawing->UpdatePenShader( framework.GetRenderingSystem()->GetShaderProvider(), pen.get() );
	CHECK( renderingData.PixelShader != nullptr );										// Shader was loaded.
	CHECK( renderingData.PixelShader != prevShader );									// Shader is different then previous shader.

	CHECK( pen->NeedsShaderUpdate() == false );										// Update function should reset update flag.
}


//====================================================================================//
//			Textures update	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Brush.UpdateTexture", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );

	brush->SetTextureFile( L"WorkingDir-RenderingSystem/textures/Tex1.png" );
	REQUIRE( brush->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdateBrushTexture( framework.GetResourceManager(), brush.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( brush->NeedsTextureUpdate() == false );

	brush->SetTextureFile( L"WorkingDir-RenderingSystem/textures/Tex2.png" );
	REQUIRE( brush->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdateBrushTexture( framework.GetResourceManager(), brush.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( brush->NeedsTextureUpdate() == false );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Pen.UpdateTexture", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );

	pen->SetTextureFile( L"WorkingDir-RenderingSystem/textures/Tex1.png" );
	REQUIRE( pen->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdatePenTexture( framework.GetResourceManager(), pen.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( pen->NeedsTextureUpdate() == false );

	pen->SetTextureFile( L"WorkingDir-RenderingSystem/textures/Tex2.png" );
	REQUIRE( pen->NeedsTextureUpdate() == true );										// Update request should be set.

	drawing->UpdatePenTexture( framework.GetResourceManager(), pen.get() );
	CHECK( renderingData.Texture != nullptr );
	CHECK( pen->NeedsTextureUpdate() == false );
}


//====================================================================================//
//			Constant buffers updates	
//====================================================================================//

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Brush.UpdateConstants", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr brush = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetBrushRenderingData( drawing.get() );
	REQUIRE( renderingData.BrushConstants == nullptr );

	drawing->UpdateBrushConstants( framework.GetResourceManager(), brush.get() );

	CHECK( renderingData.BrushConstants != nullptr );
}

// ================================ //
// 
TEST_CASE( "GUI.Rendering.Drawing.Pen.UpdateConstants", "[GUISystem][RenderingSystem][Drawing]" )
{
	TestFramework framework( 0, nullptr );	framework.Init();
	
	FakeDrawingPtr drawing = std::make_shared< FakeDrawing >();
	FakeBrushPtr pen = std::make_shared< FakeBrush >();

	auto& renderingData = CLASS_TESTER( Drawing )::GetPenRenderingData( drawing.get() );
	REQUIRE( renderingData.BrushConstants == nullptr );

	drawing->UpdatePenConstants( framework.GetResourceManager(), pen.get() );

	CHECK( renderingData.BrushConstants != nullptr );
}
