#ifndef INC_2022_PROJECT_ORFEOTERKUCI_STATEMANAGER_H
#define INC_2022_PROJECT_ORFEOTERKUCI_STATEMANAGER_H
#include <memory>
namespace GSTD {
class State;

class StateManager {
private:
    std::unique_ptr<State> currentState;
    unsigned int stateType = 0;
    StateManager();
    StateManager(StateManager const& ref); // Not implemented
    StateManager& operator=(StateManager const& ref); // Not implemented
public:

    //== Getter for instance ==//
    /**
     * Getter function for the StateManager instance
     * @return The static StateManager class type object. If it doesn't exist, it is created
     */
    static StateManager& getInstance(){
        // https://stackoverflow.com/a/271104/6453334
        // The only instance
        // Guaranteed to be lazy initialized
        // Guaranteed that it will be destroyed correctly
        static StateManager instance;
        return instance;
    }

    /**
     * Getter for the current state
     * @return The current state of the manager
     */
    const std::unique_ptr<State>& getCurrentState() const { return currentState; }

    /**
     * Getter for the state type
     * @return The state type
     */
    unsigned int getStateType() const { return stateType; }

    /**
     * Setter for the state type
     * @param newType The new state type
     */
    void setStateType(unsigned int newType) { StateManager::stateType = newType; }

    /**
     * Load the new state
     */
    void load();

    /**
     * Change state to a new type
     */
    void changeState();

    /**
     * Draw the current state on the window
     */
    void draw();

    /**
     * Player won
     */
    void won();

    /**
     * Player lost
     */
    void lost();

    /**
     * Load the next level
     */
    void changeLevel();

    /**
     * Reload the current level
     */
    void reloadLevel();

    virtual ~StateManager();
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_STATEMANAGER_H
