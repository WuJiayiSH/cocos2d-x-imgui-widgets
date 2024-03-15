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
        friend class WidgetFactory;
		friend class Editor;

        const std::string& getName() const {return _name;}
        const std::string& getDisplayName() const {return _displayName;}

    protected:
        Widget();
        virtual ~Widget();

        virtual bool init(const std::string& name, const std::string& displayName, size_t count);

    private:
        virtual void draw() = 0;
        virtual void update(float) {};

        std::string _name;
        std::string _displayName;
    };
}

#endif