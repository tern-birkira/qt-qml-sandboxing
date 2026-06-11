#include "FlightEnums.h"

namespace asd::editor::tracklabelfield
{

QString FlightEnums::controlStateToString( ControlState controlState )
{
    switch( controlState )
    {
        case ControlState::Unknown:
            return QString::fromStdString( strUnknown );
        case ControlState::NonConcerned:
            return QString::fromStdString( strNonConcerned );
        case ControlState::Concerned:
            return QString::fromStdString( strConcerned );
        case ControlState::Intruder:
            return QString::fromStdString( strIntruder );
        case ControlState::TransferInInitiated:
            return QString::fromStdString( strTransferInInitiated );
        case ControlState::RequestInInitiated:
            return QString::fromStdString( strRequestInInitiated );
        case ControlState::Assumed:
            return QString::fromStdString( strAssumed );
        case ControlState::TransferOutInitiated:
            return QString::fromStdString( strTransferOutInitiated );
        case ControlState::RequestOutInitiated:
            return QString::fromStdString( strRequestOutInitiated );
        case ControlState::Redundant:
            return QString::fromStdString( strRedundant );
        case ControlState::Completed:
            return QString::fromStdString( strCompleted );
        default:
            throw std::invalid_argument( "Invalid control state enum value" );
    }
}

FlightEnums::ControlState FlightEnums::stringToControlState( const std::string& controlStateAsString )
{
    if( controlStateAsString == strUnknown )
    {
        return ControlState::Unknown;
    }
    else if( controlStateAsString == strNonConcerned )
    {
        return ControlState::NonConcerned;
    }
    else if( controlStateAsString == strConcerned )
    {
        return ControlState::Concerned;
    }
    else if( controlStateAsString == strIntruder )
    {
        return ControlState::Intruder;
    }
    else if( controlStateAsString == strTransferInInitiated )
    {
        return ControlState::TransferInInitiated;
    }
    else if( controlStateAsString == strRequestInInitiated )
    {
        return ControlState::RequestInInitiated;
    }
    else if( controlStateAsString == strAssumed )
    {
        return ControlState::Assumed;
    }
    else if( controlStateAsString == strTransferOutInitiated )
    {
        return ControlState::TransferOutInitiated;
    }
    else if( controlStateAsString == strRequestOutInitiated )
    {
        return ControlState::RequestOutInitiated;
    }
    else if( controlStateAsString == strRedundant )
    {
        return ControlState::Redundant;
    }
    else if( controlStateAsString == strCompleted )
    {
        return ControlState::Completed;
    }
    else
    {
        throw std::invalid_argument( "Invalid control state string value: " + controlStateAsString );
    }
}

QString FlightEnums::coordinationStateToString( CoordinationState coordinationState )
{
    switch( coordinationState )
    {
        case CoordinationState::CoordinationState_NOT_SET:
            return "NOT_SET";
        case CoordinationState::CoordinationState_None:
            return "None";
        case CoordinationState::Notifying:
            return "Notifying";
        case CoordinationState::Notified:
            return "Notified";
        case CoordinationState::Coordinating:
            return "Coordinating";
        case CoordinationState::Coordinated:
            return "Coordinated";
        case CoordinationState::Revising:
            return "Revising";
        case CoordinationState::Abrogating:
            return "Abrogating";
        default:
            throw std::invalid_argument( "Invalid coordination state enum value" );
    }
}

FlightEnums::CoordinationState FlightEnums::stringToCoordinationState( const std::string& coordinationStateAsString )
{
    if( coordinationStateAsString == "NOT_SET" )
    {
        return CoordinationState::CoordinationState_NOT_SET;
    }
    else if( coordinationStateAsString == "None" )
    {
        return CoordinationState::CoordinationState_None;
    }
    else if( coordinationStateAsString == "Notifying" )
    {
        return CoordinationState::Notifying;
    }
    else if( coordinationStateAsString == "Notified" )
    {
        return CoordinationState::Notified;
    }
    else if( coordinationStateAsString == "Coordinating" )
    {
        return CoordinationState::Coordinating;
    }
    else if( coordinationStateAsString == "Coordinated" )
    {
        return CoordinationState::Coordinated;
    }
    else if( coordinationStateAsString == "Revising" )
    {
        return CoordinationState::Revising;
    }
    else if( coordinationStateAsString == "Abrogating" )
    {
        return CoordinationState::Abrogating;
    }
    else
    {
        throw std::invalid_argument( "Invalid coordination state string value: " + coordinationStateAsString );
    }
}

} // namespace asd::editor::tracklabelfield