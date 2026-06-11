/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#ifndef _asd_editor_trackLabelEditor_FieldLayout_h_
#define _asd_editor_trackLabelEditor_FieldLayout_h_

#include <QObject>
#include <QPointF>

namespace asd::editor::tracklabelfield
{

/*
 * Represents the layout of a field in the track label editor. It contains properties such as
 * position, width, height, font adjustment, fixed width in characters, left margin, and
 * bottom margin.
 */
class FieldLayout : public QObject
{
Q_OBJECT
Q_PROPERTY( QPointF position READ position WRITE setPosition NOTIFY positionChanged )
Q_PROPERTY( int width READ width WRITE setWidth NOTIFY widthChanged )
Q_PROPERTY( int height READ height WRITE setHeight NOTIFY heightChanged )
Q_PROPERTY( int fixedWidthInCharacters READ fixedWidthInCharacters WRITE setFixedWidthInCharacters NOTIFY fixedWidthInCharactersChanged )
Q_PROPERTY( int leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged )
Q_PROPERTY( int fontAdjustment READ fontAdjustment WRITE setFontAdjustment NOTIFY fontAdjustmentChanged )
Q_PROPERTY( int bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged )

public:
    explicit FieldLayout( QObject * parent = nullptr );

    // Getters
    QPointF position() const;
    int width() const;
    int height() const;
    int fontAdjustment() const;
    int fixedWidthInCharacters() const;
    int leftMargin() const;
    int bottomMargin() const;

    // Setters
    void setPosition( const QPointF &position );
    void setWidth( int width );
    void setHeight( int height );
    void setFontAdjustment( int fontAdjustment );
    void setFixedWidthInCharacters( int fixedWidthInCharacters );
    void setLeftMargin( int leftMargin );
    void setBottomMargin( int bottomMargin );

signals:
    // Signals emitted when properties change
    void positionChanged();
    void widthChanged();
    void heightChanged();
    void fontAdjustmentChanged();
    void fixedWidthInCharactersChanged();
    void leftMarginChanged();
    void bottomMarginChanged();

private:
    // Members
    QPointF m_position;
    int m_width = 100;
    int m_height = 20;
    int m_fontAdjustment = 0;
    int m_fixedWidthInCharacters = -1;
    int m_leftMargin = 0;
    int m_bottomMargin = 0;

};

}

#endif // _asd_editor_trackLabelEditor_FieldLayout_h_