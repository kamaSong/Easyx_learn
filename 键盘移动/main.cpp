#include<graphics.h>
#include<string>
using namespace std;
int current_anim = 0;
const int ANIMITION_COUNT = 6;
IMAGE player_animition[ANIMITION_COUNT];
const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;
const int WINDOW_WIDTH = 1270;
CONST int WINDOW_HEIGHT = 720;
//角色位置
POINT player_pos = { 500,500 };
//移动要有速度
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
	initgraph(1270, 720);
	bool running = true;
	ExMessage msg;
	load_animition();
	BeginBatchDraw();

	while (running) {
		DWORD startTime = GetTickCount(); //获取当前时间戳
		//操作信息
		while (peekmessage(&msg)) {
			//移动操作 普通操作会出现卡顿，解决方法设置bool变量 ,按下后设置为true，松开后设置为false，移动时判断bool变量
			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {
				case 'W':
					is_moving_up = true;
					break;
				case 'S':
					is_moving_down = true;
					break;
				case 'A':
					is_moving_left = true;
					break;
				case 'D':
					is_moving_right = true;
					break;
				}
			

			}
			else if (msg.message == WM_KEYUP) {
				switch (msg.vkcode) {
				case'W':
					is_moving_up = false;
					break;
				case 'S':
					is_moving_down = false;
					break;
				case 'A':
					is_moving_left = false;
					break;
				case 'D':
					is_moving_right = false;
					break;
				}
			}
		}
		//根据bool变量移动角色
		if (is_moving_up) {
			player_pos.y -= PLAYER_SPEED;
		}
		if (is_moving_down) {
			player_pos.y += PLAYER_SPEED;
		}
		if (is_moving_left) {
			player_pos.x -= PLAYER_SPEED;
		}
		if (is_moving_right) {
			player_pos.x += PLAYER_SPEED;
		}
		//任务角色会出界,添加便捷限制
		if (player_pos.x < 0) player_pos.x = 0;
		if (player_pos.x > WINDOW_WIDTH - PLAYER_WIDTH)  player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
		if (player_pos.y < 0) player_pos.y = 0;
		if (player_pos.y > WINDOW_HEIGHT - PLAYER_HEIGHT)  player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
		//数据处理
		static int count = 0;
		if (++count % 5 == 0) {
			current_anim++;
		}
		current_anim = current_anim % ANIMITION_COUNT;

	//绘图
		cleardevice();
		putimage(player_pos.x, player_pos.y, &player_animition[current_anim]);
		FlushBatchDraw();


		DWORD endTime = GetTickCount(); //获取当前时间戳
		DWORD deltaTime = endTime - startTime; //计算时间差
		if (deltaTime < 1000 / 60) {
			Sleep((1000 / 60) - deltaTime); //如果时间差小于1/60秒，则休眠一段时间
		}
	}
	
	EndBatchDraw();
	return 0;
}