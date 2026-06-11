/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#ifndef _asd_editor_trackLabelEditor_FieldAppearance_h_
#define _asd_editor_trackLabelEditor_FieldAppearance_h_

/*
 * Local header files
 */
#include "FlightEnums.h"
/*
 * System header files
 */
#include <QObject>
#include <qtmetamacros.h>

namespace asd::editor::tracklabelfield
{

struct VisibilityCondition
{
    std::string m_flightProperty;
    std::vector< std::string > m_values;
};
/*
 * The FieldAppearance class represents the appearance properties of a field in the track label, such as
 * whether the field is toggleable, only shown on focus, or visible in holding. It also contains
 * the visibility condition for the field, which determines under which conditions the field should be
 * visible based on flight properties and their values.
 */
class FieldAppearance : public QObject
{
Q_OBJECT
Q_PROPERTY( bool toggleable READ toggleable WRITE setToggleable NOTIFY toggleableChanged )
Q_PROPERTY( bool onlyShowOnFocus READ onlyShowOnFocus WRITE setOnlyShowOnFocus NOTIFY onlyShowOnFocusChanged )
Q_PROPERTY( bool visibleInHolding READ visibleInHolding WRITE setVisibleInHolding NOTIFY visibleInHoldingChanged )
Q_PROPERTY( bool isVisable )

public:
    explicit FieldAppearance( QObject *parent = nullptr );

    // Getters
    bool toggleable() const;
    bool onlyShowOnFocus() const;
    bool visibleInHolding() const;

    // Setters
    void setToggleable( bool toggleable );
    void setOnlyShowOnFocus( bool onlyShowOnFocus );
    void setVisibleInHolding( bool visibleInHolding );

signals:
    void toggleableChanged();
    void onlyShowOnFocusChanged();
    void visibleInHoldingChanged();

private:
    // Members
    bool m_toggleable = false;
    bool m_onlyShowOnFocus = false;
    bool m_visibleInHolding = false;
    VisibilityCondition m_visibilityCondition;
    std::vector< FlightEnums::ControlState > m_controlStateVisibility;
};

}

#endif // _asd_editor_trackLabelEditor_FieldAppearance_h_