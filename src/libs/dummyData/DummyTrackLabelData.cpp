#include "DummyTrackLabelData.h"

namespace DummyData {

void TrackLabelFactory::populateLabelGrid(TrackLabel* label, const QList<QList<FieldConfigTemplate>>& gridData) {
    if (!label) return;

    // Implementation assumes standard 2D layout methods or loops matching your raw TrackLabel class setters.
    // Example layout population:
    for (int row = 0; row < gridData.size(); ++row) {
        for (int col = 0; col < gridData[row].size(); ++col) {
            const FieldConfigTemplate &f = gridData[row][col];
            
            // Map directly to your raw TrackLabel's internal data population functions, e.g.:
            // label->setFieldConfig(row, col, f.fieldName, f.prefix, f.placeholder, f.toggleable, f.fontAdjustment, f.dummyValue);
        }
    }
}

TrackLabel* TrackLabelFactory::createUncorrelatedLabel(QObject *parent) {
    TrackLabel *label = new TrackLabel(parent);

    // Mapped precisely from <tlabel:tracklabel tracklabel-type="Uncorrelated">
    QList<QList<FieldConfigTemplate>> uncorrelatedGrid = {
        // Line 1
        {
            {"ssrCodeAndCallsign", "", "", false, false, 4, false, "2347/ICE425"},
            {"snsInhibitedSsrDot", "", "", false, false, 0, false, ""}
        },
        // Line 2
        {
            {"currentFlightLevel", "", "AFL", false, false, 0, false, "350"},
            {"verticalRateArrow", "", "", false, false, 0, false, "↑"},
            {"verticalRate", "", "", false, false, 0, false, "↑1500"}
        },
        // Line 3
        {
            {"speed", "", "", true, false, 0, true, "M082"}
        },
        // Line 4
        {
            {"indicatedAirspeed", "I", "", true, false, 0, true, "280"}
        },
        // Line 5
        {
            {"freeText", "", "", false, false, 0, false, "RVSM APPROVED"}
        }
    };

    populateLabelGrid(label, uncorrelatedGrid);
    return label;
}

TrackLabel* TrackLabelFactory::createCorrelatedLabel(QObject *parent) {
    TrackLabel *label = new TrackLabel(parent);

    // Mapped from Correlated layout + positionally blended fields from <tlabel:extended-tracklabel>
    QList<QList<FieldConfigTemplate>> correlatedGrid = {
        // Line 1
        {
            {"callsign", "", "", false, false, 4, false, "ICE425"},
            {"snsInhibitedSsrDot", "", "", false, false, 0, false, ""},
            {"currentControllingSector", "", "CS", false, false, 0, true, "BIRD_N"},
            {"numberOfAircraft", "", "", false, false, 0, false, "1"},
            {"aircraftType", "", "", true, false, 0, true, "B738"},
            {"wakeTurbulenceCategory", "", "", true, false, 0, false, "M"},
            {"approachSequenceNumber", "", "#_", true, false, 0, false, "3"},
            {"destinationRunway", "", "", true, false, 0, false, "27L"}
        },
        // Line 2 (Base fields + positionally appended extended layout item "requestedFlightLevel")
        {
            {"currentFlightLevel", "", "AFL", false, false, 0, false, "350"},
            {"verticalRateArrow", "", "", false, false, 0, false, "↑"},
            {"verticalRate", "", "", false, false, 0, false, "↑1500"},
            {"clearedFlightLevelOrApproach", "", "CFL", false, false, 0, false, "FL350"},
            {"assignedVerticalRate", "", "ARC", false, false, 0, false, "1500"},
            {"selectedAltitude", "", "SFL", true, false, 0, false, "FL350"},
            {"requestedFlightLevel", "", "RFL", false, false, 0, false, "FL390"} // Merged positionally from extended config
        },
        // Line 3
        {
            {"speed", "", "SPD", false, false, 0, false, "M082"},
            {"clearedSpeed", "", "ASP", false, false, 0, false, "M082"},
            {"indicatedAirspeed", "I", "DSPD", true, false, 0, false, "280"},
            {"clearedApproach", "", "APP", true, false, 0, false, "ILS27L"}
        },
        // Line 4
        {
            {"currentRouteElement", "", "ROUTE", false, false, 0, false, "RATSU"},
            {"nextRouteElement", ">", "", true, false, 0, true, "MIMKU"},
            {"magneticHeading", "", "DHDG", true, false, 0, true, "093"},
            {"barometricPressureSettings", "", "", true, false, 0, false, "1013"}
        },
        // Line 5
        {
            {"destinationAerodrome", "", "", true, false, 0, false, "EGLL"},
            {"freeText", "", "", false, false, 0, false, "RVSM APPROVED"}
        },
        // Extended Configuration Line 6
        {
            {"numberOfAircraft", "", "", false, false, 0, false, "1"},
            {"ssrCode", "", "TSSR", false, false, 0, false, "2347"},
            {"previousSSRCode", "", "PSSR", false, false, 0, false, "2346"},
            {"assignedSSRCode", "", "ASSR", false, false, 0, false, "2347"}
        },
        // Extended Configuration Line 7
        {
            {"departureAerodrome", "", "ADEP", false, false, 0, false, "BIKF"},
            {"actualDepartureTime", "", "ADT", false, false, 0, false, "1429"},
            {"alternativeDestinationAeroDrome", "", "ALTN", false, false, 0, false, "EGKK"},
            {"alternativeDestinationAeroDrome2", "", "ALTN2", false, false, 0, false, "EHAM"}
        },
        // Extended Configuration Line 8
        {
            {"route", "", "", false, false, 0, false, "DCT RATSU DCT"}
        },
        // Extended Configuration Line 9 (Field 18 compound mappings)
        {
            {"field18", "", "STS/", false, false, 0, false, "STS/HOSP"},
            {"field18", "", "RMK/", false, false, 0, false, "RMK/TCAS AVBL"}
        }
    };

    populateLabelGrid(label, correlatedGrid);
    return label;
}

TrackLabel* TrackLabelFactory::createFlightPlanLabel(QObject *parent) {
    TrackLabel *label = new TrackLabel(parent);

    // Mapped from FlightPlanTrack layout + positionally blended fields from <tlabel:extended-tracklabel>
    QList<QList<FieldConfigTemplate>> flightPlanGrid = {
        // Line 1
        {
            {"callsign", "", "", false, false, 4, false, "ICE425"},
            {"currentControllingSector", "", "CS", false, false, 0, true, "BIRD_N"},
            {"numberOfAircraft", "", "", false, false, 0, false, "1"},
            {"aircraftType", "", "", true, false, 0, true, "B738"},
            {"wakeTurbulenceCategory", "", "", true, false, 0, false, "M"},
            {"approachSequenceNumber", "", "#_", true, false, 0, false, "3"},
            {"destinationRunway", "", "", true, false, 0, false, "27L"}
        },
        // Line 2 (Base fields incorporating "reportedLevel" instead of "currentFlightLevel" + Extended item "requestedFlightLevel")
        {
            {"reportedLevel", "", "AFL", false, false, 0, false, "FL350"},
            {"verticalRateArrow", "", "", false, false, 0, false, "↑"},
            {"verticalRate", "", "", false, false, 0, false, "↑1500"},
            {"clearedFlightLevelOrApproach", "", "CFL", false, false, 0, false, "FL350"},
            {"assignedVerticalRate", "", "ARC", false, false, 0, false, "1500"},
            {"selectedAltitude", "", "SFL", true, false, 0, false, "FL350"},
            {"requestedFlightLevel", "", "RFL", false, false, 0, false, "FL390"} // Merged positionally from extended config
        },
        // Line 3
        {
            {"speed", "", "SPD", false, false, 0, false, "M082"},
            {"clearedSpeed", "", "ASP", false, false, 0, false, "M082"},
            {"indicatedAirspeed", "I", "DSPD", true, false, 0, false, "280"},
            {"clearedApproach", "", "APP", true, false, 0, false, "ILS27L"}
        },
        // Line 4
        {
            {"currentRouteElement", "", "ROUTE", false, false, 0, false, "RATSU"},
            {"nextRouteElement", ">", "", true, false, 0, true, "MIMKU"},
            {"magneticHeading", "", "DHDG", true, false, 0, true, "093"},
            {"barometricPressureSettings", "", "", true, false, 0, false, "1013"}
        },
        // Line 5
        {
            {"destinationAerodrome", "", "", true, false, 0, false, "EGLL"},
            {"freeText", "", "", false, false, 0, false, "RVSM APPROVED"}
        },
        // Extended Lines 6 through 9 follow structurally symmetric boundaries matching Correlated configuration
        {
            {"numberOfAircraft", "", "", false, false, 0, false, "1"},
            {"ssrCode", "", "TSSR", false, false, 0, false, "2347"},
            {"previousSSRCode", "", "PSSR", false, false, 0, false, "2346"},
            {"assignedSSRCode", "", "ASSR", false, false, 0, false, "2347"}
        },
        {
            {"departureAerodrome", "", "ADEP", false, false, 0, false, "BIKF"},
            {"actualDepartureTime", "", "ADT", false, false, 0, false, "1429"},
            {"alternativeDestinationAeroDrome", "", "ALTN", false, false, 0, false, "EGKK"},
            {"alternativeDestinationAeroDrome2", "", "ALTN2", false, false, 0, false, "EHAM"}
        },
        {
            {"route", "", "", false, false, 0, false, "DCT RATSU DCT"}
        },
        {
            {"field18", "", "STS/", false, false, 0, false, "STS/HOSP"},
            {"field18", "", "RMK/", false, false, 0, false, "RMK/TCAS AVBL"}
        }
    };

    populateLabelGrid(label, flightPlanGrid);
    return label;
}

} // namespace DummyData