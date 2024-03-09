#ifndef __CCIMWIDGETS_WIDGETFACTORY_H__
#define __CCIMWIDGETS_WIDGETFACTORY_H__

#include "Widget.h"

#include "cocos2d.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace CCImWidgets
{
    class WidgetFactory : public cocos2d::Ref
    {
    public:
        struct WidgetCreator
        {
            std::string _name;
            std::string _displayName;
            std::function<Widget*()> _ctor;
            uint32_t _count;
		};
    
        template <typename T>
        struct AutoRegister
        {
            AutoRegister(const char* name, const char* displayName)
            {
                WidgetCreator& creator = WidgetFactory::getInstance()->_widgetCreators[name];
                creator._name = name;
                creator._displayName = displayName;
				creator._ctor = []() -> Widget* {return new (std::nothrow)T(); };
                creator._count = 0;
            }
        };

        const std::unordered_map<std::string, WidgetCreator>& getCreators() { return _widgetCreators; };
        Widget* createWidget(const std::string& name);
        
        static WidgetFactory* getInstance();

    private:
        std::unordered_map<std::string, WidgetCreator> _widgetCreators;
    };
}

#endif