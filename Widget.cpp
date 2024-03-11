
#include "cocos2d.h"
#include "Widget.h"
#include "CCIMGUI.h"
#include <vector>
#include <string>
#include <inttypes.h>

namespace CCImWidgets
{
    Widget::Widget()
    {
    }
    
    Widget::~Widget()
    {
        CCIMGUI::getInstance()->removeCallback(_displayName);
    }

    bool Widget::init(const std::string& name, const std::string& displayName, size_t count)
    {
        _name = name;
        size_t slashIndex = displayName.rfind("/");
        if (slashIndex == std::string::npos)
        {
            _displayName = displayName;
        }
        else
        {
            _displayName = displayName.substr(slashIndex + 1);
        }
        
        _displayName.append("###");
        _displayName.append(_name);
        _displayName.append(".");
        char id[16];
        sprintf(id, "%" PRIu32, count);
        _displayName.append(id);

        CCIMGUI::getInstance()->addCallback(std::bind(&Widget::callback, this), _displayName);
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

