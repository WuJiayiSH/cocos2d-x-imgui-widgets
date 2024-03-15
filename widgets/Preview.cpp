#include "Preview.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "Editor.h"

using namespace cocos2d;

namespace CCImWidgets
{
    bool Preview::init(const std::string& name, const std::string& displayName, size_t count) 
    {
        if (!Widget::init(name, displayName, count))
            return false;
        
        _camera = Camera::create();
        if (!_camera)
            return false;

        _camera->setCameraFlag(CameraFlag::USER1);
        _camera->setName(displayName);

        Editor::getInstance()->scheduleOnce([this](float)
        {
            updateFrameBufferObject(1, 1);
            Editor::getInstance()->addChild(_camera);
		}, 0, displayName);

        return true;
    }

    void Preview::draw()
    {
        if (!_camera)
            return;

        experimental::FrameBuffer* fbo = _camera->getFrameBufferObject();
        if (!fbo)
            return;

        experimental::RenderTargetBase* renderTarget = fbo->getRenderTarget();
        if (!renderTarget)
            return;

        Texture2D* texture = renderTarget->getTexture();
        if (!texture)
            return;

        unsigned int wide = texture->getPixelsWide();
        unsigned int high = texture->getPixelsHigh();
        ImGui::Image((ImTextureID)texture->getName(), ImVec2((float)wide, (float)high));

		_windowSize = ImGui::GetWindowSize();
        
    }

	void Preview::update(float)
	{
		if (!_camera)
			return;

		experimental::FrameBuffer* fbo = _camera->getFrameBufferObject();
		if (!fbo)
			return;

		experimental::RenderTargetBase* renderTarget = fbo->getRenderTarget();
		if (!renderTarget)
			return;

		Texture2D* texture = renderTarget->getTexture();
		if (!texture)
			return;

		unsigned int wide = texture->getPixelsWide();
		unsigned int high = texture->getPixelsHigh();
		if (std::abs(_windowSize.x - wide) >= 1.0f || std::abs(_windowSize.y - high) >= 1.0f)
		{
			updateFrameBufferObject((unsigned int)_windowSize.x, (unsigned int)_windowSize.y);
		}
	}

    void Preview::updateFrameBufferObject(unsigned int width, unsigned int height)
    {
        experimental::FrameBuffer* fbo = experimental::FrameBuffer::create(1, width, height);
        if (!fbo)
            return;

        experimental::RenderTarget* renderTarget = experimental::RenderTarget::create(width, height);
        if (!renderTarget)
            return;

        experimental::RenderTarget* depthStencilTarget = experimental::RenderTarget::create(width, height, Texture2D::PixelFormat::D24S8);
        if (!depthStencilTarget)
            return;

        fbo->attachRenderTarget(renderTarget);
        fbo->attachDepthStencilTarget(depthStencilTarget);

        _camera->setFrameBufferObject(fbo);
    }

    namespace
    {
        static WidgetFactory::AutoRegister<Preview> s_register(
            "CCImWidgets.Preview",
            "Built-in/Preview"
        );
    }
}


