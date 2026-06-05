#pragma once
#include <QString>

// ─────────────────────────────────────────────
//  Plain data struct — one cell in the grid.
//  No QObject needed; the model owns all cells.
// ─────────────────────────────────────────────
struct TrackLabelField
{
    // Visible
    QString label;
    int     width  = 120;   // pixels hint for the delegate
    QString color  = "#ffffff";

    // Invisible / behavioural
    int     id     = -1;    // unique stable id assigned on creation
    bool    isActive  = true;
    QString extraData;      // extend freely
};