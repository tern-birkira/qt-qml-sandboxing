/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/


#include "FieldInterface.h"

namespace asd::editor::tracklabelfield
{

FieldInterface::FieldInterface( QObject *parent ) : QObject( parent )
{
    m_fieldText = std::make_unique< FieldText >( this );
    m_fieldAppearance = std::make_unique< FieldAppearance >( this );
    m_fieldLayout = std::make_unique< FieldLayout >( this );
}

FieldText* FieldInterface::fieldText() const
{
    return m_fieldText.get();
}

FieldAppearance* FieldInterface::fieldAppearance() const
{
    return m_fieldAppearance.get();
}

FieldLayout* FieldInterface::fieldLayout() const
{
    return m_fieldLayout.get();
}

} // namespace asd::editor::tracklabelfield