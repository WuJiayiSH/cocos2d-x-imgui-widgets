# cocos2d-x-imgui-widgets
ImGui Widgets for Cocos2d-x

Install using git submodule:
    
    git submodule add https://github.com/WuJiayiSH/cocos2d-x-imgui-widgets.git frameworks\cocos2d-x-imgui-widgets

Update CMakeLists.txt:

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x-imgui-widgets)
    include(${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x-imgui-widgets/CMakeLists.txt)
    set(GAME_HEADER ${GAME_HEADER} ${CCIMGUI_WIDGETS_HEADER})
    set(GAME_SOURCE ${GAME_SOURCE} ${CCIMGUI_WIDGETS_SRC})

cocos2d-x-imgui-widgets has dependency on cocos2d-x-imgui, you also need to install it:
    
    git submodule add https://github.com/Xrysnow/cocos2d-x-imgui.git frameworks\cocos2d-x-imgui

Update CMakeLists.txt:

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x-imgui)
    target_link_libraries(${APP_NAME} cc_imgui)
    target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/cocos2d-x-imgui)
