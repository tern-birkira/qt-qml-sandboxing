#include "TrackLabelEditorModel.h"

namespace asd::editor::tracklabel
{

TrackLabelEditorModel::TrackLabelEditorModel(QObject *parent) : QObject(parent)
{
    m_layouts[Uncorrelated]    = new RowListModel(this);
    m_layouts[Correlated]      = new RowListModel(this);
    m_layouts[Ground]          = new RowListModel(this);
    m_layouts[FlightPlanTrack] = new RowListModel(this);
    
    // Initial instantiation loop bypasses signals in constructors:
    // e.g., m_layouts[Uncorrelated]->appendRow();
}

void TrackLabelEditorModel::setActiveType(LabelType type) {
    if (m_activeType == type) return;
    m_activeType = type;
    emit activeTypeChanged();
    emit currentLayoutChanged();
    clearSelection();
    reevaluateActiveLayoutVisibility();
}

void TrackLabelEditorModel::setActiveVisibility(VisibilityState state) {
    if (m_activeVisibility == state) return;
    m_activeVisibility = state;
    emit activeVisibilityChanged();
    reevaluateActiveLayoutVisibility();
}

void TrackLabelEditorModel::setActiveControlState(int state) {
    if (m_activeControlState == state) return;
    m_activeControlState = state;
    emit activeControlStateChanged();
    reevaluateActiveLayoutVisibility();
}

RowListModel* TrackLabelEditorModel::currentLayout() const {
    return m_layouts.value(m_activeType, nullptr);
}

void TrackLabelEditorModel::selectField(int rowIndex, int colIndex) {
    auto* layout = currentLayout();
    if (!layout) return;

    auto rowIdx = layout->index(rowIndex);
    auto* cellModel = layout->data(rowIdx, RowListModel::CellModelRole).value<RowCellModel*>();
    if (cellModel && colIndex >= 0 && colIndex < cellModel->cellCount()) {
        m_selectedField = cellModel->cellAt(colIndex);
        emit selectedFieldChanged();
    }
}

void TrackLabelEditorModel::clearSelection() {
    if (m_selectedField) {
        m_selectedField = nullptr;
        emit selectedFieldChanged();
    }
}

void TrackLabelEditorModel::reevaluateActiveLayoutVisibility() {
    auto* layout = currentLayout();
    if (!layout) return;

    for (int r = 0; r < layout->rowCount(); ++r) {
        auto rowIdx = layout->index(r);
        auto* cellModel = layout->data(rowIdx, RowListModel::CellModelRole).value<RowCellModel*>();
        if (!cellModel) continue;

        cellModel->evalVisability(m_activeVisibility, m_activeControlState);
    }
}

}