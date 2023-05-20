#pragma once
#include "GraphicsSystem.h"
#include "GraphicsComponent.h"
#include "PositionComponent.h"
#include <SFML/Window.hpp>

#include <iostream>

int GraphicsSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {
    
    window.clear();
    // Создаем массив для верхнего слоя отрисовки
    std::vector<int> upper_layer;

    //Отрисовываем нижний слой (карту) и откладываем элементы верхнего слоя
    for (int i = 0; i < scene.size(); ++i) {

        sf::Sprite curr_sprite;

        GraphicsComponent* current_graph = dynamic_cast<GraphicsComponent*>(scene[i]->getComponentByID(ComponentID::GraphicsComponent));
        // проверить, что граф компонента вообще существует 
        if (!current_graph) continue;

        if (!current_graph->layer) {
            PositionComponent* current_pos = dynamic_cast<PositionComponent*>(scene[i]->getComponentByID(ComponentID::PositionComponent));
            curr_sprite = current_graph->getSprite();
            curr_sprite.setPosition(current_pos->getPosition().x, current_pos->getPosition().y);
        }
        else {
            upper_layer.push_back(i);
        }
        window.draw(curr_sprite);
    }

    // Отрисовываем верхний слой
    for (int i = 0; i < upper_layer.size(); ++i) {

        sf::Sprite curr_sprite;

        GraphicsComponent* current_graph = dynamic_cast<GraphicsComponent*>(scene[upper_layer[i]]->getComponentByID(ComponentID::GraphicsComponent));
        PositionComponent* current_pos = dynamic_cast<PositionComponent*>(scene[upper_layer[i]]->getComponentByID(ComponentID::PositionComponent));
        curr_sprite = current_graph->getSprite();

        curr_sprite.setPosition(current_pos->getPosition().x, current_pos->getPosition().y);
        curr_sprite.setRotation(current_pos->getRotation());

        curr_sprite.setPosition(current_pos->getPosition().x, current_pos->getPosition().y);
        window.draw(curr_sprite);
    }

    window.display();
    return 0;
}