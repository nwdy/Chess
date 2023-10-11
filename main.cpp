#include "resource_manager.h"
#include "game_state.h"
#include "render_engine.h"
#include "controller.h"

int main()
{
    ResourceManager manager;
    GameState state;
    GameWindow window(manager, state);
    Controller controller(state, window);
    controller.launch();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            controller.processEvent(event);
        }
        if (!state.isThinking())
            window.render();
    }

    controller.wait();
    return 0;
}