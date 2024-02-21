#ifndef __CCIMGUIWIDGET_H__
#define __CCIMGUIWIDGET_H__

#include <vector>
#include <string>

namespace CCImGuiWidgets
{
    class ImGuiWidget
    {
    public:
        friend class ImGuiWidgetManager;

        ImGuiWidget() {};
        virtual ~ImGuiWidget() {};

        const std::string& getName() const {return _name;}
        const std::string& getDescription() const {return _description;}
        const std::vector<std::string>& getDependencies() const {return _dependencies;}
        bool isLoaded() const {return _loaded;}

    private:
        virtual void onLoad();
        virtual void onUnload();
        virtual void onMessage() {};
        virtual void draw() {};

        std::string _name;
        std::string _description;
        std::vector<std::string> _dependencies;
        bool _loaded = false;
    };
}

#endif