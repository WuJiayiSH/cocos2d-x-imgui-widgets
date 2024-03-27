#ifndef __CCIMWIDGETS_EDITOR_H__
#define __CCIMWIDGETS_EDITOR_H__

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
        
        void addWidget(Widget* widget);
        Widget* getWidgetByName(const std::string& name) const;
        
        cocos2d::Node* getEditingNode() const { return _editingNode; };

   CC_CONSTRUCTOR_ACCESS: 
        Editor();
		~Editor();

    private:
        Editor(const Editor&) = delete;
        void operator=(const Editor&) = delete;

        bool init() override;
        void callback();
        void update(float) override;

        std::unordered_map<std::string, cocos2d::WeakPtr<cocos2d::Ref>> _userObjects;
        std::vector<cocos2d::RefPtr<Widget>> _widgets;
        cocos2d::WeakPtr<cocos2d::Node> _editingNode;
    };
}

#endif