# It depends on SDL2 and ffmpeg library, set library root path here
SDL2_ROOT=/opt/homebrew/Cellar/sdl2/2.0.22
FFMPEG_ROOT=/opt/homebrew/Cellar/ffmpeg@4/4.4.2_3

demo: main.cpp video_decoder.cpp video_decoder.h video_sender.cpp video_sender.h sdl_window.cpp sdl_window.h
	g++ main.cpp \
		video_decoder.cpp \
		video_sender.cpp \
		sdl_window.cpp \
		-l stdc++ \
		-I ${SDL2_ROOT}/include \
		-L ${SDL2_ROOT}/lib/ \
		-l SDL2 \
		-I ${FFMPEG_ROOT}/include \
		-L ${FFMPEG_ROOT}/lib \
		-l avcodec \
		-l avdevice \
		-l avformat \
		-l postproc \
		-l swresample \
		-l swscale \
		-l avutil\
		-l avfilter \
		-o demo

clean:
	rm demo
