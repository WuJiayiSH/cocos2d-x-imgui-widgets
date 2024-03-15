#ifndef __CCIMWIDGETS_EDITOR_H__
#define __CCIMWIDGETS_EDITOR_H__

#include <string>

#include "cocos2d.h"

#include "Widget.h"

namespace CCImWidgets
{
    class Editor: public cocos2d::Node
    {
    public:
        static Editor* getInstance();

        Ref* getUserObject(const std::string& path) { return _userObjects[path]; };
        
        void setUserObject(const std::string& path, Ref* handle) { _userObjects[path] = handle; };

        void onEnter() override;
        void onExit() override;
        
        void addWidget(Widget*);
    private:
        Editor();
        ~Editor();
        
        Editor(const Editor&) = delete;
        void operator=(const Editor&) = delete;

        void update(float) override;

        bool init();
        std::unordered_map<std::string, cocos2d::WeakPtr<cocos2d::Ref>> _userObjects;
        std::vector<cocos2d::RefPtr<Widget>> _widgets;
        
    };
}

#endif