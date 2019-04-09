# tick-Qt-game
一个使用QT框架制作的双人非对称竞技游戏  
A Double Asymmetric Competitive Game Using the QT Framework  
  
点击[宣传视频](https://v.youku.com/v_show/id_XNDEyOTA1MjYyNA==.html?spm=a2hzp.8253869.0.0)快速了解  
  
## 安装&编译
  * QT版本 5.9.2  
  * IDE版本 4.4.1  
  * 编译环境 Desktop_Qt_5_9_2_MinGW_32bit-Debug  
  * BGM.mp3请放在编译生成的文件夹里  
  **请确认路径中不含中文**  
  
## 代码结构及注释  
**所有函数前均有注释**  
root:  
│  BGM.mp3    **背景音乐**  
│  game.cpp   **游戏主界面**  
│  game.h  
│  game.ui  
│  image.qrc  
│  introduction.cpp  **介绍界面**  
│  introduction.h  
│  introduction.ui  
│  main.cpp          **主函数**    
│  mainwindow.cpp  
│  mainwindow.h  
│  mainwindow.ui  
│  result.cpp        **结果界面**  
│  result.h  
│  result.ui  
│  setting.cpp      **设置界面**  
│  setting.h  
│  setting.ui  
│  sound.qrc  
│  start.cpp  
│  start.h  
│  start.ui  
│  ui_setting.h  
│  viewpainter.cpp  
│  viewpainter.h  
│  
├─logic                **底层逻辑**  
│      game_logic.cpp  **判定逻辑**  
│      game_logic.h  
│      game_map.cpp    **游戏地图**  
│      game_map.h  
│      
├─show_img             **展示图片**  
│      
└─sourse               **程序材质**  
  
  
## 游戏描述  
   游戏分为两个阵营，抓捕者和逃亡者，逃亡者无法对抓捕者造成伤害但抓捕者有能量限制，  
  移动和释放技能都会消耗能量，能量耗尽抓捕者就会死亡。逃亡者有三条生命，逃亡者被抓  
  捕者抓到或被抓捕者的大招技能命中会损失生命同时抓捕者会回复能量。逃亡者和抓捕者都  
  拥有三个技能，技能既可以帮自己脱离困境也有可能妨碍自己。他们各自拥有三个技能，并  
  且每个技能在使用之后都有相应的冷却时间，（左右两侧的进度条就是用于显示生效时间与  
  冷却时间，冷却中进度条会增长，生效时会减少），对于抓捕者来说技能的使用和移动次数  
  的增加都会减少其能量，当抓捕者能量耗尽时逃亡者获胜，进入结果界面。对于逃亡者来说  
  他一共有三条命，每次被抓捕者捕获后生命条数减一，同时抓捕者获得相应的能量奖励，当  
  逃亡者生命用尽则抓捕者获胜，进入结果接界面。  
  
## 技能博弈
  ![技能关系](https://github.com/inkeast/tick-Qt-game/blob/master/show_img/skill_related.png)  
  游戏突出非对称性，这一点主要体现在两个玩家不同的技能实现和对两者生命和能量的约束
  上，在Qt图形化方面实现了界面，人物，特效的自主构建，在逻辑层方面6大技能的实现是  
  增加游戏的平衡性， 竞技性是一大亮点，虽然对战的玩家会拥有不同的技能但是所有的技  
  能之间都是有相互的制约作用并且同一玩家的不同技能也会有相应的增益，至于效果主要  
  看玩家对技能的理解与对游戏环境的判断，这样能确保非对称情况下游戏的相对公平进而加  
  深游戏的深度和可玩性。
    
  ![skill_kill1](https://github.com/inkeast/tick-Qt-game/blob/master/show_img/skill_kill1.gif)
    
  ![skill_kill1](https://github.com/inkeast/tick-Qt-game/blob/master/show_img/skill_kill2.gif)
    
  ![skill_kill1](https://github.com/inkeast/tick-Qt-game/blob/master/show_img/skill_debuff.gif)
    
