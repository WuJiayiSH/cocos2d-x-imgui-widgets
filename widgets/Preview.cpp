#include "Preview.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "Editor.h"
#include "NodeFactory.h"
#include "Helper.h"

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

        return true;
    }

    void Preview::draw(bool* open)
    {
        if (ImGui::Begin(getDisplayName().c_str(), open, ImGuiWindowFlags_MenuBar))
        {
            if (ImGui::BeginMenuBar())
            {
                

                ImGui::EndMenuBar();
            }

            
            if (Texture2D* texture = getRenderTexture())
            {
                const unsigned int wide = texture->getPixelsWide();
                const unsigned int high = texture->getPixelsHigh();
                ImGui::Image((ImTextureID)texture->getName(), ImVec2((float)wide, (float)high));
            }

            _windowSize = ImGui::GetWindowSize();
        }

        ImGui::End();
    }

	void Preview::update(float)
	{
        if (!_camera->getParent())
            Editor::getInstance()->addChild(_camera);

        bool isRenderTextureDirty = true;
		if (Texture2D* texture = getRenderTexture())
        {
            const unsigned int wide = texture->getPixelsWide();
            const unsigned int high = texture->getPixelsHigh();
            if (std::abs(_windowSize.x - wide) < 1.0f || std::abs(_windowSize.y - high) < 1.0f)
                isRenderTextureDirty = false;
        }

        if (isRenderTextureDirty)
        {
            _camera->removeFromParent();
            _camera = Camera::createOrthographic(_windowSize.x, _windowSize.y, -1024, 1024);
            if (!_camera)
                return ;

            _camera->setCameraFlag(CameraFlag::USER1);
            _camera->setName(getDisplayName().c_str());
            Editor::getInstance()->addChild(_camera);
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

    cocos2d::Texture2D* Preview::getRenderTexture() const
    {
        if (!_camera)
			return nullptr;

		experimental::FrameBuffer* fbo = _camera->getFrameBufferObject();
		if (!fbo)
			return nullptr;

		experimental::RenderTargetBase* renderTarget = fbo->getRenderTarget();
		if (!renderTarget)
			return nullptr;

		return renderTarget->getTexture();
    }

    namespace
    {
        static WidgetFactory::AutoRegister<Preview> s_register(
            "CCImWidgets.Preview",
            "Built-in/Preview"
        );
    }
}


