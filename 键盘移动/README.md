# 📚 键盘控制 + 序列帧动画 —— 学习笔记

## 今日学习目标

- 掌握键盘控制角色移动（WASD）
- 学会用 bool 变量解决按键卡顿问题
- 学会边界限制，防止角色跑出窗口
- 巩固序列帧动画切换

---

## 核心概念

### 游戏主循环的四个步骤
处理输入（键盘/鼠标）

更新逻辑（移动/动画）

绘制画面

帧率控制

text

---

## 代码结构
main.cpp
├── 头文件（graphics.h / string）
├── 全局变量
│ ├── current_anim // 当前播放到第几帧
│ ├── ANIMITION_COUNT // 总帧数（6张）
│ ├── player_animition[] // 存储6张图片
│ ├── player_pos // 角色位置（POINT类型）
│ ├── PLAYER_SPEED // 移动速度
│ ├── WINDOW_WIDTH/HEIGHT // 窗口尺寸
│ ├── PLAYER_WIDTH/HEIGHT // 角色尺寸
│ └── is_moving_* // 移动状态（bool）
├── load_animition()
│ └── 循环加载 player_left_0~5.png
├── main()
│ ├── 初始化窗口
│ ├── 加载动画
│ ├── 主循环
│ │ ├── 帧率控制（60FPS）
│ │ ├── 消息处理（peekmessage）
│ │ │ ├── 按下（WM_KEYDOWN）→ bool = true
│ │ │ └── 松开（WM_KEYUP）→ bool = false
│ │ ├── 移动更新（根据bool状态）
│ │ ├── 边界限制（防止出界）
│ │ ├── 动画更新（每5帧切一次）
│ │ ├── 清屏 + 绘制当前帧
│ │ └── 双缓冲显示
│ └── 结束

text

---

## 关键代码解析

### 1. 键盘控制（bool 状态法）

```cpp
// 移动状态
bool is_moving_up = false;
bool is_moving_down = false;
bool is_moving_left = false;
bool is_moving_right = false;

// 消息处理
while (peekmessage(&msg)) {
    if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
        case 'W': is_moving_up = true; break;
        case 'S': is_moving_down = true; break;
        case 'A': is_moving_left = true; break;
        case 'D': is_moving_right = true; break;
        }
    }
    else if (msg.message == WM_KEYUP) {
        switch (msg.vkcode) {
        case 'W': is_moving_up = false; break;
        case 'S': is_moving_down = false; break;
        case 'A': is_moving_left = false; break;
        case 'D': is_moving_right = false; break;
        }
    }
}
2. 为什么用 bool 变量？
方式	效果	原因
❌ 直接移动	卡顿，动一下停一下	每次按键只触发一次
✅ bool 状态	按住一直动，松开立刻停	每帧检查状态，持续移动
3. 根据状态移动
cpp
if (is_moving_up) player_pos.y -= PLAYER_SPEED;
if (is_moving_down) player_pos.y += PLAYER_SPEED;
if (is_moving_left) player_pos.x -= PLAYER_SPEED;
if (is_moving_right) player_pos.x += PLAYER_SPEED;
4. 边界限制（防止出界）
cpp
const int WINDOW_WIDTH = 1270;
const int WINDOW_HEIGHT = 720;
const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;

if (player_pos.x < 0) player_pos.x = 0;
if (player_pos.x > WINDOW_WIDTH - PLAYER_WIDTH) player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
if (player_pos.y < 0) player_pos.y = 0;
if (player_pos.y > WINDOW_HEIGHT - PLAYER_HEIGHT) player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
图解：

text
窗口：1270 × 720    角色：50 × 50

允许范围：
X: 0 ~ 1220 (1270 - 50)
Y: 0 ~ 670  (720 - 50)

┌──────────────────────────┐
│  (0,0)                    │
│    ┌──────┐               │
│    │ 角色  │               │
│    │50×50 │               │
│    └──────┘               │
│                    (1220,670) ← 右下角极限位置
└──────────────────────────┘
5. 动画帧更新
cpp
static int count = 0;        // 静态变量，跨帧保留值
if (++count % 5 == 0) {      // 每5帧切换一次
    current_anim++;
}
current_anim = current_anim % ANIMITION_COUNT;  // 0~5 循环
完整代码
cpp
#include<graphics.h>
#include<string>
using namespace std;

int current_anim = 0;
const int ANIMITION_COUNT = 6;
IMAGE player_animition[ANIMITION_COUNT];

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;
const int WINDOW_WIDTH = 1270;
const int WINDOW_HEIGHT = 720;

POINT player_pos = { 500,500 };
const int PLAYER_SPEED = 3;

bool is_moving_up = false;
bool is_moving_down = false;
bool is_moving_left = false;
bool is_moving_right = false;

void load_animition() {
    for (int i = 0; i < ANIMITION_COUNT; i++) {
        wstring path = L"player_left_" + to_wstring(i) + L".png";
        loadimage(&player_animition[i], path.c_str());
    }
}

int main() {
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
    bool running = true;
    ExMessage msg;
    load_animition();
    BeginBatchDraw();

    while (running) {
        DWORD startTime = GetTickCount();

        while (peekmessage(&msg)) {
            if (msg.message == WM_KEYDOWN) {
                switch (msg.vkcode) {
                case 'W': is_moving_up = true; break;
                case 'S': is_moving_down = true; break;
                case 'A': is_moving_left = true; break;
                case 'D': is_moving_right = true; break;
                }
            }
            else if (msg.message == WM_KEYUP) {
                switch (msg.vkcode) {
                case 'W': is_moving_up = false; break;
                case 'S': is_moving_down = false; break;
                case 'A': is_moving_left = false; break;
                case 'D': is_moving_right = false; break;
                }
            }
        }

        if (is_moving_up) player_pos.y -= PLAYER_SPEED;
        if (is_moving_down) player_pos.y += PLAYER_SPEED;
        if (is_moving_left) player_pos.x -= PLAYER_SPEED;
        if (is_moving_right) player_pos.x += PLAYER_SPEED;

        if (player_pos.x < 0) player_pos.x = 0;
        if (player_pos.x > WINDOW_WIDTH - PLAYER_WIDTH) player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
        if (player_pos.y < 0) player_pos.y = 0;
        if (player_pos.y > WINDOW_HEIGHT - PLAYER_HEIGHT) player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;

        static int count = 0;
        if (++count % 5 == 0) {
            current_anim++;
        }
        current_anim = current_anim % ANIMITION_COUNT;

        cleardevice();
        putimage(player_pos.x, player_pos.y, &player_animition[current_anim]);
        FlushBatchDraw();

        DWORD endTime = GetTickCount();
        DWORD deltaTime = endTime - startTime;
        if (deltaTime < 1000 / 60) {
            Sleep((1000 / 60) - deltaTime);
        }
    }

    EndBatchDraw();
    return 0;
}
易错点 ⚠️
问题	原因	解决
按键没反应	用了 W 而不是 'W'	加单引号 'W'
移动卡顿	直接在消息里移动	用 bool 状态，在主循环移动
角色跑出窗口	没加边界限制	加 if 判断限制位置
角色消失一半	边界值算错	用 WINDOW_WIDTH - PLAYER_WIDTH
学到的新知识 ✨
✅ WM_KEYDOWN：键盘按下事件

✅ WM_KEYUP：键盘松开事件

✅ vkcode：按键码（'W'、'A'、VK_ESCAPE 等）

✅ bool 状态控制移动：按下 true，松开 false

✅ 边界限制：用常量和 if 判断

明日计划
□ 多方向动画（左/右/上/下）
□ 敌人系统
□ 碰撞检测
□ 攻击系统
运行方法
把 player_left_0~5.png 放在 main.cpp 同目录

Visual Studio 中编译运行

WASD 控制角色移动

参考链接
EasyX 官方文档

学习日期：2026-08-17
状态：✅ 已掌握键盘控制 + 边界限制
