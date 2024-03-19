#ifndef INC_2022_PROJECT_ORFEOTERKUCI_WALLVIEW_H
#define INC_2022_PROJECT_ORFEOTERKUCI_WALLVIEW_H

#include "EntityView.h"

namespace GSTD {

class WallView final : public EntityView {
public:
    /**
     * Default constructor for WallView class object
     */
    WallView() = default;
    void handle() override;
    ~WallView() final = default;
};

} // namespace GSTD

#endif // INC_2022_PROJECT_ORFEOTERKUCI_WALLVIEW_H
