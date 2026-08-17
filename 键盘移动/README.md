📚 键盘控制 + 序列帧动画 —— 学习笔记
今日学习目标
掌握键盘控制角色移动（WASD）

学会用 bool 变量解决按键卡顿问题

学会边界限制，防止角色跑出窗口

巩固序列帧动画切换

核心概念
游戏主循环的四个步骤
text
1. 处理输入（键盘/鼠标） → 2. 更新逻辑（移动/动画） → 3. 绘制画面 → 4. 帧率控制
代码结构
text
main.cpp
├── 头文件（graphics.h / string）
├── 全局变量
│   ├── current_anim         // 当前播放到第几帧
│   ├── ANIMITION_COUNT      // 总帧数（6张）
│   ├── player_animition[]   // 存储6张图片
│   ├── player_pos           // 角色位置（POINT类型）
│   ├── PLAYER_SPEED         // 移动速度
│   ├── WINDOW_WIDTH/HEIGHT  // 窗口尺寸
│   ├── PLAYER_WIDTH/HEIGHT  // 角色尺寸
│   └── is_moving_*          // 移动状态（bool）
├── load_animition()
│   └── 循环加载 player_left_0~5.png
├── main()
│   ├── 初始化窗口
│   ├── 加载动画
│   ├── 主循环
│   │   ├── 帧率控制（60FPS）
│   │   ├── 消息处理（peekmessage）
│   │   │   ├── 按下（WM_KEYDOWN）→ bool = true
│   │   │   └── 松开（WM_KEYUP）→ bool = false
│   │   ├── 移动更新（根据bool状态）
│   │   ├── 边界限制（防止出界）
│   │   ├── 动画更新（每5帧切一次）
│   │   ├── 清屏 + 绘制当前帧
│   │   └── 双缓冲显示
│   └── 结束
关键代码解析
1. 键盘控制（bool 状态法）
cpp
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

📚 多方向动画 + 方向切换 —— 学习笔记
今日学习目标
掌握多方向动画加载（左/右）

学会根据移动方向切换动画

学会用 static 变量记录角色朝向

巩固序列帧动画切换逻辑

核心概念
动画方向切换原理
text
按下 A（左移）→ 播放左侧动画
按下 D（右移）→ 播放右侧动画
停止移动 → 保持上次朝向
代码结构
text
main.cpp
├── 头文件（graphics.h / string）
├── 全局变量
│   ├── current_anim              // 当前播放到第几帧
│   ├── ANIMITION_COUNT           // 总帧数（6张）
│   ├── player_left_animition[]   // 左侧动画（6张）
│   ├── player_right_animition[]  // 右侧动画（6张）
│   ├── player_pos                // 角色位置（POINT类型）
│   ├── PLAYER_SPEED              // 移动速度
│   ├── WINDOW_WIDTH/HEIGHT       // 窗口尺寸
│   ├── PLAYER_WIDTH/HEIGHT       // 角色尺寸
│   └── is_moving_*               // 移动状态（bool）
├── load_animition()
│   ├── 循环加载 player_left_0~5.png
│   └── 循环加载 player_right_0~5.png
├── main()
│   ├── 初始化窗口
│   ├── 加载动画
│   ├── 主循环
│   │   ├── 帧率控制（60FPS）
│   │   ├── 消息处理（peekmessage）
│   │   │   ├── 按下（WM_KEYDOWN）→ bool = true
│   │   │   └── 松开（WM_KEYUP）→ bool = false
│   │   ├── 移动更新（根据bool状态）
│   │   ├── 边界限制（防止出界）
│   │   ├── 方向判断（根据按键切换左右）
│   │   ├── 动画更新（每5帧切一次）
│   │   ├── 清屏 + 绘制当前帧
│   │   └── 双缓冲显示
│   └── 结束
关键代码解析
1. 加载多方向动画
cpp
IMAGE player_left_animition[ANIMITION_COUNT];
IMAGE player_right_animition[ANIMITION_COUNT];

void load_animition() {
    // 加载左侧动画
    for (int i = 0; i < ANIMITION_COUNT; i++) {
        wstring path = L"player_left_" + to_wstring(i) + L".png";
        loadimage(&player_left_animition[i], path.c_str());
    }
    // 加载右侧动画
    for (int i = 0; i < ANIMITION_COUNT; i++) {
        wstring path = L"player_right_" + to_wstring(i) + L".png";
        loadimage(&player_right_animition[i], path.c_str());
    }
}
2. 方向判断
cpp
static bool facing_left = false;  // 记录朝向，停止时保留
int dir_x = is_moving_right - is_moving_left;

if (dir_x < 0) {
    facing_left = true;   // 左移 → 朝左
}
else if (dir_x > 0) {
    facing_left = false;  // 右移 → 朝右
}
// dir_x == 0 时保持上次朝向
dir_x 取值表：

按键状态	is_moving_right	is_moving_left	dir_x	结果
按 A	0	1	-1	朝左
按 D	1	0	1	朝右
按 A+D	1	1	0	保持上次
没按	0	0	0	保持上次
3. 根据方向绘制不同动画
cpp
if (facing_left) {
    putimage(player_pos.x, player_pos.y, &player_left_animition[current_anim]);
} else {
    putimage(player_pos.x, player_pos.y, &player_right_animition[current_anim]);
}
4. 为什么用 static bool？
cpp
static bool facing_left = false;
不加 static	加 static
每次循环重置为 false	只初始化一次，保留上次值
停止时朝向被重置 ❌	停止时保留上次朝向 ✅

易错点 ⚠️
问题	原因	解决
停止时方向重置	没用 static 记录朝向	加 static bool facing_left
左右动画反了	逻辑写反	检查 dir_x < 0 是左还是右
两个方向同时加载慢	循环两次	正常，素材加载必须
动画不同步	current_anim 共用	左右共用同一个索引即可
学到的新知识 ✨
✅ 多方向动画加载（player_left_* 和 player_right_*）

✅ 方向判断：dir_x = is_moving_right - is_moving_left

✅ static 保留朝向：停止时保持上次方向

✅ 根据方向选择不同动画数组


运行方法
把 player_left_0~5.png 和 player_right_0~5.png 放在 main.cpp 同目录

Visual Studio 中编译运行

WASD 控制角色移动，左右自动切换动画

参考链接
EasyX 官方文档

学习日期：2026-08-17
状态：✅ 已掌握多方向动画切换

