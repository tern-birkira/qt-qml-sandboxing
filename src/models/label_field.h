#pragma once

#include <QString>
#include <QHash>


struct LabelField {
    QString label_name;
    QString label_value;
};



// Realistic dummy values based on a fictional IFR flight:
//   ICE425  BIKF (Keflavik) → EGLL (London Heathrow)
//   B738/M, FL350, M082, squawk 2347, Reykjavik ACC (BIRD)
static const QHash<QString, QString> labelFieldsData = {
    // --- Standard fields ---
    { "aircraftType",                                    "B738"          },
    { "assignedVerticalRate",                            "1500"          },
    { "callsign",                                        "ICE425"        },
    { "calculatedTakeOffTime",                           "1428"          },
    { "clearedFlightLevel",                              "FL350"         },
    { "clearedFlightLevelOrApproach",                    "FL350"         },
    { "clearedHeadingOrWaypoint",                        "RATSU"         },
    { "clearedHeading",                                  "093"           },
    { "currentControllingSector",                        "BIRD_N"        },
    { "nextControllingSector",                           "BIRD_S"        },
    { "currentSectorFrequency",                          "132.025"       },
    { "nextSectorFrequency",                             "135.600"       },
    { "sectorIndicator",                                 "N"             },
    { "waypoint",                                        "DETKO"         },
    { "eobtOrCtot",                                      "1415"          },
    { "clearedSpeed",                                    "M082"          },
    { "ssrCodeAndCallsign",                              "2347/ICE425"   },
    { "snsInhibitedSsrDot",                              ""              },
    { "combinedAircraftTypeAndWTC",                      "B738/M"        },
    { "currentFlightLevel",                              "350"           },
    { "destinationAerodrome",                            "EGLL"          },
    { "freeText",                                        "RVSM APPROVED" },
    { "speed",                                           "M082"          },
    { "ssrCode",                                         "2347"          },
    { "transferArrow",                                   "→"             },
    { "verticalRateArrow",                               "↑"             },
    { "verticalRate",                                    "↑1500"         },
    { "wakeTurbulenceCategory",                          "M"             },
    { "alternativeDestinationAeroDrome",                 "EGKK"          },
    { "alternativeDestinationAeroDrome2",                "EHAM"          },
    { "assignedSSRCode",                                 "2347"          },
    { "currentFrequency",                                "132.025"       },
    { "departureAerodrome",                              "BIKF"          },
    { "destinationRunway",                               "27L"           },
    { "firExitPoint",                                    "MIMKU"         },
    { "firExitFlightLevel",                              "FL350"         },
    { "firExitTime",                                     "1532"          },
    { "flightRule",                                      "I"             },
    { "flightType",                                      "S"             },
    { "clearedHoldingPoint",                             "SOSIM"         },
    { "holdingTerminationTime",                          "1510"          },
    { "numberOfAircraft",                                "1"             },
    { "previousSSRCode",                                 "2346"          },
    { "requestedFlightLevel",                            "FL390"         },
    { "route",                                           "DCT RATSU DCT" },
    { "clearedStar",                                     "MATCH1A"       },
    { "clearedApproach",                                 "ILS27L"        },
    { "measuredFlightLevel",                             "349"           },
    { "actualDepartureTime",                             "1429"          },
    { "reportedLevel",                                   "FL350"         },
    { "approachSequenceNumber",                          "3"             },
    { "sectorCoordinatedPointOfExitLevel",               "FL350"         },
    { "sectorCoordinatedPointOfExitAndEnrouteCruisingLevel", "FL350/FL350" },
    { "sectorPlannedEntryLevel",                         "FL350"         },
    { "controlStateString",                              "ASSUMED"       },
    { "sectorCoordinatedPointOfEntry",                   "RATSU"         },
    { "sectorCoordinatedPointOfExit",                    "MIMKU"         },
    { "sectorCoordinatedPointOfExitTime",                "1532"          },
    { "sectorCoordinatedPointOfEntryTime",               "1445"          },
    { "nextRouteElement",                                "MIMKU"         },
    { "currentRouteElement",                             "RATSU"         },
    // --- Downlinked / ADS-B fields ---
    { "indicatedAirspeed",                               "280"           },
    { "magneticHeading",                                 "093"           },
    { "trueAirspeed",                                    "465"           },
    { "selectedAltitude",                                "FL350"         },
    { "finalStateSelectedAltitude",                      "FL350"         },
    { "flightStatusReportedByAdsB",                      "AIRBORNE"      },
    { "barometricVerticalRate",                          "+512"          },
    { "geometricVerticalRate",                           "+480"          },
    { "machNumber",                                      "M082"          },
    { "barometricPressureSettings",                      "1013"          },
};

// QMap<QString, LabelField> fields;
// for (auto it = dummyValues.constBegin(); it != dummyValues.constEnd(); ++it) {
//     fields.insert(it.key(), LabelField{it.key(), it.value()});
// }
// return fields;
// }