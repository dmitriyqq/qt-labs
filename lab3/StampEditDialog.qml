import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4  // это версия библиотеки, содержащей Contol (аналоги виджетов) для версии Qt 5.6
import QtQuick.Layouts 1.2


Window {
    id: root
    modality: Qt.ApplicationModal  // окно объявляется модальным
    title: qsTr("Редактирование информации о студенте")
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 200
    maximumHeight: 200

    property int currentIndex: -1

    GridLayout {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: buttonCancel.top; margins: 10 }
        columns: 2

        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Название:")
        }
        TextField {
            id: textName
            Layout.fillWidth: true
            placeholderText: qsTr("название")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Страна:")
        }
        ComboBox {
            id: textCountry
            Layout.fillWidth: true
            model: [ "Poland", "United Kingdom", "Yemen", "USA", "Ukraine", "Russia" ]
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Год выпуска:")
        }
        TextField {
            id: textYear
            Layout.fillWidth: true
            placeholderText: qsTr("Год выпуска")
        }
        Label {
            Layout.alignment: Qt.AlignRight
            text: qsTr("Количество выпущенных марок:")
        }
        TextField {
            id: textCount
            Layout.fillWidth: true
            placeholderText: qsTr("2000")
        }
    }

    Button {
        anchors { right: buttonCancel.left; verticalCenter: buttonCancel.verticalCenter; rightMargin: 10 }
        text: qsTr("Применить")
        width: 100
        onClicked: {
            root.hide()
            edit(root.currentIndex, textName.text, textCountry.currentText, textYear.text, textCount.text)
        }
    }
    Button {
        id: buttonCancel
        anchors { right: parent.right; bottom: parent.bottom; rightMargin: 10; bottomMargin: 10 }
        text: qsTr("Отменить")
        width: 100
        onClicked: {
             root.hide()
        }
    }


    function execute(index, name, country, year, numberIssued){
        textName.text = name
        textYear.text = year
        textCount.text = numberIssued
        textCountry.currentIndex = textCountry.find(country)
        root.currentIndex = index
        root.show()
    }
 }
