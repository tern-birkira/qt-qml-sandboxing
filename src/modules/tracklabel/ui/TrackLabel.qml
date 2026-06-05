import QtQuick
import TrackLabelModels 1.0

Item {

    // ── Outer ListView — one RowContainer per row ──
    ListView {
        id: rowListView

        // layoutModel is the RowListModel* from context
        model: layoutModel

        // Delegate is our RowContainer which holds a Repeater internally
        delegate: RowContainer {}

        // Needed so ListView sizes to content rather than clipping
        implicitHeight: contentHeight

        spacing: 2
        clip: true
    }
}