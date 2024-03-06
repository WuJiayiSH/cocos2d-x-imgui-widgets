#ifndef __CCIMWIDGETS_WIDGET_H__
#define __CCIMWIDGETS_WIDGET_H__

#include "cocos2d.h"

#include <vector>
#include <string>

namespace CCImWidgets
{
    class Widget: public cocos2d::Ref
    {
    public:
        friend class WidgetManager;
        friend class WidgetFactory;

        Widget();
        virtual ~Widget();

        bool init(const std::string& name, const std::string& displayName);

        const std::string& getName() const {return _name;}
        const std::string& getDisplayName() const {return _displayName;}

    private:
        void callback();
        virtual void draw() = 0;

        std::string _name;
        std::string _displayName;
    };
}

#endif