/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#ifndef _asd_editor_trackLabelEditor_FieldText_h_
#define _asd_editor_trackLabelEditor_FieldText_h_

/*
 * System header files
 */
#include <QObject>
#include <QString>

namespace asd::editor::tracklabelfield
{

/*
 * The FieldText class represents the text properties of a field in the track label, such as
 * the field name, display name, field type, prefix, and placeholder text. It provides
 * getters and setters for these properties, along with signals that are emitted when
 * the properties change.
 */
class FieldText : public QObject
{
Q_OBJECT
Q_PROPERTY( QString fieldName READ fieldName WRITE setFieldName NOTIFY fieldNameChanged )
Q_PROPERTY( QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged )
Q_PROPERTY( QString fieldType READ fieldType WRITE setFieldType NOTIFY fieldTypeChanged )
Q_PROPERTY( QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged )
Q_PROPERTY( QString placeholder READ placeholder WRITE setPlaceholder NOTIFY placeholderChanged )

friend class FieldInterface;

public:

    explicit FieldText( QObject *parent = nullptr );

    // Getters
    QString fieldName() const;
    QString displayName() const;
    QString fieldType() const;
    QString prefix() const;
    QString placeholder() const;

    // Setters
    void setFieldName( const QString &fieldName );
    void setDisplayName( const QString &displayName );
    void setFieldType( const QString &fieldType );
    void setPrefix( const QString &prefix );
    void setPlaceholder( const QString &placeholder );

signals:
    void fieldNameChanged();
    void displayNameChanged();
    void fieldTypeChanged();
    void prefixChanged();
    void placeholderChanged();

private:
    QString m_fieldName;
    QString m_displayName;
    QString m_fieldType;
    QString m_prefix;
    QString m_placeholder;
};

}

#endif // _asd_editor_trackLabelEditor_FieldText_h