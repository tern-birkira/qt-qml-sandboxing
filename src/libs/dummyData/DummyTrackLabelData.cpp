#include "DummyTrackLabelData.h"

using namespace asd::editor::tracklabel;
using namespace asd::editor::tracklabelfield;

namespace DummyData {

// Internal field configuration — maps directly to XML attributes
struct FieldConfig {
    QString fieldName;
    QString prefix           = {};
    QString placeholder      = {};
    bool    toggleable       = false;
    bool    onlyShowOnFocus  = false;
    bool    visibleInHolding = false;
    int     fontAdjustment   = 0;
    int     fixedWidthInChars = -1;
    int     leftMargin       = 0;
};

static FieldInterface* makeField(const FieldConfig& cfg, QObject* parent)
{
    auto* field = new FieldInterface(parent);
    field->fieldText()->setFieldName(cfg.fieldName);
    if (!cfg.prefix.isEmpty())       field->fieldText()->setPrefix(cfg.prefix);
    if (!cfg.placeholder.isEmpty())  field->fieldText()->setPlaceholder(cfg.placeholder);
    if (cfg.toggleable)              field->fieldAppearance()->setToggleable(true);
    if (cfg.onlyShowOnFocus)         field->fieldAppearance()->setOnlyShowOnFocus(true);
    if (cfg.visibleInHolding)        field->fieldAppearance()->setVisibleInHolding(true);
    if (cfg.fontAdjustment != 0)     field->fieldLayout()->setFontAdjustment(cfg.fontAdjustment);
    if (cfg.fixedWidthInChars >= 0)  field->fieldLayout()->setFixedWidthInCharacters(cfg.fixedWidthInChars);
    if (cfg.leftMargin != 0)         field->fieldLayout()->setLeftMargin(cfg.leftMargin);
    return field;
}

static RowCellModel* makeRow(const QList<FieldConfig>& cfgs)
{
    QVector<FieldInterface*> cells;
    cells.reserve(cfgs.size());
    for (const auto& cfg : cfgs)
        cells.append(makeField(cfg, nullptr));
    auto* row = new RowCellModel(cells, nullptr);
    for (auto* f : cells)
        f->setParent(row);
    return row;
}

static RowListModel* buildModel(const QList<QList<FieldConfig>>& grid, QObject* parent)
{
    QVector<RowCellModel*> rows;
    rows.reserve(grid.size());
    for (const auto& rowCfg : grid)
        rows.append(makeRow(rowCfg));
    auto* model = new RowListModel(rows, parent);
    for (auto* r : rows)
        r->setParent(model);
    return model;
}

// Extended lines 6-9 are shared between Correlated and FlightPlanTrack
static QList<QList<FieldConfig>> extendedLines()
{
    return {
        // Extended Line 6
        {
            { "numberOfAircraft" },
            { "ssrCode",         "", "TSSR" },
            { "previousSSRCode", "", "PSSR" },
            { "assignedSSRCode", "", "ASSR" }
        },
        // Extended Line 7
        {
            { "departureAerodrome",               "", "ADEP"  },
            { "actualDepartureTime",              "", "ADT"   },
            { "alternativeDestinationAeroDrome",  "", "ALTN"  },
            { "alternativeDestinationAeroDrome2", "", "ALTN2" }
        },
        // Extended Line 8
        {
            { "route" }
        },
        // Extended Line 9 — field18 items (STS / RMK)
        {
            { "field18", "", "STS/" },
            { "field18", "", "RMK/" }
        }
    };
}

RowListModel* TrackLabelFactory::createUncorrelatedLabel(QObject* parent)
{
    return buildModel({
        // Line 1
        {
            { "ssrCodeAndCallsign", "", "", false, false, false, 4 },
            { "snsInhibitedSsrDot" }
        },
        // Line 2
        {
            { "currentFlightLevel", "", "AFL" },
            { "verticalRateArrow",  "", "", false, false, false, 0, 1, -4 },
            { "verticalRate",       "", "", false, false, false, 0, -1, -5 }
        },
        // Line 3
        {
            { "speed", "", "", true, true }
        },
        // Line 4
        {
            { "indicatedAirspeed", "I", "", true, true }
        },
        // Line 5
        {
            { "freeText" }
        }
    }, parent);
}

RowListModel* TrackLabelFactory::createCorrelatedLabel(QObject* parent)
{
    QList<QList<FieldConfig>> grid = {
        // Line 1
        {
            { "callsign",                  "", "",   false, false, true,  4       },
            { "snsInhibitedSsrDot" },
            { "currentControllingSector",  "", "CS", false, true                 },
            { "flightRule" },
            { "numberOfAircraft" },
            { "aircraftType",              "", "",   true,  true                 },
            { "wakeTurbulenceCategory",    "", "",   true,  false, false, 0, -1, -4 },
            { "approachSequenceNumber",    "", "#_", true                        },
            { "destinationRunway",         "", "",   true,  false, false, 0, -1, -8 }
        },
        // Line 2 — base fields + extended "requestedFlightLevel" merged at line position
        {
            { "currentFlightLevel",          "", "AFL", false, false, true  },
            { "verticalRateArrow",           "", "",   false, false, false, 0, 1,  -8 },
            { "verticalRate",                "", "",   false, false, false, 0, -1, -4 },
            { "clearedFlightLevelOrApproach","", "CFL" },
            { "assignedVerticalRate",        "", "ARC" },
            { "selectedAltitude",            "", "SFL", true },
            { "requestedFlightLevel",        "", "RFL" }
        },
        // Line 3
        {
            { "speed",              "", "SPD"  },
            { "clearedSpeed",       "", "ASP"  },
            { "indicatedAirspeed",  "I","DSPD", true },
            { "clearedApproach",    "", "APP",  true }
        },
        // Line 4
        {
            { "currentRouteElement",       "", "ROUTE" },
            { "nextRouteElement",          ">","",      true, true },
            { "magneticHeading",           "", "DHDG",  true, true },
            { "barometricPressureSettings","", "",      true }
        },
        // Line 5
        {
            { "destinationAerodrome", "", "", true },
            { "freeText" }
        }
    };

    const auto ext = extendedLines();
    grid.append(ext);
    return buildModel(grid, parent);
}

RowListModel* TrackLabelFactory::createFlightPlanLabel(QObject* parent)
{
    QList<QList<FieldConfig>> grid = {
        // Line 1 — no snsInhibitedSsrDot compared to Correlated
        {
            { "callsign",                 "", "",   false, false, true,  4       },
            { "currentControllingSector", "", "CS", false, true                 },
            { "flightRule" },
            { "numberOfAircraft" },
            { "aircraftType",             "", "",   true,  true                 },
            { "wakeTurbulenceCategory",   "", "",   true,  false, false, 0, -1, -4 },
            { "approachSequenceNumber",   "", "#_", true                        },
            { "destinationRunway",        "", "",   true,  false, false, 0, -1, -8 }
        },
        // Line 2 — reportedLevel instead of currentFlightLevel + extended "requestedFlightLevel"
        {
            { "reportedLevel",               "", "AFL", false, false, true  },
            { "verticalRateArrow",           "", "",   false, false, false, 0, 1,  -8 },
            { "verticalRate",                "", "",   false, false, false, 0, -1, -4 },
            { "clearedFlightLevelOrApproach","", "CFL" },
            { "assignedVerticalRate",        "", "ARC" },
            { "selectedAltitude",            "", "SFL", true },
            { "requestedFlightLevel",        "", "RFL" }
        },
        // Line 3
        {
            { "speed",             "", "SPD"  },
            { "clearedSpeed",      "", "ASP"  },
            { "indicatedAirspeed", "I","DSPD", true },
            { "clearedApproach",   "", "APP",  true }
        },
        // Line 4
        {
            { "currentRouteElement",       "", "ROUTE" },
            { "nextRouteElement",          ">","",      true, true },
            { "magneticHeading",           "", "DHDG",  true, true },
            { "barometricPressureSettings","", "",      true }
        },
        // Line 5
        {
            { "destinationAerodrome", "", "", true },
            { "freeText" }
        }
    };

    const auto ext = extendedLines();
    grid.append(ext);
    return buildModel(grid, parent);
}

} // namespace DummyData