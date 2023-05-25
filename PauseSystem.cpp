#pragma once
#include "PauseSystem.h"
#include <chrono>
#include "SpawnerSystem.h"
#include "SpawnID.h"
#include "GameSingleton.h"
#include "InputHandler.h"

double esc_button_cooldown = 0.2;

int PauseSystem::update(sf::RenderWindow& window, std::vector<Entity*>& scene) {

    Input inputs;
    inputs.handleInput(window);

    static bool was_paused = false;
    static std::chrono::steady_clock::time_point last_time_pause = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point curr_time = std::chrono::high_resolution_clock::now();
    double elapsed_time_pause = std::chrono::duration<double>(curr_time - last_time_pause).count();


    if (inputs.esc_pressed_ && elapsed_time_pause > esc_button_cooldown) {

        if (Game::getInstance().getGamePaused()) { /// стоит на паузе
            Game::getInstance().setGamePause(false);
        }
        else {
            ButtonSpawner button_spawner;
            BannerSpawner banner_spawner;
            //1900 1000 
            Entity* temp_ent = nullptr;
            temp_ent = banner_spawner.Spawn(Position(650, 300), pause_banner);
            temp_ent->setType(ObjectType::PauseMenu);
            scene.push_back(temp_ent);

            temp_ent = button_spawner.Spawn(Position(800, 400), back_to_main_menu_button_id);
            temp_ent->setType(ObjectType::PauseMenu);
            scene.push_back(temp_ent);

            temp_ent = button_spawner.Spawn(Position(800, 550), resume_game_button_id);
            temp_ent->setType(ObjectType::PauseMenu);
            scene.push_back(temp_ent);

            Game::getInstance().setGamePause(true);
            was_paused = true;
        }
        last_time_pause = std::chrono::high_resolution_clock::now();

    }

    if (was_paused && !Game::getInstance().getGamePaused()) {
        for (int i = 0; i < scene.size(); ++i) {
            ////////////удаление меню паузы
            if (scene[i]->getType() == ObjectType::PauseMenu) {
                scene.erase(scene.begin() + i);
                --i;
            }
        }
        was_paused = false;
    }

    return 0;
};
