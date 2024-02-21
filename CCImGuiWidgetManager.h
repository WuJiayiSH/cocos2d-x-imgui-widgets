#ifndef __CCIMGUIWIDGETMANAGER_H__
#define __CCIMGUIWIDGETMANAGER_H__

#include "cocos2d.h"
#include "CCImGuiWidget.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace CCImGuiWidgets
{
    class ImGuiWidgetManager: public cocos2d::Ref
    {
    public:
        template<typename T>
        struct AutoRegister
        {
            AutoRegister(const std::string& name, const std::string& description, const std::vector<std::string>& dependencies)
            {
                auto widget = new T();
                widget->_name = name;
                widget->_description = description;
                widget->_dependencies = dependencies;
                ImGuiWidgetManager::getInstance()->_widgets.emplace(name, widget);
            }
        };

        static ImGuiWidgetManager* getInstance();
        ImGuiWidget* getWidget(const std::string& name);

        bool load();
        void update(float dt);
        void draw();
    private:
        ImGuiWidgetManager() {};
        ~ImGuiWidgetManager();
        std::unordered_map<std::string, ImGuiWidget*> _widgets;
    };
}

#endif