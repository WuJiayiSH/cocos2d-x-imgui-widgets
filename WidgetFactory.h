#ifndef __CCIMWIDGETS_WIDGETFACTORY_H__
#define __CCIMWIDGETS_WIDGETFACTORY_H__

#include <string>
#include <unordered_map>

#include "Widget.h"

namespace CCImWidgets
{
	
    class WidgetFactory
    {
    public:
        struct Creator
        {
            friend class WidgetFactory;
            
            Creator(const std::string& name, const std::string& displayName, uint32_t mask, const std::function<Widget*()>& constructor)
            : _name(name)
            , _displayName(displayName)
            , _mask(mask)
            , _constructor(constructor)
            {
            }

            const std::string& getName() const { return _name; };

            const std::string& getDisplayName() const { return _displayName; };

            uint32_t getMask() const { return _mask; };

        private:
            std::string _name;
            std::string _displayName;
            uint32_t _mask;
            std::function<Widget*()> _constructor;
		};
    
        template <typename T>
        struct AutoRegister
        {
            AutoRegister(const char* name, const char* displayName, uint32_t mask = 0)
            {
                std::function<Widget*()> constructor = []() -> Widget* {return new (std::nothrow)T(); };
                WidgetFactory::getInstance()->_creators.emplace(name, Creator(name, displayName, mask, constructor));
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