/*****************************************************************************
 * Copyright (c) 1998-2024, Tern Systems Inc.
 * All Rights Reserved.
 *****************************************************************************/

#ifndef _asd_editor_trackLabelEditor_TrackLabelField_h_
#define _asd_editor_trackLabelEditor_TrackLabelField_h_

/*
 * Local header files
 */
#include "FieldText.h"
#include "FieldAppearance.h"
#include "FieldLayout.h"
/*
 * System header files
 */
#include <QObject>
#include <QString>
#include <QPointF>

namespace asd::editor::tracklabelfield
{
/**
 * @brief The FieldInterface class acts as a mediator between the FieldModel and the
 * individual field properties (text, appearance, layout) in the track label editor.
 * It provides a structured way to access and modify the properties of each field while
 * keeping them organized and encapsulated.
 */
class FieldInterface : public QObject
{
Q_OBJECT
Q_PROPERTY( FieldText * m_fieldText READ fieldText CONSTANT )
Q_PROPERTY( FieldAppearance * m_fieldAppearance READ fieldAppearance CONSTANT )
Q_PROPERTY( FieldLayout * m_fieldLayout READ fieldLayout CONSTANT )

public:
    /**
     * @brief Construct a new Field Interface object
     * @param parent The parent QObject, default is nullptr
     */
    explicit FieldInterface( QObject *parent = nullptr );

    // Getters
    [[nodiscard]] FieldText* fieldText() const;
    [[nodiscard]] FieldAppearance* fieldAppearance() const;
    [[nodiscard]] FieldLayout* fieldLayout() const;

private:
    // Member variables
    std::unique_ptr< FieldText > m_fieldText;
    std::unique_ptr< FieldAppearance > m_fieldAppearance;
    std::unique_ptr< FieldLayout > m_fieldLayout;
};

} // namespace asd::editor::tracklabelfield

#endif // _asd_editor_trackLabelEditor_FieldInterface_h_