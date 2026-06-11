#pragma once
#include <QObject>
#include <QHash>
#include <qtmetamacros.h>
#include "RowListModel.h"
#include "FieldInterface.h"
#include "EditorEnums.h"
#include "FlightEnums.h"
#include "types.h"

namespace asd::editor::tracklabel
{

class TrackLabelEditorModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LabelType activeType READ activeType WRITE setActiveType NOTIFY activeTypeChanged)
    Q_PROPERTY(VisibilityState activeVisibility READ activeVisibility WRITE setActiveVisibility NOTIFY activeVisibilityChanged)
    Q_PROPERTY(int activeControlState READ activeControlState WRITE setActiveControlState NOTIFY activeControlStateChanged)
    Q_PROPERTY(RowListModel* currentLayout READ currentLayout NOTIFY currentLayoutChanged)
    Q_PROPERTY(tracklabelfield::FieldInterface* selectedField READ selectedField NOTIFY selectedFieldChanged)

public:


    explicit TrackLabelEditorModel(QObject *parent = nullptr);
    virtual ~TrackLabelEditorModel() override = default;

    apptypes::tracklabel::LabelType activeType() const { return m_activeType; }
    void setActiveType(EditorEnums::LabelType type);

    EditorEnums::VisibilityState activeVisibility() const { return m_activeVisibility; }
    void setActiveVisibility(EditorEnums::VisibilityState state);

    int activeControlState() const { return m_activeControlState; }
    void setActiveControlState(int state);

    RowListModel* currentLayout() const;
    asd::editor::tracklabelfield::FieldInterface* selectedField() const { return m_selectedField; }

    Q_INVOKABLE void selectField(int rowIndex, int colIndex);
    Q_INVOKABLE void clearSelection();

signals:
    void activeTypeChanged();
    void activeVisibilityChanged();
    void activeControlStateChanged();
    void currentLayoutChanged();
    void selectedFieldChanged();

private:
    void reevaluateActiveLayoutVisibility();

    EditorEnums::LabelType m_activeType = EditorEnums::LabelType::Uncorrelated;
    EditorEnums::VisibilityState m_activeVisibility = EditorEnums::VisibilityState::Normal;
    tracklabelfield::FlightEnums::ControlState m_activeControlState = tracklabelfield::FlightEnums::ControlState::Unknown;

    QHash<EditorEnums::LabelType, RowListModel*> m_layouts;
    asd::editor::tracklabelfield::FieldInterface* m_selectedField = nullptr;
};

} // namespace asd::editor::tracklabel