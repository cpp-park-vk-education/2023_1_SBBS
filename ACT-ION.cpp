#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include <vector>


int main() {
	GameState* curr_state = new ClientPlayingGameState();
	std::vector<sf::Event> events;
	sf::Mouse mouse;

	while (1) {
		curr_state = curr_state->update(events,mouse);

	}
}
