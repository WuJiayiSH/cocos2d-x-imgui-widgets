#ifndef __CCIMWIDGETS_EDITOR_H__
#define __CCIMWIDGETS_EDITOR_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class Editor: public cocos2d::Ref
    {
    public:
        static Editor* getInstance();

        Ref* getUserObject(const std::string& path) { return _userObjects[path]; };
        
        void setUserObject(const std::string& path, Ref* handle) { _userObjects[path] = handle; };

    private:
        Editor();
        ~Editor();
        
        Editor(const Editor&) = delete;
        void operator=(const Editor&) = delete;

        void draw();

        std::unordered_map<std::string, cocos2d::WeakPtr<Ref>> _userObjects;
    };
}

#endif