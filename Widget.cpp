
#include "cocos2d.h"
#include "Widget.h"
#include "CCIMGUI.h"
#include <vector>
#include <string>

namespace CCImWidgets
{
    Widget::Widget()
    {
        
    }
    
    Widget::~Widget()
    {
        CCIMGUI::getInstance()->removeCallback(_name);
    }

    bool Widget::init(const std::string& name, const std::string& displayName)
    {
        _name = name;
        _displayName = displayName;
        CCIMGUI::getInstance()->addCallback(std::bind(&Widget::callback, this), _name);
        return true;
    }

    void Widget::callback()
    {
        bool open = true;
        if (ImGui::Begin(_displayName.c_str(), &open))
        {
            draw();
        }
        ImGui::End();

        if (!open)
            autorelease();
    }
}

