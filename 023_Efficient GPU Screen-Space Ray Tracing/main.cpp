#include "Interface.h"
#include "Sponza.h"
#include "GBufferPass.h"
#include "ScreenSpaceRayTracingPass.h"
#include "ScreenQuadPass.h"
int main()
{
	ElayGraphics::WINDOW_KEYWORD::setWindowSize(1920, 1152);
	ElayGraphics::WINDOW_KEYWORD::setSampleNum(4);
	ElayGraphics::WINDOW_KEYWORD::setIsCursorDisable(true);
	ElayGraphics::COMPONENT_CONFIG::setIsEnableGUI(false);

	ElayGraphics::ResourceManager::registerGameObject(std::make_shared<CSponza>("Sponza", 1));
	ElayGraphics::ResourceManager::registerGameObject(std::make_shared<CDynamicObject>("DynamicObject", 2));

	ElayGraphics::ResourceManager::registerRenderPass(std::make_shared<GBufferPass>("SponzaGBufferPass", 0));
	ElayGraphics::ResourceManager::registerRenderPass(std::make_shared<CScreenSpaceRayTracingPass>("ScreenSpaceRayTracingPass", 1));
	ElayGraphics::ResourceManager::registerRenderPass(std::make_shared<CScreenQuadPass>("ScreenQuadPass", 2));

	ElayGraphics::App::initApp();
	ElayGraphics::App::updateApp();

	return 0;
}