#ifndef __CCIMWIDGETS_EDITOR_H__
#define __CCIMWIDGETS_EDITOR_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class Editor: public cocos2d::Ref
    {
    public:
        Editor();
        ~Editor();

        static Editor* getInstance();
    private:
        void draw() ;
    };
}

#endif