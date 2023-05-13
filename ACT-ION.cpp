#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>



int main() {
	sf::Music music;
	sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Timur ebat the best");

	if(!music.openFromFile("Sound/baraban.ogg")) return -1;
	music.play();

	while (1);
}