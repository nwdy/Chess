# Note: You must replace <sfml-install-path> as the directory where you copied/downloaded SFML
# For example: <sfml-install-path> = /home/user_name/sfml

all: resource_manager.h game_state.h render_engine.h controller.h
	g++ main.cpp \
		resource_manager.cpp \
		game_state.cpp \
		render_engine.cpp \
		controller.cpp \
		minimax.cpp \
		-o chess \
		-std=c++17 \
		-I <sfml-install-path>/include \ 
		-lsfml-graphics -lsfml-window -lsfml-system \
		-L <sfml-install-path>/lib \
