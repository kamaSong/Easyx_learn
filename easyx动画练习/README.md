# 序列帧动画 —— 学习笔记 📖

## 今日学习目标

- 理解序列帧动画的原理
- 掌握 EasyX 中加载多张图片的方法
- 学会用静态变量控制动画切换
- 掌握宽字符（`wstring`）的使用

---

## 核心概念

### 什么是序列帧动画？

把一组图片按顺序快速切换，形成"动起来"的效果。类似翻书动画 📚

```
帧0 → 帧1 → 帧2 → 帧3 → 帧4 → 帧5 → 帧0 → 帧1 → ...
```

---

## 代码结构

```
main.cpp
├── 头文件（graphics.h / string）
├── 全局变量
│   ├── idx_current_anim   // 当前播放到第几帧
│   ├── ANIM_COUNT         // 总帧数（6张）
│   └── img_left[6]        // 存储6张图片
├── loadAnimation()
│   └── 循环加载 player_left_0~5.png
├── main()
│   ├── 初始化窗口
│   ├── 加载动画
│   ├── 主循环
│   │   ├── 帧率控制（60FPS）
│   │   ├── 消息处理（peekmessage）
│   │   ├── 动画更新（每5帧切一次）
│   │   ├── 清屏 + 绘制当前帧
│   │   └── 双缓冲显示
│   └── 结束
```

---

## 关键代码解析

### 1. 存储多张图片

```cpp
IMAGE img_left[ANIM_COUNT];  // 数组，存6张图
```

### 2. 加载图片（注意宽字符）

```cpp
wstring path = L"player_left_" + to_wstring(i) + L".png";
//  ↑ 必须加 L          ↑ int 转 wstring
loadimage(&img_left[i], path.c_str());
//                      ↑ wstring → const wchar_t*
```

### 3. 动画计数器（关键！）

```cpp
static int count = 0;        // 静态变量，跨帧保留值
if (++count % 5 == 0) {      // 每5帧切一次
    idx_current_anim++;
}
idx_current_anim = idx_current_anim % ANIM_COUNT;  // 循环 0~5
```

### 4. 绘制当前帧

```cpp
putimage(500, 500, &img_left[idx_current_anim]);
```

---

## 易错点 ⚠️

| 问题 | 原因 | 解决 |
|------|------|------|
| 图片加载失败 | 路径不对 / 文件名错误 | 检查图片是否在 exe 同目录 |
| 动画不动 | `count` 没用 `static` | 加 `static` 保留累加值 |
| 编译报错类型不匹配 | VS 默认 Unicode | 用 `wstring` + `L"..."` |
| 数组越界崩溃 | 索引超过 5 | 用 `% ANIM_COUNT` 限制 |

---

## 学到的新知识 ✨

- ✅ `static`：让变量跨函数调用保持值
- ✅ `wstring`：宽字符字符串（VS Unicode 默认）
- ✅ `to_wstring()`：int → wstring 转换
- ✅ `.c_str()`：wstring → const wchar_t*
- ✅ `%` 取模运算：实现循环

---

## 明日计划

- [ ] 键盘控制（WASD 切换方向）
- [ ] 多个方向动画（左/右/上/下）
- [ ] 角色移动
- [ ] 碰撞检测

---

## 运行方法

1. 把 `player_left_0~5.png` 放在 `main.cpp` 同目录
2. Visual Studio 中编译运行
3. 按 ESC 退出（如果需要）

---

## 参考链接

- [EasyX 官方文档](https://easyx.cn/doc/)
- [序列帧动画原理](https://baike.baidu.com/item/%E5%BA%8F%E5%88%97%E5%B8%A7%E5%8A%A8%E7%94%BB)

---

**学习日期**：2026-08-16  
**状态**：✅ 已掌握序列帧动画