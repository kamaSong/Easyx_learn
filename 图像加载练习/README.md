# EasyX 背景图片加载

使用 EasyX 加载并显示背景图片，包含帧率控制。

## 功能
- 加载 PNG 图片作为背景
- 双缓冲绘制，无闪烁
- 帧率控制，降低 CPU 占用

## 技术要点

### 1. 创建图像对象

```cpp
IMAGE img_background;
```

- `IMAGE` 是 EasyX 的图像类型，用于存储图片数据

### 2. 加载图片

```cpp
loadimage(&img_background, _T("background.png"));
```

- 第一个参数：`IMAGE` 对象的地址（`&` 取地址）
- 第二个参数：图片文件路径

### 3. 显示图片

```cpp
putimage(0, 0, &img_background);
```

- `(0, 0)` — 图片左上角在窗口中的坐标
- `&img_background` — 要显示的图片对象

### 4. 双缓冲防闪烁

```cpp
BeginBatchDraw();       // 创建后台缓冲区
cleardevice();          // 清空后台
putimage(0, 0, &img_background);  // 在后台绘制
FlushBatchDraw();       // 一次性显示到屏幕
EndBatchDraw();         // 结束
```

所有绘制在后台完成，`FlushBatchDraw()` 瞬间显示整帧，避免闪烁。

### 5. 帧率控制

```cpp
DWORD start_time = GetTickCount();  // 帧开始时间

// 处理 + 绘制

DWORD end_time = GetTickCount();    // 帧结束时间
DWORD delta_time = end_time - start_time;  // 本帧耗时

if (delta_time < 1000 / 60) {       // 期望 60 帧
    Sleep(1000 / 60 - delta_time);  // 补足剩余时间
}
```

**时间线**：
```
帧开始              帧结束          下一帧开始
  |---- 处理+绘制 ----|---- Sleep ----|
  |<-- delta_time -->|<-- 补足时间 -->|
  |<------------ 固定 16ms ---------->|
```

### 6. 主循环结构

```cpp
while (running) {
    DWORD start_time = GetTickCount();
    
    // 1. 处理消息
    // 2. 更新数据
    // 3. 清空画面
    // 4. 绘制内容
    // 5. 显示画面
    
    // 6. 帧率控制
    DWORD end_time = GetTickCount();
    DWORD delta_time = end_time - start_time;
    if (delta_time < 1000 / 60) {
        Sleep(1000 / 60 - delta_time);
    }
}
```

## 开发中遇到的问题

| 问题 | 原因 | 解决方法 |
|------|------|---------|
| 图片不显示 | 文件路径不对 | 图片放到项目文件夹 |
| 加载失败不报错 | 未检查返回值 | 加 if 判断 |
| 画面闪烁 | 未用双缓冲 | BeginBatchDraw + FlushBatchDraw |
| CPU 占用高 | 无帧率限制 | GetTickCount + Sleep |

## 完整代码
见 `main.cpp`

## 运行环境
- Visual Studio
- EasyX 图形库