# 鼠标跟随小球

使用 EasyX 实现小球实时跟随鼠标移动的示例。

## 效果
- 小球圆心跟随鼠标位置移动
- 画面无闪烁、无拖尾

## 技术要点

### 1. 全局变量存储小球位置

​```cpp
int x = 300, y = 300;
​```

- 全局变量在消息循环和绘制循环之间共享数据
- 鼠标移动时更新坐标，绘制时使用最新坐标

### 2. 鼠标消息处理

​```cpp
ExMessage msg;
while (peekmessage(&msg)) {
    if (msg.message == WM_MOUSEMOVE) {
        x = msg.x;
        y = msg.y;
    }
}
​```

**关键点**：
- `peekmessage(&msg)` 取地址传入，函数内部会修改 `msg` 内容
- `WM_MOUSEMOVE` 是鼠标移动消息类型
- `msg.x` / `msg.y` 是鼠标当前坐标

### 3. 双缓冲解决闪烁

**问题**：不加双缓冲时，先清空屏幕再画圆，中间有短暂空白，产生闪烁。

**解决**：所有绘制在后台缓冲区完成，一次性显示。

​```cpp
BeginBatchDraw();
cleardevice();
solidcircle(x, y, 20);
FlushBatchDraw();
EndBatchDraw();
​```

### 4. 必须加 cleardevice()

不加 `cleardevice()` 的后果：每帧都在旧画面上叠加新圆，出现拖尾。

​```cpp
cleardevice();
solidcircle(x, y, 20);
​```

### 5. 主循环结构

​```cpp
while (true) {
    // 1. 处理消息
    // 2. 清空画面
    // 3. 绘制小球
    // 4. 显示画面
}
​```

## 开发中遇到的问题

| 问题 | 原因 | 解决方法 |
|------|------|---------|
| 出现很多圆 | 没清空画面 | 每帧先 `cleardevice()` |
| 圆闪烁 | 清空到绘制有间隔 | 双缓冲 |
| 编译报错 | 没取地址 | 改为 `peekmessage(&msg)` |

## 完整代码
见 `main.cpp`

## 运行环境
- Visual Studio
- EasyX 图形库