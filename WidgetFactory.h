#ifndef __CCIMWIDGETS_WIDGETFACTORY_H__
#define __CCIMWIDGETS_WIDGETFACTORY_H__

#include <string>
#include <unordered_map>
#include "cocos2d.h"

#include "Widget.h"

namespace CCImWidgets
{
    class WidgetFactory : public cocos2d::Ref
    {
    public:
        struct Creator
        {
            friend class WidgetFactory;
            
            Creator(const std::string& name, const std::string& displayName, const std::function<Widget*()>& constructor)
            : _name(name)
            , _displayName(displayName)
            , _constructor(constructor)
            , _count(0)
            {

            }

            const std::string& getName() const { return _name; };

            const std::string& getDisplayName() const { return _displayName; };
            
        private:
            std::string _name;
            std::string _displayName;
            std::function<Widget*()> _constructor;
            uint32_t _count;
		};
    
        template <typename T>
        struct AutoRegister
        {
            AutoRegister(const char* name, const char* displayName)
            {
                std::function<Widget*()> constructor = []() -> Widget* {return new (std::nothrow)T(); };
                WidgetFactory::getInstance()->_creators.emplace(name, Creator(name, displayName, constructor));
            }
        };

        const std::unordered_map<std::string, Creator>& getCreators() { return _creators; };

        Widget* createWidget(const std::string& name);

        static WidgetFactory* getInstance();

    private:
        std::unordered_map<std::string, Creator> _creators;
    };
}

#endif