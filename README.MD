# 跑者
/// 不知道怎麽命名好www 先這樣吧
---
靈感來源于Ava做的游戲：[一周內做了，山寨版地鐵跑酷 | Unity 遊戲開發](https://www.youtube.com/watch?v=0tItdC1xwcM&list=PLKcM8_6ZrNaSlWq2FbU716_jNLSe5cqd8)

Ava的頻道[@AvaLab](https://www.youtube.com/@AvaLab)

因爲3D對於我這個專業不對口的初學者來説有點困難 www~~
所以我使用2D

---

## 部署方式
* 添加環境變量COCOS_HOME 目標為Cocos2d-x根目錄
* Run Bash:
```bash
#! Linux:
mkdir -p build
cd build
cmake ..
# Change Your Processor Number For Build project
make -j8
```

```bash
#! Windows:
mkdir build
cd build
# Change Your Visual Studio Version, If else
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug -A win32
# Change Your Processor Number For Build project
cmake --build . --target Runner --config Debug -j 10
```


## 游戲構思：
  使用文字來描述界面

## Class Map
- Scene
    - MenuScene : Scene
    - GameScene : Scene
    - EndScene : Scene
- Sprite
  - Player
  - AbstractObstacle
    - StaticObstacle
    - DynamicObstacle


## Features
- 建模任務
    - [ ] 人物建模
    - [ ] 地圖建模
    - [ ] 基礎障礙物建模
- 場景任務
    - [ ] 開始菜單
    - [ ] 游戲界面
    - [ ] 結束界面
