#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include <vector>


int main() {

	GameState* curr_state = new ClientPlayingGameState();

	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "ACT-ION", sf::Style::Fullscreen);

	while (1) {
		curr_state = curr_state->update(window);

	}
}