#ifndef __CCIMWIDGET_H__
#define __CCIMWIDGET_H__

#include "cocos2d.h"

#include <vector>
#include <string>

namespace CCImWidgets
{
    class CCImWidget: cocos2d::Ref
    {
    public:
        friend class CCImWidgetManager;

        CCImWidget() {};
        virtual ~CCImWidget() {};

        const std::string& getName() const {return _name;}
        const std::string& getDescription() const {return _description;}
        bool isVisible() const { return _visible; }

    protected:
        bool _visible = true;

    private:
        virtual void draw() = 0;

        std::string _name;
        std::string _description;
    };
}

#endif