/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#include "FieldLayout.h"

namespace asd::editor::tracklabelfield
{

FieldLayout::FieldLayout( QObject *parent ) : QObject( parent )
{
}

QPointF FieldLayout::position() const
{
    return m_position;
}

int FieldLayout::width() const
{
    return m_width;
}

int FieldLayout::height() const
{
    return m_height;
}

int FieldLayout::fontAdjustment() const
{
    return m_fontAdjustment;
}

int FieldLayout::fixedWidthInCharacters() const
{
    return m_fixedWidthInCharacters;
}

int FieldLayout::leftMargin() const
{
    return m_leftMargin;
}

int FieldLayout::bottomMargin() const
{
    return m_bottomMargin;
}

void FieldLayout::setPosition( const QPointF &position )
{
    if( m_position != position )
    {
        m_position = position;
        emit positionChanged();
    }
}

void FieldLayout::setWidth( int width )
{
    if( m_width != width )
    {
        m_width = width;
        emit widthChanged();
    }
}

void FieldLayout::setHeight( int height )
{
    if( m_height != height )
    {
        m_height = height;
        emit heightChanged();
    }
}

void FieldLayout::setFontAdjustment( int fontAdjustment )
{
    if( m_fontAdjustment != fontAdjustment )
    {
        m_fontAdjustment = fontAdjustment;
        emit fontAdjustmentChanged();
    }
}

void FieldLayout::setFixedWidthInCharacters( int fixedWidthInCharacters )
{
    if( m_fixedWidthInCharacters != fixedWidthInCharacters )
    {
        m_fixedWidthInCharacters = fixedWidthInCharacters;
        emit fixedWidthInCharactersChanged();
    }
}

void FieldLayout::setLeftMargin( int leftMargin )
{
    if( m_leftMargin != leftMargin )
    {
        m_leftMargin = leftMargin;
        emit leftMarginChanged();
    }
}

void FieldLayout::setBottomMargin( int bottomMargin )
{
    if( m_bottomMargin != bottomMargin )
    {
        m_bottomMargin = bottomMargin;
        emit bottomMarginChanged();
    }
}

} // namespace asd::editor::tracklabelfield