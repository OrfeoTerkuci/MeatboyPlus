#ifndef INC_2022_PROJECT_ORFEOTERKUCI_WORLD_H
#define INC_2022_PROJECT_ORFEOTERKUCI_WORLD_H

#include "AbstractFactory.h"
#include "StandardValues.h"
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <exception>

namespace LSTD {

class FileExist : public std::exception {
private:
    std::string error {};
public:
    /**
     * Constructor for FileExists type exception
     * @param error The error message
     */
    explicit FileExist(std::string  error) : error(std::move(error)) {}

    /**
     * Copy constructor for FileExists type exception
     * @param ref Reference to another FileExists object
     */
    FileExist(const FileExist& ref) noexcept : error(ref.error) {}

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return error.c_str();
    }

    ~FileExist() override = default;
};

class FileEmpty : public std::exception {
private:
    std::string error {};
public:
    /**
     * Constructor for FileEmpty type exception
     * @param error The error message
     */
    explicit FileEmpty(std::string  error) : error(std::move(error)) {}

    /**
     * Copy constructor for FileEmpty type exception
     * @param ref Reference to another FileEmpty object
     */
    FileEmpty(const FileEmpty& ref) noexcept : error(ref.error) {}

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return error.c_str();
    }

    ~FileEmpty() override = default;
};

class World {

private:

    //== Entities ==//
    std::shared_ptr<EntityModel> current_player;
    std::vector<std::shared_ptr<EntityModel>> walls;
    std::shared_ptr<EntityModel> current_goal;
    //== Entity factory ==//
    std::unique_ptr<AbstractFactory> entity_factory;
    //== Level specifics ==//
    bool scroll {false};
    int max_height {-1};
    std::string name;
    bool playerMoved {false};
    //== Private constructors ==//
    World();
    World(World const& ref); // Not implemented
    World& operator=(World const& ref); // Not implemented

    //== Collision detectors ==//
    /**
     * Player collides with entity e from below (ceiling collision)
     * @param player    The player
     * @param e         The entity
     * @return          True if they collide , False otherwise
     */
    static bool calculateCeiling(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e);

    /**
     * Player collides with entity e from above (floor collision)
     * @param player    The player
     * @param e         The entity
     * @return          True if they collide, False otherwise
     */
    static bool calculateFloor(const std::shared_ptr<EntityModel>& player , const std::shared_ptr<EntityModel>& e);

    /**
     * Player collides with entity from the right (left wall collision)
     * @param player    The player
     * @param e         The entity
     * @return          True if they collide , False otherwise
     */
    static bool calculateLeft(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e);

    /**
     * Player collides with entity from the left (right wall collision)
     * @param player    The player
     * @param e         The entity
     * @return          True if they collide , False otherwise
     */
    static bool calculateRight(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e);

    /**
     * Player collides with the entity from left or right
     * @param player    The player
     * @param e         The entity
     * @return          True if they collide, false if not
     */
    static bool calculateX(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e);

    /**
     * Player collides with the entity from above or below
     * @param player    The player
     * @param e         The entity
     * @return          True if they collide, false if not
     */
    static bool calculateY(const std::shared_ptr<EntityModel>& player, const std::shared_ptr<EntityModel>& e);

public:

    /**
     * Getter function for the world instance
     * @return The static World class type object. If it doesn't exist, it is created
     */
    static World& getInstance(){
        static World instance;
        return instance;
    }

    //== Level loading functions ==//
    /**
     * Setter for entityFactory member
     * @param factory The new Entity (Abstract) factory
     */
    void loadFactory(std::unique_ptr<AbstractFactory> factory);

    /**
     * Parses a level
     * @param filename The path to the level to be parsed
     */
    void parse(const std::string& filename);

    //== Getters ==//
    /**
     * Getter for entityFactory member
     * @return The entityFactory
     */
    const std::unique_ptr<AbstractFactory>& getEntityFactory() const { return entity_factory; }

    /**
     * Getter for the player member
     * @return The currentPlayer
     */
    const std::shared_ptr<EntityModel>& getCurrentPlayer() const { return current_player; }

    /**
     * Getter for the walls vector
     * @return The walls vector
     */
    const std::vector<std::shared_ptr<EntityModel>>& getWalls() const { return walls; }

    /**
     * Getter for the goal member
     * @return The currentGoal
     */
    const std::shared_ptr<EntityModel>& getCurrentGoal() const { return current_goal; }

    /**
     * Getter for the scroll boolean
     * @return True if world has autoScroll
     */
    bool isScroll() const { return scroll; }

    /**
     * Getter for the maximum height
     * @return The height of the highest wall
     */
    int getMaxHeight() const { return max_height; }

    /**
     * Getter for the world name
     * @return The name of the world
     */
    const std::string& getName() const { return name; }

    /**
     * Getter for player movement boolean
     * @return True if player has moved
     */
    bool moved() const { return playerMoved; }

    //== Setters ==//

    /**
     * Setter for the player member
     * @param currentPlayer The new player member
     */
    void setCurrentPlayer(const std::shared_ptr<EntityModel>& currentPlayer) { current_player = currentPlayer; };

    /**
     * Setter for the walls vector
     * @param newWalls The new walls vector
     */
    void setWalls(const std::vector<std::shared_ptr<EntityModel>>& newWalls) { World::walls = newWalls; };

    /**
     * Setter for the goal member
     * @param currentGoal The new goal
     */
    void setCurrentGoal(const std::shared_ptr<EntityModel>& currentGoal) { current_goal = currentGoal; };

    /**
     * Setter for the autoScroll boolean
     * @param newScroll The new autoScroll status
     */
    void setScroll(bool newScroll) { World::scroll = newScroll; };

    /**
     * Setter for the maximum height of the world
     * @param maxHeight The new maximal world height
     */
    void setMaxHeight(int maxHeight) { max_height = maxHeight; };

    /**
     * Setter for the world name
     * @param newName The new name
     */
    void setName(const std::string& newName) { World::name = newName; };

    // Player movement simulation

    /**
     * Simulates a player move to the left
     */
    void move_left();

    /**
     * Simulates a player move to the right
     */
    void move_right();

    /**
     * Simulates a player jump
     */
    void jump();

    /**
     * Simulates player falling
     */
    void fall();

    /**
     * Simulates player slowing down
     */
    void drag();

    // Collision simulation

    /**
     * Calculates player's collision with the walls
     */
    void calculateCollision();

    // Won?
    /**
     * Checks whether the player reached the goal
     * @return True if player reached the goal
     */
    bool playerWon();

    // Reset functions

    /**
     * Resets the world
     */
    void reset();

    virtual ~World();
};

} // namespace LSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_WORLD_H
