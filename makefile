all: resource_manager.h game_state.h render_engine.h controller.h
	clang++ main.cpp \
		resource_manager.cpp \
		game_state.cpp \
		render_engine.cpp \
		controller.cpp \
		minimax.cpp \
		-o chess \
		-std=c++17 \
		-I sfml/2.6.0/include \
		-lsfml-graphics -lsfml-window -lsfml-system \
		-L sfml/2.6.0/lib \
		-mmacosx-version-min=13.0
