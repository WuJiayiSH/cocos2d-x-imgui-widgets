#ifndef __CCIMGUIWIDGETMANAGER_H__
#define __CCIMGUIWIDGETMANAGER_H__

#include "cocos2d.h"
#include "CCImGuiWidget.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace CCImGuiWidgets
{
	class ImGuiWidgetManager : public cocos2d::Ref
	{
	public:
		template<typename T>
		struct AutoRegister
		{
			AutoRegister(const char* name, const char* description, const std::initializer_list<const char*>& dependencies)
			{
				auto widget = new T();
				widget->_name = name;
				widget->_description = description;
				for (const char* dependency : dependencies)
				{
					widget->_dependencies.push_back(dependency);
				}
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