#ifndef INC_2022_PROJECT_ORFEOTERKUCI_PLAYERVIEW_H
#define INC_2022_PROJECT_ORFEOTERKUCI_PLAYERVIEW_H

#include "EntityView.h"

namespace GSTD {

class PlayerView final : public EntityView {
public:

    /**
     * Default constructor for object of PlayerView type
     */
    PlayerView() = default;
    void handle() override;
    ~PlayerView() final = default;

};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_PLAYERVIEW_H
