#include <iostream>
#include <string>
#include "video_decoder.h"
#include "video_sender.h"
#include "sdl_window.h"

using namespace std;

static void printHelp() {
    cout << "usage :" << endl;
    cout << "        -s url    Send Video" << endl;
    cout << "        -p url    Play Video" << endl;
}

static void playVideo(const string& url) {
    VideoDecoder decoder;
    if(!decoder.Load(url)) {
        return;
    }
    
    decoder.DumpVideoInfo();

    AVPixelFormat format = decoder.GetPixelFormat();

    if(format != AV_PIX_FMT_YUV420P) {
        cout << "only support YUV420P, the video format id is" << format << endl;
        return ;
    }

    SdlWindow::GetInstance()->Show("FFMPEG PLAYER", decoder.GetVideoWidth(), decoder.GetVideoHeight());

    AVFrame* frame;
    while((frame = decoder.NextFrame()) != NULL) {
        if(!SdlWindow::GetInstance()->Update(frame->data, frame->linesize)) {
            break;
        }
    }

    decoder.Release();
}

static void sendVideo(const string& srcUrl, const string& destUrl) {
    VideoSender::Send(srcUrl, destUrl);
}

static bool invkoeWithParam(int argc, char* argv[]) {
    if(argc < 2) {
        return false;
    }

    if(strcmp("-p", argv[1]) == 0) {
        if(argc < 3) {
            return false;
        }
        playVideo(argv[2]);
        return true;
    }

    if(strcmp("-s", argv[1]) == 0) {
        if(argc < 4) {
            return false;
        }
        sendVideo(argv[2], argv[3]);
        return true;
    }
    
    return false;
}

int main(int argc, char* argv[]) {
    if(!invkoeWithParam(argc, argv)) {
        printHelp();
        return -1;
    }

    return 0;
}