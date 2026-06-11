/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#include "FieldAppearance.h"

namespace asd::editor::tracklabelfield
{

FieldAppearance::FieldAppearance( QObject *parent ) : QObject( parent )
{
}

bool FieldAppearance::toggleable() const
{
    return m_toggleable;
}


bool FieldAppearance::onlyShowOnFocus() const
{
    return m_onlyShowOnFocus;
}

bool FieldAppearance::visibleInHolding() const
{
    return m_visibleInHolding;
}

void FieldAppearance::setToggleable( bool toggleable )
{
    if( m_toggleable != toggleable )
    {
        m_toggleable = toggleable;
        emit toggleableChanged();
    }
}


void FieldAppearance::setOnlyShowOnFocus( bool onlyShowOnFocus )
{
    if( m_onlyShowOnFocus != onlyShowOnFocus )
    {
        m_onlyShowOnFocus = onlyShowOnFocus;
        emit onlyShowOnFocusChanged();

    }
}

void FieldAppearance::setVisibleInHolding( bool visibleInHolding )
{
    if( m_visibleInHolding != visibleInHolding )
    {
        m_visibleInHolding = visibleInHolding;
        emit visibleInHoldingChanged();
    }
}

} // namespace asd::editor::tracklabelfield