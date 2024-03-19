#include "World.h"
#include "Stopwatch.h"
#include "Camera.h"
#include <fstream>
#include <utility>
#include "json.hpp"
using json = nlohmann::json;

namespace LSTD {

World::World() = default;

void World::parse(const std::string& filename) {
    try {
        // Parse the json file
        std::ifstream input(filename);
        if (!input) {
            throw FileExist("JSON file was not opened");
        }
        json j;
        input >> j;
        // Read the level specifications
        scroll = j["Settings"]["scroll"];
        name = j["Name"];
        current_player = entity_factory->createPlayer();
        std::string level_file = j["Settings"]["filename"];
        auto entities = j["Entities"];
        char wall = entities["wall"].get<std::string>()[0];
        char player = entities["player"].get<std::string>()[0];
        __attribute__((unused)) char air = entities["air"].get<std::string>()[0];
        char goal = entities["goal"].get<std::string>()[0];
        input.close();
        input = std::ifstream(level_file);
        if (!input) {
            throw FileExist("txt file was not opened");
        }
        if(input.is_open()){
            // Get number of lines
            std::string line;
            int current_line = 0;
            int total_lines = 0;
            // Count number of lines on the file
            while(getline(input , line)){
                total_lines++;
            }
            input.clear();
            input.seekg(0, std::ifstream::beg);
            if(total_lines == 0){
                throw FileEmpty("Level file is empty");
            }
            // Get all entities
            while (getline(input, line)) {
                if(line.back() == '\r'){
                    line.pop_back();
                }
                for (int i = 0; i < line.size(); ++i) {
                    char c = line[i];
                    double posX = - 1 + ( (2 * i) / (double)line.size() );
                    double posY = total_lines - current_line - 1;
                    if(posY > max_height){
                        max_height = (int)posY;
                    }
                    double width = (double) 2 / (double)line.size();
                    if (c == player) {
                        current_player->setWidth(width * 0.95);
                        current_player->setHeight(0.95);
                        current_player->setPositionX(posX);
                        current_player->setPositionY(posY - 1 + current_player->getHeight());
                    } else if (c == wall) {
                        auto newWall = std::move(entity_factory->createWall());
                        newWall->setWidth(width);
                        newWall->setHeight(1.0);
                        newWall->setPositionX(posX);
                        newWall->setPositionY(posY);
                        walls.push_back(std::move(newWall));
                    } else if (c == goal) {
                        current_goal = std::move(entity_factory->createGoal());
                        current_goal->setWidth(width);
                        current_goal->setHeight(1.0);
                        current_goal->setPositionX(posX);
                        current_goal->setPositionY(posY);
                    }
                }
                current_line++;
            }
            input.close();
            // Check if player was created
            if(current_player == nullptr || current_goal == nullptr || walls.empty()){
                throw FileEmpty("Level layout file was empty");
            }
        }
    } catch (FileExist& e) {
        std::cout << e.what();
    }
}

void World::loadFactory(std::unique_ptr<AbstractFactory> factory) { entity_factory = std::move(factory); }

void World::move_left() { current_player->move_left(); }

void World::move_right() { current_player->move_right(); }

void World::jump() { current_player->jump(); }

void World::fall() { current_player->fall(); }

void World::drag() { current_player->drag(); }

void World::calculateCollision() {

    current_player->setFloorBlocked(false);

    for(const auto& e : walls){
        // Wall not visible = skip
        if(!Camera::getInstance().isVisible(e)){
            continue;
        }
        if(!calculateX(current_player , e) && !calculateY(current_player , e)){
            continue ;
        }
        // Collision against floor
        if( current_player->getOldYCoord() - current_player->getHeight() >= e->getPositionY() &&
            current_player->getOldYCoord() > e->getPositionY()
            && calculateFloor(current_player , e)){
            current_player->setPositionY(e->getPositionY() + current_player->getHeight());
            current_player->setFloorBlocked(true);
            current_player->resetVerticalSpeed();
            current_player->resetJumping();
        }
        // Collision against ceiling
        if( current_player->getOldYCoord() <= e->getPositionY() - e->getHeight() &&
            current_player->getOldYCoord() < e->getPositionY()
            && calculateCeiling(current_player, e)){
            current_player->setPositionY(e->getPositionY() - e->getHeight());
            current_player->resetVerticalSpeed();
        }

    }
    for(const auto& e : walls){
        // Wall not visible = skip
        if(!Camera::getInstance().isVisible(e)){
            continue;
        }
        if(!calculateX(current_player , e) && !calculateY(current_player , e)){
            continue ;
        }
        // Collision against a wall to the left
        if( e->getPositionX() + e->getWidth() <= current_player->getOldXCoord()
            && calculateLeft(current_player, e)) {
            current_player->setPositionX(e->getPositionX() + e->getWidth());
            current_player->setLeftBlocked(true);
            current_player->resetHorizontalSpeed();
            current_player->resetVerticalSpeed();
            current_player->resetJumping();
        }
        // Collision against a wall to the right
        if( current_player->getOldXCoord() + current_player->getWidth() < e->getPositionX()
            && calculateRight(current_player, e)){
            current_player->setPositionX(e->getPositionX() - current_player->getWidth() * 1.00001);
            current_player->setRightBlocked(true);
            current_player->resetHorizontalSpeed();
            current_player->resetVerticalSpeed();
            current_player->resetJumping();
        }
    }
}

bool World::calculateCeiling(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e) {
    return e->getPositionY() - e->getHeight() < player->getPositionY() &&
           e->getPositionY() > player->getPositionY() &&
           calculateX(player , e);
}

bool World::calculateFloor(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e) {
    return round((player->getPositionY() - player->getHeight()) / 0.0000000001) * 0.0000000001 <= e->getPositionY() &&
           player->getPositionY() > e->getPositionY() &&
           calculateX(player , e);
}

bool World::calculateLeft(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e) {
    return e->getPositionX() + e->getWidth() > player->getPositionX() &&
           e->getPositionX() + e->getWidth() < player->getPositionX() + player->getWidth() &&
           calculateY(player , e);
}

bool World::calculateRight(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e) {
    return player->getPositionX() + player->getWidth() > e->getPositionX() &&
           player->getPositionX() + player->getWidth() < e->getPositionX() + e->getWidth() &&
           calculateY(player , e);
}

bool World::calculateX(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e) {
    return  (player->getPositionX() == e->getPositionX()
            ||
            (e->getPositionX() < player->getPositionX() + player->getWidth() &&
             e->getPositionX() > player->getPositionX())
            ||
            (e->getPositionX() > player->getPositionX() - player->getWidth() &&
             e->getPositionX() < player->getPositionX()));
}

bool World::calculateY(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e) {
    return  (player->getPositionY() == e->getPositionY())
            ||
            (player->getPositionY() > e->getPositionY() &&
             round((player->getPositionY() - player->getHeight()) / 0.0000000001) * 0.0000000001 < e->getPositionY())
            ||
           (e->getPositionY() > player->getPositionY() &&
            e->getPositionY() - e->getHeight() < player->getPositionY());
}

void World::reset() {
    // Clear all entities
    current_player.reset();
    current_goal.reset();
    walls.clear();
    scroll = false;
    playerMoved = false;
    max_height = -1;
}

bool World::playerWon() {
    // Wall not visible = skip
    if(!Camera::getInstance().isVisible(current_goal)){
        return false;
    }
    if(!calculateX(current_player , current_goal) && !calculateY(current_player , current_goal)){
        return false;
    }
    return calculateFloor(current_player , current_goal) ||
           calculateCeiling(current_player , current_goal) ||
           calculateLeft(current_player , current_goal) ||
           calculateRight(current_player , current_goal);
}

World::~World(){
    reset();
}

} // namespace LSTD