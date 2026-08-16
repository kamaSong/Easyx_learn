# EasyX 井字棋（Tic-Tac-Toe）

使用 EasyX 图形库实现的经典井字棋游戏，支持双人对战。

## 功能特点
- 双人轮流下棋（O 和 X）
- 鼠标点击棋盘落子
- 自动判断胜负和平局
- 实时显示当前轮到哪一方
- 双缓冲绘制，无闪烁
- 帧率控制，降低 CPU 占用

## 操作方式
- 鼠标左键点击棋盘格子落子
- 游戏结束后弹出提示框

## 技术要点

### 1. 数据结构：二维数组存储棋盘

```cpp
char board_data[3][3] = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};
```

- `'-'` 表示空格
- `'O'` 表示玩家 O 的棋子
- `'X'` 表示玩家 X 的棋子

### 2. 鼠标坐标转换为棋盘索引

```cpp
int index_x = x / 200;  // 窗口 600x600，每格 200x200
int index_y = y / 200;
```

利用整数除法自动向下取整，将像素坐标映射到 0-2 的棋盘坐标。

### 3. 胜负判断（CheckWin）

检查 8 种获胜情况：
- 3 条横线
- 3 条竖线
- 2 条对角线

```cpp
bool CheckWin(char c) {
    // 检查所有行、列、对角线
    // 有任意一条线全是 c，则 c 获胜
}
```

### 4. 平局判断（CheckDraw）

```cpp
bool CheckDraw() {
    // 遍历棋盘，如果没有 '-' 则平局
    // 全部占满且无人获胜
}
```

### 5. 双缓冲防止闪烁

```cpp
BeginBatchDraw();       // 创建后台缓冲区
cleardevice();          // 清空后台
drawBoard();            // 画棋盘
drawPiece();            // 画棋子
DrawTipText();          // 画提示文字
FlushBatchDraw();       // 一次性显示整帧
EndBatchDraw();         // 结束双缓冲
```

**原理**：所有绘制在后台缓冲区完成，`FlushBatchDraw()` 瞬间显示，避免清空到绘制的闪烁过程。

### 6. 帧率控制降低 CPU 占用

```cpp
DWORD start_time = GetTickCount();  // 帧开始时间
// ... 处理消息、绘制 ...
DWORD end_time = GetTickCount();    // 帧结束时间
DWORD delta_time = end_time - start_time;  // 本帧耗时

if (delta_time < 1000 / 60) {       // 期望 60 帧
    Sleep(1000 / 60 - delta_time);  // 补足剩余时间
}
```

### 7. 棋子绘制

```cpp
// O 棋子：圆形
circle(200 * j + 100, 200 * i + 100, 80);

// X 棋子：两条对角线
line(200 * j + 20, 200 * i + 20, 200 * (j + 1) - 20, 200 * (i + 1) - 20);
line(200 * (j + 1) - 20, 200 * i + 20, 200 * j + 20, 200 * (i + 1) - 20);
```

### 8. 文字提示

```cpp
_stprintf_s(str, _T("当前棋子类型:%c"), cur_piece);
settextcolor(RGB(225, 175, 45));
outtextxy(0, 0, str);
```

### 9. 消息框弹出结果

```cpp
MessageBox(GetHWnd(), _T("玩家X获胜"), _T("游戏结束"), MB_OK);
```

- `GetHWnd()` 获取 EasyX 窗口句柄
- 阻塞式，关闭后才继续执行

### 10. 棋盘绘制

```cpp
line(200, 0, 200, 600);   // 竖线1
line(400, 0, 400, 600);   // 竖线2
line(0, 200, 600, 200);   // 横线1
line(0, 400, 600, 400);   // 横线2
```

## 开发中遇到的问题

| 问题 | 原因 | 解决方法 |
|------|------|---------|
| 结束时不显示最后棋子 | 绘制顺序问题 | 先绘制，再判断胜负 |
| CPU 占用过高 | while 循环无限制 | GetTickCount + Sleep 控制帧率 |
| 画面闪烁 | 清空到绘制有间隔 | 双缓冲 BeginBatchDraw/FlushBatchDraw |
| 编译报错 | 没取地址 | peekmessage(&msg) |

## 完整代码
见 `main.cpp`

## 运行环境
- Visual Studio 2019+
- EasyX 图形库