#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Runner)

project(${APP_NAME})

if (MSVC_VERSION GREATER_EQUAL "1900")
    message("Use MSVC")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_17_flag_supported)
    if (_cpp_17_flag_supported)
        add_compile_options("/std:c++17")
    endif()
else()
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)
endif()

set(BUILD_MESSAGE_TAG "${APP_NAME} BUILD: ")

function(appBuildLog l m)
    if (l STREQUAL e)
        message(FATAL_ERROR ${BUILD_MESSAGE_TAG} ${m})
    elseif (l STREQUAL w)
        message(${BUILD_MESSAGE_TAG} ${m})
    else()
        message(${BUILD_MESSAGE_TAG} ${m})
    endif()
endfunction()

#include(FetchContent)
#
#function(makeCocos)
#    appBuildLog("i" "Starting to clone cocos2d-x into ${CMAKE_CURRENT_SOURCE_DIR}/coco2d-x")
#    # start clone cocos2d-x
#    FetchContent_Declare(
#            "cocos2d-x"
#            GIT_REPOSITORY "https://github.com/monoliths-uni/cocos2d-x.git"
#            SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/coco2d-x"
#            GIT_TAG "origin/v4"
#            CONFIGURE_COMMAND ""
#            BUILD_COMMAND ""
#            INSTALL_COMMAND ""
#    )
#    FetchContent_MakeAvailable(cocos2d-x)
#endfunction()
#makeCocos()

# add build type debug
if (DEFINED CMAKE_BUILD_TYPE)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
#        appBuildLog("i" "Debug Draw")
#        Do not Use It, Because debug line Will Be Written In Render Image.
#        add_definitions(-DCC_SPRITE_DEBUG_DRAW=1)
    endif()
endif()


if (NOT DEFINED ENV{COCOS_HOME})
    # 必須先定義Cocos路徑
    appBuildLog("w" "Cocos Env{COCOS_HOME} Not Define!!! Please Read README.MD!")
#    makeCocos()
else()
    if (EXISTS $ENV{COCOS_HOME} AND EXISTS $ENV{COCOS_HOME}/cocos AND EXISTS $ENV{COCOS_HOME}/cmake)
        appBuildLog("i" "Find COCOS_HOME With '$ENV{COCOS_HOME}'")
    elseif()
        appBuildLog("i" "Cocos Path Error '$ENV{COCOS_HOME}', Has Not Cmake And cocos source code! ")
    endif()
endif()



# 使用LEGACY
if (NOT DEFINED OpenGL_GL_PREFERENCE)
    set(OpenGL_GL_PREFERENCE LEGACY)
endif()

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()

if(NOT DEFINED BUILD_ENGINE_DONE) # to test Runner into root project
    set(COCOS2DX_ROOT_PATH $ENV{COCOS_HOME})
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files
file(GLOB_RECURSE GAME_SOURCE "Classes/*.cc" "Classes/*.cpp" "Classes/*/*.cpp")
file(GLOB_RECURSE GAME_HEADER "Classes/*.h" "Classes/*/*.h")

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

remove_definitions(-DCOCOS2D_DEBUG)
if (DEFINED CMAKE_BUILD_TYPE)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        appBuildLog("i" "Debug Mode!")
        target_compile_definitions(${APP_NAME}
                PUBLIC $<$<CONFIG:Debug>:COCOS2D_DEBUG=2>)
    elseif(CMAKE_BUILD_TYPE STREQUAL Release)
        appBuildLog("d" "Relase Mode!")
        target_compile_definitions(${APP_NAME} PUBLIC $<$<CONFIG:Debug>:COCOS2D_DEBUG=0>)
    endif()
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if(MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
