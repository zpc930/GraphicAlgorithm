#include "ScreenSpaceRayTracingPass.h"
#include "Shader.h"
#include "Interface.h"
#include "Common.h"
#include "Utils.h"
#include "Sponza.h"
#include "AABB.h"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

CScreenSpaceRayTracingPass::CScreenSpaceRayTracingPass(const std::string& vPassName, int vExcutionOrder) : IRenderPass(vPassName, vExcutionOrder)
{
}

CScreenSpaceRayTracingPass::~CScreenSpaceRayTracingPass()
{
}

void CScreenSpaceRayTracingPass::initV()
{
	m_pShader = std::make_shared<CShader>("GBuffer_VS.glsl", "GBuffer_FS.glsl");
	m_pDynamicObjectShader = std::make_shared<CShader>("ScreenSpaceRayTracing_VS.glsl", "ScreenSpaceRayTracing_FS.glsl");

	m_pSponza = std::dynamic_pointer_cast<CSponza>(ElayGraphics::ResourceManager::getGameObjectByName("Sponza"));
	m_pDynamicObject = std::dynamic_pointer_cast<CDynamicObject>(ElayGraphics::ResourceManager::getGameObjectByName("DynamicObject"));


	auto TextureConfig4RayMarching = std::make_shared<ElayGraphics::STexture>();
	TextureConfig4RayMarching->InternalFormat = GL_RGBA32F;
	TextureConfig4RayMarching->ExternalFormat = GL_RGBA;
	TextureConfig4RayMarching->DataType = GL_FLOAT;
	genTexture(TextureConfig4RayMarching);

	m_FBO = genFBO({ TextureConfig4RayMarching });

	ElayGraphics::ResourceManager::registerSharedData("RayMarchingTexture", TextureConfig4RayMarching);


	m_pShader->activeShader();
	m_pShader->setMat4UniformValue("u_ModelMatrix", glm::value_ptr(m_pSponza->getModelMatrix()));
	m_pShader->setFloatUniformValue("u_Near", ElayGraphics::Camera::getMainCameraNear());
	m_pShader->setFloatUniformValue("u_Far", ElayGraphics::Camera::getMainCameraFar());
	m_pShader->setMat4UniformValue("u_TransposeInverseViewModelMatrix", glm::value_ptr(glm::transpose(glm::inverse(ElayGraphics::Camera::getMainCameraViewMatrix() *  m_pSponza->getModelMatrix()))));
	m_pSponza->initModel(*m_pShader);


	m_pDynamicObjectShader->activeShader();
	m_pDynamicObjectShader->setMat4UniformValue("u_ModelMatrix", glm::value_ptr(m_pSponza->getModelMatrix()));
	m_pDynamicObjectShader->setFloatUniformValue("u_Near", ElayGraphics::Camera::getMainCameraNear());
	m_pDynamicObjectShader->setFloatUniformValue("u_Far", ElayGraphics::Camera::getMainCameraFar());
	m_pDynamicObjectShader->setFloatUniformValue("u_DepthSize", 1920.0f,1152.0f);
	m_pDynamicObjectShader->setTextureUniformValue("u_DepthTexture", ElayGraphics::ResourceManager::getSharedDataByName<std::shared_ptr<ElayGraphics::STexture>>("DepthTexture"));
	m_pDynamicObjectShader->setTextureUniformValue("u_AlbedoTexture", ElayGraphics::ResourceManager::getSharedDataByName<std::shared_ptr<ElayGraphics::STexture>>("AlbedoTexture"));
	m_pDynamicObjectShader->setFloatUniformValue("u_WindowWidth", ElayGraphics::WINDOW_KEYWORD::getWindowWidth());
	m_pDynamicObjectShader->setFloatUniformValue("u_WindowHeight", ElayGraphics::WINDOW_KEYWORD::getWindowHeight());
	
}

void CScreenSpaceRayTracingPass::updateV()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	m_pShader->activeShader();
	m_pShader->setMat4UniformValue("u_TransposeInverseViewModelMatrix", glm::value_ptr(glm::transpose(glm::inverse(ElayGraphics::Camera::getMainCameraViewMatrix() *  m_pSponza->getModelMatrix()))));
	m_pSponza->updateModel(*m_pShader);

	m_pDynamicObjectShader->activeShader();
	m_pDynamicObjectShader->setMat4UniformValue("u_ModelMatrix", glm::value_ptr(m_pDynamicObject->getModelMatrix()));
	glm::vec3 CameraPos = ElayGraphics::Camera::getMainCameraPos();
	m_pDynamicObjectShader->setFloatUniformValue("u_CameraPosInWorldSpace", CameraPos.x, CameraPos.y, CameraPos.z);
	drawQuad();

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}