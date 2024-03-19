#ifndef INC_2022_PROJECT_ORFEOTERKUCI_GOALVIEW_H
#define INC_2022_PROJECT_ORFEOTERKUCI_GOALVIEW_H

#include "EntityView.h"

namespace GSTD {

class GoalView final : public EntityView {

public:

    /**
     * Default constructor for GoalView type object
     */
    GoalView() = default;

    void handle() override;

    ~GoalView() final = default;

};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_GOALVIEW_H
