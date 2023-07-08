# 地鐵跑酷



---
靈感來源于Ava做的游戲：[一周內做了，山寨版地鐵跑酷 | Unity 遊戲開發](https://www.youtube.com/watch?v=0tItdC1xwcM&list=PLKcM8_6ZrNaSlWq2FbU716_jNLSe5cqd8)

Ava的頻道[@AvaLab](https://www.youtube.com/@AvaLab)

---

## 部署方式
* 添加環境變量COCOS_HOME 目標為Cocos2d-x根目錄
* Run Bash:
```bash
mkdir -p build
cd build
cmake ..
make -j8
```

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
