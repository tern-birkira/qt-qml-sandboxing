#pragma once
#include <QObject>
// #include "../../modules/tracklabel/models/FieldInterface.h"
// #include "../../modules/tracklabel/models/RowCellModel.h"
// #include "namespace_decl.h"
#include "../../modules/tracklabel/models/RowListModel.h"
// using namespace asd::editor::tracklabel;
// using namespace asd::editor::tracklabelfield;

namespace DummyData {

/**
 * @brief Factory producing pre-configured RowListModel instances for each track label type.
 *        Field data is sourced directly from tracklabel-config.xml.
 */
class TrackLabelFactory {
public:
    static asd::editor::tracklabel::RowListModel* createUncorrelatedLabel(QObject* parent = nullptr);
    static asd::editor::tracklabel::RowListModel* createCorrelatedLabel(QObject* parent = nullptr);
    static asd::editor::tracklabel::RowListModel* createFlightPlanLabel(QObject* parent = nullptr);
};

} // namespace DummyData
