// modules/commontypes/types.h
#pragma once

#include <QObject>
#include <QtQmlIntegration>
#include <qtmetamacros.h>

namespace apptypes {
    Q_NAMESPACE

    enum class AppState : int {
        Idle = 0,
        Loading,
        Success,
        Error
    };
    Q_ENUM_NS(AppState) // Registers the enum class with the Meta-Object System

    namespace tracklabel {
        Q_NAMESPACE
        enum class LabelType { Uncorrelated, Correlated, Ground, FlightPlanTrack  };
        enum class VisibilityState { Normal, Hover, Completed };
        enum class ControlState {
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
        enum class CoordinationState { // Don't know if needed
            CoordinationState_NOT_SET,
            CoordinationState_None, // after MAC received, or MAC acknowledged
            Notifying, // after ABI sent
            Notified, // after at least one ABI received, or ABI acknowledged
            Coordinating, // after ACT sent
            Coordinated, // after ACT received, or ACT acknowledged, or after manual estimate
            Revising,   // when coordinated transfer conditions are revised and not yet acknowledged with a LAM.
            Abrogating // after MAC sent
        };

        Q_ENUM_NS(LabelType) 
        Q_ENUM_NS(VisibilityState)
        Q_ENUM_NS(ControlState)
        Q_ENUM_NS(CoordinationState)
    }
}


