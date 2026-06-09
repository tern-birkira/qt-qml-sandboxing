
#ifndef _asd_editor_trackLabelField_FlightEnums_h_
#define _asd_editor_trackLabelField_FlightEnums_h_

/*
 * Local header files
 */

/*
 * System header files
 */
#include <QQmlEngine>
#include <QString>

namespace asd::editor::tracklabelfield
{

/*
 * The FlightEnums class provides enumerations for various flight states, including control
 * states and coordination states. It also provides utility functions to convert between
 * enum values and their string representations.
 */
class FlightEnums : public QObject
{
Q_OBJECT
public:
    enum ControlState {
        Unknown,
        NonConcerned,
        Concerned,
        Intruder,
        TransferInInitiated,
        RequestInInitiated,
        Assumed,
        TransferOutInitiated,
        RequestOutInitiated,
        Redundant,
        Completed,
        ControlStateCount
    };
    Q_ENUM( ControlState );

    inline static const std::string strUnknown = "Unknown";
    inline static const std::string strNonConcerned = "NonConcerned";
    inline static const std::string strConcerned = "Concerned";
    inline static const std::string strIntruder = "Intruder";
    inline static const std::string strTransferInInitiated = "TransferInInitiated";
    inline static const std::string strRequestInInitiated = "RequestInInitiated";
    inline static const std::string strAssumed = "Assumed";
    inline static const std::string strTransferOutInitiated = "TransferOutInitiated";
    inline static const std::string strRequestOutInitiated = "RequestOutInitiated";
    inline static const std::string strRedundant = "Redundant";
    inline static const std::string strCompleted = "Completed";

    [[nodiscard]] static QString controlStateToString( ControlState controlState );
    [[nodiscard]] static ControlState stringToControlState( const std::string& controlStateAsString );

    enum CoordinationState {
        CoordinationState_NOT_SET,
        CoordinationState_None, // after MAC received, or MAC acknowledged
        Notifying, // after ABI sent
        Notified, // after at least one ABI received, or ABI acknowledged
        Coordinating, // after ACT sent
        Coordinated, // after ACT received, or ACT acknowledged, or after manual estimate
        Revising,   // when coordinated transfer conditions are revised and not yet acknowledged with a LAM.
        Abrogating // after MAC sent
    };
    Q_ENUM( CoordinationState );

    [[nodiscard]] static QString coordinationStateToString( CoordinationState coordinationState );
    [[nodiscard]] static CoordinationState stringToCoordinationState( const std::string& coordinationStateAsString );
};

} // namespace asd::editor::tracklabelfield

#endif // _asd_editor_trackLabelField_FlightEnums_h_