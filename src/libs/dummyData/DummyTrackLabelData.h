#pragma once
#include <QObject>
#include <QString>
#include <QList>
#include <QVariant>
#include "tracklabel.h" // The raw base class from your branch layout

namespace DummyData {

/**
 * @brief Plain struct to hold parameters mapped exactly from the XML attributes
 */
struct FieldConfigTemplate {
    QString fieldName;
    QString prefix;
    QString placeholder;
    bool toggleable;
    bool blinking;
    int fontAdjustment;
    bool onlyShowOnFocus;
    QVariant dummyValue;
};

/**
 * @brief Factory class to initialize and deliver pre-configured raw TrackLabel instances
 */
class TrackLabelFactory {
public:
    /**
     * @brief Generates a raw TrackLabel populated with the Uncorrelated configuration matrix
     */
    static TrackLabel* createUncorrelatedLabel(QObject *parent = nullptr);

    /**
     * @brief Generates a raw TrackLabel populated with the positionally merged Correlated + Extended matrix
     */
    static TrackLabel* createCorrelatedLabel(QObject *parent = nullptr);

    /**
     * @brief Generates a raw TrackLabel populated with the positionally merged FlightPlanTrack + Extended matrix
     */
    static TrackLabel* createFlightPlanLabel(QObject *parent = nullptr);

private:
    // Helper to abstract grid insertion logic depending on your TrackLabel setter implementation
    static void populateLabelGrid(TrackLabel* label, const QList<QList<FieldConfigTemplate>>& gridData);
};

} // namespace DummyData
