# EasyX 学习：游戏框架基础

使用 EasyX 图形库搭建的游戏基础框架。

## 已完成功能

- 窗口初始化（1280×720）
- 背景图片加载与显示
- 游戏主循环
- 帧率控制（60 FPS）
- 键盘输入（WASD / ESC）
- 双缓冲绘制（无闪烁）
- 消息处理

## 操作方式

| 按键 | 功能 |
|------|------|
| `WASD` | 控制角色移动 |
| `ESC` | 退出游戏 |

## 运行方法

1. 安装 [EasyX 图形库](https://easyx.cn/)
2. 编译运行 `main.cpp`
3. 确保 `img/background.png` 存在

## 开发环境

- Visual Studio 2022
- EasyX 图形库

## 学习笔记

- `GetTickCount()` 控制帧率
- `BeginBatchDraw()` / `FlushBatchDraw()` 双缓冲
- `peekmessage()` 非阻塞消息处理