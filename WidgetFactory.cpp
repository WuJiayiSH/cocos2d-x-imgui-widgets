#include "WidgetFactory.h"
#include <sstream>

namespace CCImWidgets
{
    Widget* WidgetFactory::Creator::create() const
    {
        Widget* widget = _constructor();

        std::ostringstream oss;

        const std::string& displayName = getDisplayName();
        size_t lastSlash = displayName.find_last_of('/');
        oss << (lastSlash == std::string::npos ? displayName : displayName.substr(lastSlash + 1));
        oss << "###";
        oss << static_cast<void*>(widget); // use pointer address as unique name
        
        if (widget && widget->init(_name, oss.str(), _mask))
        {
            widget->autorelease();
            return widget;
        }

        delete widget;
        return nullptr;
    }

    WidgetFactory* WidgetFactory::getInstance()
    {
        static WidgetFactory* instance = new WidgetFactory();
        return instance;
    }

    Widget* WidgetFactory::createWidget(const std::string& name)
    {
        std::unordered_map<std::string, Creator>::iterator it = _creators.find(name);
        if (it != _creators.end())
        {
			Creator& creator = it->second;
			return creator.create();
        }
        
        return nullptr;
    }
}
