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

        experimental::FrameBuffer* fbo = experimental::FrameBuffer::create(1, 512, 512);
        if (!fbo)
            return false;

        experimental::RenderTarget* renderTarget = experimental::RenderTarget::create(512, 512);
        if (!renderTarget)
            return false;

        experimental::RenderTarget* depthStencilTarget = experimental::RenderTarget::create(512, 512, Texture2D::PixelFormat::D24S8);
        if (!depthStencilTarget)
            return false;

        fbo->attachRenderTarget(renderTarget);
        fbo->attachDepthStencilTarget(depthStencilTarget);
    
        _camera->setCameraFlag(CameraFlag::USER1);
        _camera->setFrameBufferObject(fbo);
        
        Editor::getInstance()->scheduleOnce([this](float)
        {
            Editor::getInstance()->addChild(_camera);
		}, 0, "addCamera");


        return true;
    }

    void Preview::draw()
    {
        if (!_camera)
            return;

        experimental::FrameBuffer* fbo = _camera->getFrameBufferObject();
        if (!fbo)
            return;

        experimental::RenderTarget* renderTarget = fbo->getRenderTarget();
        if (!renderTarget)
            return;

        Texture2D* texture = renderTarget->getTexture();
        if (!texture)
            return;
        
        ImGui::Image(texture->getName(), ImVec2(512, 512));
    }

    namespace
    {
        static WidgetFactory::AutoRegister<Preview> s_register(
            "CCImWidgets.Preview",
            "Built-in/Preview"
        );
    }
}


