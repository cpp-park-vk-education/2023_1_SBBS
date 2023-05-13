#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include <vector>


int main() {
<<<<<<< Updated upstream
	GameState* curr_state = new ClientPlayingGameState();
	std::vector<sf::Event> events;
	sf::Mouse mouse;

	while (1) {
		curr_state = curr_state->update(events,mouse);

	}
}
=======
	sf::Music music;
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "ACT-ION");

	music.openFromFile("Sound/baraban.ogg"); 
	music.play();

	while (window.isOpen());
}
>>>>>>> Stashed changes
