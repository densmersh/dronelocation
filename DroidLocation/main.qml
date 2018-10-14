import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtLocation 5.6
import QtPositioning 5.6
import Location 1.0

Window {
    id:mainWindow
    visible: true
    height: 720
    width: 1240
    title: qsTr("LocatDrone")

    Location
    {
        id:location
    }

    function changeTrack(latitude, longtitude) {
        map.track.replaceCoordinate(1, QtPositioning.coordinate(latitude, longtitude));
//        map.center = QtPositioning.coordinate(dronePoint.coordinate)
    }

    function changeHomePosition(latitude, longtitude) {
        map.track.replaceCoordinate(0,QtPositioning.coordinate(latitude, longtitude));
    }

    Connections{
        target: location
        onCoordinatesHPUpdated:
        {
            homePoint.coordinate = QtPositioning.coordinate(location.hpLatitude, location.hpLongtitude)
            changeHomePosition(location.hpLatitude, location.hpLongtitude)
        }

        onHpSatellitesInUseChanged:
        {
            satelliteCountOnSmartText.text = hpSatellitesInUse
        }

        onDistanceToDroneChanged:
        {
            distanceToDroneText.text = distanceToDrone
        }

        onInitializedGPSPhone:{
            rectLoading.visible = "false"
            mainRect.visible = "true"
        }
    }

    Component.onCompleted: {
        imageLoading.state = "show"
        backLoading.state = "show"
    }

    Rectangle{
        id:rectLoading
        visible: true
        anchors.fill: parent
        color:"#ffffff"

        Image {
            id: backLoading
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            source: "images/milkiway.jpg"
            state:"hide"


//            fillMode: Image.Tile
//            fillMode: Image.PreserveAspectFit

            states:[
               State {
                  name: "hide"
                  PropertyChanges {target: backLoading; x:-(backLoading.width - mainWindow.width) }
               },
              State {
                 name: "show"
                 PropertyChanges {target: backLoading;x:mainWindow.x}
              }
            ]

            transitions: Transition {
               NumberAnimation { properties: "x"; duration: 60000 }
            }
        }


        Image {
            id: imageLoading
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "images/satellite.png"
            transformOrigin: Item.Center
            width: parent.width/7
            fillMode: Image.PreserveAspectFit
            state:"hide"

            states:[
               State {
                  name: "hide"
                  PropertyChanges {target: imageLoading; rotation:540 }
               },
              State {
                 name: "show"
                 PropertyChanges {target: imageLoading;rotation:0}
              }
            ]

            transitions: Transition {
               NumberAnimation { properties: "rotation"; duration: 60000}
            }

        }

        Text {
            id: textLoading
            x: 578
            y: 497
            color: "#989090"
            text: qsTr("Поиск спутников...")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: mainWindow.height/7
            font.pixelSize: 25
        }
    }

    Rectangle{
        id:mainRect
        color: "#d3d7cf"
        visible: false
        anchors.fill: parent

        Plugin {
               id: mapPlugin
               name: "osm" // "mapboxgl", "esri", ...
               // specify plugin parameters if necessary
               // PluginParameter {
               //     name:
               //     value:
               // }
           }
//-------------------------------------------------------------------------------------------
           Map {
               id:map
               anchors.fill: parent
               plugin: mapPlugin
               center: homePoint.coordinate
               zoomLevel: 14


               property MapPolyline track
               property MapQuickItem mark

                   Component.onCompleted: {
                       map.track = Qt.createQmlObject('import QtLocation 5.6; MapPolyline {}', map, "main.qml")
                       map.track.line.color = "#f4427a"
                       map.track.line.width = 6
                       map.addMapItem(track)

                       map.track.addCoordinate(QtPositioning.coordinate(location.hpLatitude, location.hpLongtitude))
                       map.track.addCoordinate(QtPositioning.coordinate(location.droneLatitude, location.droneLongtitude))
                   }

               MapQuickItem{
                   id:dronePoint
                   coordinate: QtPositioning.coordinate(location.droneLatitude, location.droneLongtitude)
                   sourceItem: Image {
                       id: dronePointImage
                       source: "images/position.png"
                       width: mainWindow.height/12
                       fillMode: Image.PreserveAspectFit
                   }
                   anchorPoint.x: dronePoint.width / 2
                   anchorPoint.y: dronePoint.height
               }

               MapQuickItem{
                   id:homePoint
                   coordinate: QtPositioning.coordinate(location.hpLatitude, location.hpLongtitude)
                   sourceItem: Image {
                       id: homePointImage
                       source: "images/home.png"
                       width: mainWindow.height/10
                       fillMode: Image.PreserveAspectFit
                   }
                   anchorPoint.x: homePointImage.width / 2
                   anchorPoint.y: homePointImage.height
               }
           }
//___________________________________________________________________________________
            Rectangle
            {
                id:topPannel
                width:mainWindow.width
                height: mainWindow.height/8
                anchors.horizontalCenter: parent.horizontalCenter
                color:"#501f80"
                anchors.top: parent.top
                anchors.horizontalCenterOffset: 0
                y:mainWindow.y

                Rectangle
                {
                    id:additionalInfoTopPannel
                    height: mainWindow.height - topPannel.height
                    width: mainWindow.width / 3
                    x:mainWindow.x
                    color:"#234252"
                    state:"hide"

                    states:[
                       State {
                          name: "hide"
                          PropertyChanges {target: additionalInfoTopPannel; y:topPannel.y - additionalInfoTopPannel.height }
                       },
                      State {
                         name: "show"
                         PropertyChanges {target: additionalInfoTopPannel;y:topPannel.height }
                      }
                    ]

                    transitions: Transition {
                       NumberAnimation { properties: "y"; duration: 300 }
                    }


                }

                Grid
                {
                    anchors.fill: parent
                    columns: 6

                    Rectangle{
                        id: rectangleSatellitesOnDrone
                        height: parent.height
                        width: parent.width/6
                        color:topPannel.color
                        MouseArea
                        {
                            id:droneSatArea
                            anchors.fill:parent
                            onClicked:
                            {
                                if(additionalInfoTopPannel.state == "hide")
                                {
                                    parent.color = "#234252"
                                    additionalInfoTopPannel.state = "show"
                                }
                                else
                                {
                                    additionalInfoTopPannel.state = "hide"
                                    parent.color = "#501f80"
                                }
                            }

                            Image {
                                id: sattelitesCountOnDroneImage
                                anchors.verticalCenterOffset: 0
                                source: "images/remoteSignal.png"
                                width: mainWindow.height/10
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                fillMode: Image.PreserveAspectFit
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            TextEdit{
                                id:satelliteCountOnDrone
                                x: parent.width/2
                                y:parent.y
                                height: parent.height
                                color: "#ccf80303"
                                text: "7"
                                font.pointSize: 25
                                selectionColor: "#bff99d"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                width: parent.width/2
                                readOnly: true
                            }
                        }
                    }
                    Rectangle{
                        id: rectangleDistance
                        height: parent.height
                        width: parent.width/6
                        color:topPannel.color
                        MouseArea
                        {
                            id:droneDistanceArea
                            anchors.fill:parent
                            onClicked:
                            {
                                if(additionalInfoTopPannel.state == "hide")
                                {
                                    parent.color = "#234252"
                                    additionalInfoTopPannel.state = "show"
                                }
                                else
                                {
                                    additionalInfoTopPannel.state = "hide"
                                    parent.color = "#501f80"
                                }
                            }

                        Image {
                            id: currentDistanceImage
                            anchors.verticalCenter: parent.verticalCenter
                            source: "images/distance.png"
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: mainWindow.height/10
                            fillMode: Image.PreserveAspectFit
                        }
                        TextEdit{
                            id:distanceToDroneText
                            x:parent.width/2
                            y:parent.y
                            height: parent.height
                            color: "#ccf80303"
                            font.pointSize: 25
                            selectionColor: "#bff99d"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            width: parent.width/2
                            readOnly: true
                        }
                      }
                    }
                    Rectangle{
                        id: rectangleAltitude
                        height: parent.height
                        width: parent.width/6
                        color:topPannel.color

                        MouseArea
                        {
                            id:droneAltitudeArea
                            anchors.fill:parent
                            onClicked:
                            {
                                if(additionalInfoTopPannel.state == "hide")
                                {
                                    parent.color = "#234252"
                                    additionalInfoTopPannel.state = "show"
                                }
                                else
                                {
                                    additionalInfoTopPannel.state = "hide"
                                    parent.color = "#501f80"
                                }
                            }


                        Image {
                            id: currentAltitudeImage
                            anchors.verticalCenterOffset: 0
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            source: "images/altitude.png"
                            width: mainWindow.height/10
                            fillMode: Image.PreserveAspectFit
                        }
                        TextEdit{
                            id:droneAltitudeText
                            x:parent.width/2
                            y:parent.y
                            height: parent.height
                            color: "#ccf80303"
                            text: "100"
                            font.pointSize: 25
                            selectionColor: "#bff99d"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            width: parent.width/2
                            readOnly: true
                        }
                      }
                    }

                    Rectangle{
                        id: rectangleSmartSatelliteCount
                        height: parent.height
                        width: parent.width/6
                        color:topPannel.color

                        MouseArea
                        {
                            id:sattelitesCountOnSmartArea
                            anchors.fill:parent
                            onClicked:
                            {
                                if(additionalInfoTopPannel.state == "hide")
                                {
                                    parent.color = "#234252"
                                    additionalInfoTopPannel.state = "show"
                                }
                                else
                                {
                                    additionalInfoTopPannel.state = "hide"
                                    parent.color = "#501f80"
                                }
                            }

                        Image {
                            id: satelliteCountOnSmartImage
                            anchors.verticalCenterOffset: 0
                            source: "images/phoneSignal.png"
                            width: mainWindow.height/10
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            fillMode: Image.PreserveAspectFit
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        TextEdit{
                            id:satelliteCountOnSmartText
                            y:parent.y
                            x:parent.width/2
                            height: parent.height
                            color: "#ccf80303"
                            readOnly: true
                            font.pointSize: 25
                            selectionColor: "#bff99d"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            width: parent.width/2

                        }
                      }
                    }
                }


            }
            //-----------------------------------------------------------------------------------

            Column
            {
                id: grid
                width: mainWindow.width/12
                height: mainWindow.height - topPannel.height
                anchors.right: parent.right
                anchors.rightMargin: 20
                y:topPannel.height
             //   rows:3

                Rectangle {
                    id: rectangle
                    width: parent.width
                    height: width
                    color: "#501f80"
                  //  anchors.verticalCenter: parent.verticalCenter
                    radius: width
                    state:"hpObserver"

                    states:[
                       State {
                          name: "hpObserver"
                          PropertyChanges {target: rectangle; y:trackHP.y + trackHP.height/2 - rectangle.height/2 }
                       },
                      State {
                         name: "dpObserver"
                         PropertyChanges {target: rectangle; y:trackDP.y + trackDP.height/2 - rectangle.height/2 }
                      }
                    ]

                    transitions: Transition {
                       NumberAnimation { properties: "y"; duration: 50 }
                    }
                }

                        Image {
                            id: trackHP
                            source: "images/homeView.png"
                            width: mainWindow.height/10
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            fillMode: Image.PreserveAspectFit

                            MouseArea{
                                anchors.fill:parent
                                onClicked: {
                                    map.center = homePoint.coordinate
                                    rectangle.state = "hpObserver"
                                }
                            }
                         }

                        Image {
                            id: trackDP
                            source: "images/droneView.png"
                            width: mainWindow.height/10
                            anchors.bottom: trackHP.top
                            anchors.bottomMargin: 40
                            anchors.horizontalCenter: rectangle.horizontalCenter
                            fillMode: Image.PreserveAspectFit

                            MouseArea{
                                anchors.fill:parent
                                onClicked: {

                                        map.center = dronePoint.coordinate
                                        rectangle.state = "dpObserver"
                                }
                            }
                         }

            }

            //-------------------------------------------------------------------------------------

    }
}
