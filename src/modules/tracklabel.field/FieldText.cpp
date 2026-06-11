/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#include "FieldText.h"
#include <qobject.h>

namespace asd::editor::tracklabelfield
{

FieldText::FieldText( QObject *parent ) : QObject( parent )
{
}

QString FieldText::fieldName() const
{
    return m_fieldName;
}

QString FieldText::displayName() const
{
    return m_displayName;
}

QString FieldText::fieldType() const
{
    return m_fieldType;
}

QString FieldText::prefix() const
{
    return m_prefix;
}

QString FieldText::placeholder() const
{
    return m_placeholder;
}

void FieldText::setFieldName( const QString &fieldName )
{
    if( m_fieldName != fieldName )
    {
        m_fieldName = fieldName;
        emit fieldNameChanged();
    }
}

void FieldText::setDisplayName( const QString &displayName )
{
    if( m_displayName != displayName )
    {
        m_displayName = displayName;
        emit displayNameChanged();
    }
}

void FieldText::setFieldType( const QString &fieldType )
{
    if( m_fieldType != fieldType )
    {
        m_fieldType = fieldType;
        emit fieldTypeChanged();
    }
}

void FieldText::setPrefix( const QString &prefix )
{
    if( m_prefix != prefix )
    {
        m_prefix = prefix;
        emit prefixChanged();
    }
}

void FieldText::setPlaceholder( const QString &placeholder )
{
    if( m_placeholder != placeholder )
    {
        m_placeholder = placeholder;
        emit placeholderChanged();
    }
}

} // namespace asd::editor::tracklabelfield