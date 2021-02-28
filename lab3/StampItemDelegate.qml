import QtQuick 2.0
Rectangle  {

    readonly property color backgroundColor1: "#111"  // цвет для четных пунктов списка
    readonly property color backgroundColor2: "aquamarine"  // цвет выделенного элемента списка

    id: stampItem
    width: parent.width
    height: 100
    property variant stampData: model

    property bool isCurrent: stampItem.ListView.view.currentIndex === index
    property bool selected: stampItemMouseArea.containsMouse || isCurrent

    states: [
        State {
            when: selected
            PropertyChanges {
                target: stampItem
                color: isCurrent ? "red" : "aquamarine"
            }
       },
        State {
            when: !selected
            PropertyChanges {
                target: stampItem
                color: "#111"
            }
        }
    ]

    MouseArea {
        id: stampItemMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            stampItem.ListView.view.currentIndex = index
            stampItem.forceActiveFocus()
        }
    }

    Row {
        width: parent.width
        Column {
            width: parent.width / 2
            Text {
                text: "Марка: " + stampName
                color: "white"
                font.pixelSize: 24
            }
        }

        Column {
            width: parent.width / 2
            anchors.verticalCenter: parent.verticalCenter

            Text {
                width: parent.width
                text: "Страна: " + stampCountry
                color: "white"
                font.pixelSize: 24
            }

            Text {
                width: parent.width
                text: "Год: " + stampYear
                color: "white"
                font.pixelSize: 24
            }

            Text {
                width: parent.width
                text: "Количество: " + stampNumberIssued
                color: "white"
                font.pixelSize: 24
            }
        }
    }
}

