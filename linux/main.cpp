#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/concept_check.hpp>
namespace fs=boost::filesystem;

#include <SDL/SDL.h>
#include <X11/Xlib.h>

#include <avplay.h>
#include "player.h"

static void play_thread(void *param)
{
//	avplayer *play = (avplayer*)param;
//	play->play();
//	play->wait_for_completion();
	// play->load_subtitle("d:\\media\\dfsschs2.srt");
	// 一直等待直到播放完成.
// 	Sleep(5000);
// 	play->stop();
// 	play->close();

// 	// 播放完成后, 处理各种事件.
//
// 	printf("+++++++++++++++ play completed! ++++++++++++++\n");
// 	return ;
//
// 	for (;;)
// 	{
// 		double d = play->duration();
// 		double cur_time = play->curr_play_time();
// 		printf("-----------time: %0.2f, duration: %0.2f---------\n", cur_time, d - cur_time);
// 		Sleep(200);
// 	}
}

int main(int argc, char* argv[])
{
	// 判断播放参数是否足够.
	if (argc != 2)
	{
		printf("usage: avplayer <video>\n");
		return -1;
	}

	player ply;

	XInitThreads();

	SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTTHREAD);


	// 判断打开的媒体类型, 根据媒体文件类型选择不同的方式打开.
	std::string filename(argv[1]);
	if (fs::path(filename).extension() == ".torrent")
	{
		if(ply.open(filename.c_str(), MEDIA_TYPE_BT)<0)
			return -1;
	}
	else
	{
		std::string is_url = filename.substr(0, 7);
		if (is_url == "http://")
		{
			if (ply.open(filename.c_str(), MEDIA_TYPE_HTTP)<0)
				return -1;
		}
		else if (is_url == "rtsp://")
		{
			//if (!ply.open(filename.c_str(), MEDIA_TYPE_RTSP))
				return -1;
		}
		else
		{
			if (ply.open(filename.c_str(), MEDIA_TYPE_FILE)<0)
			return -1;
		}
	}

	//开始播放
	ply.play();

	SDL_WM_SetCaption((std::string("正在播放") + filename).c_str(),"");

	while(true){
		SDL_Event event;
		SDL_WaitEvent(&event);

		if(event.type == SDL_QUIT){
			//ply.stop();
			break;
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_RIGHT){
				ply.fwd();
			}
		}
	}
	
	//ply.wait_for_completion();

	return 0;
}


