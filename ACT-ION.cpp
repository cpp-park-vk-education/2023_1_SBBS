#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include <vector>


int main() {

	GameState* curr_state = new ClientPlayingGameState();

	sf::RenderWindow window(sf::VideoMode({ 1600,720  }), "ACT-ION");

	while (1) {
		curr_state = curr_state->update(window);

	}
}