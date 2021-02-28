import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4  // это версия библиотеки, содержащей Contol (аналоги виджетов) для версии Qt 5.6
import QtQuick.Layouts 1.2


ApplicationWindow {
    id: root
    modality: Qt.ApplicationModal
    title: qsTr("Добавить марку")
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 200
    maximumHeight: 200

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
            model:  [ "Poland", "United Kingdom", "Yemen", "USA", "Ukraine", "Russia" ]
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
        text: qsTr("Добавить марку")
        width: 100
        onClicked: {
            root.hide()
            add(textName.text, textCountry.currentText, textYear.text, textCount.text)
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
    // изменение статуса видимости окна диалога
    onVisibleChanged: {
      if (visible) {
          textName.text = ""
          textYear.text = ""
          textCount.text = ""
          textCountry.currentIndex = 0;
      }
    }
 }
