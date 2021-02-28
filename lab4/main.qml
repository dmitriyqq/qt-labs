import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Справочник филателиста")

    ScrollView {
        id:  scrollView
        anchors.fill: parent

        ListView {
            id: stampList
            width: parent.width
            model: philatelyModel
            delegate: StampItemDelegate {}
        }
    }

    Button {
        id: addButton
        anchors.bottom: scrollView.bottom
        anchors.margins: 8
        anchors.right:editButton.left
        text: "Добавить марку"
        width: 100
        onClicked: {
            windowAddEdit.currentIndex = -1
            windowAddEdit.show()
        }
    }

    Button {
        id: editButton
        anchors.bottom: scrollView.bottom
        anchors.right: deleteButton.left
        anchors.margins: 8
        enabled: stampList.currentIndex >= 0
        text: "Редактировать"
        width: 100
        onClicked: {
            var stampName = stampList.currentItem.stampData.stampName
            var stampCountry = stampList.currentItem.stampData.stampCountry
            var stampYear = stampList.currentItem.stampData.stampYear
            var stampNumberIssued = stampList.currentItem.stampData.stampNumberIssued

            windowAddEdit.execute(stampList.currentIndex, stampName, stampCountry, stampYear, stampNumberIssued)
        }
    }

    Button {
        id: deleteButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right:parent.right
        anchors.rightMargin: 8
        text: "Удалить марку"
        width: 100
        enabled: stampList.currentIndex >= 0
        onClicked: del(stampList.currentIndex)
    }

    AddOrEditStampDialog {
        id: windowAddEdit
    }
}
