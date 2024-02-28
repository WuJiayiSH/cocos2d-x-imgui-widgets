#include "CCImWidgetManager.h"

namespace CCImWidgets
{
    CCImWidgetManager* CCImWidgetManager::getInstance()
    {
        static CCImWidgetManager* instance = new CCImWidgetManager();
        return instance;
    }

    void CCImWidgetManager::draw()
    {
        for (const std::pair<std::string, cocos2d::RefPtr<CCImWidget>>& p : _widgets)
        {
            p.second->draw();
        }
    }

    bool CCImWidgetManager::load()
    {
        CCIMGUI::getInstance()->addCallback(
            std::bind(&ImGuiWidget::draw, this, std::placeholders::_1),
            getName()
            );
    }
}
