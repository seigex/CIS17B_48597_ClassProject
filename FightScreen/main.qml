import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: applicationWindow1
    width: 640
    height: 480
    visible: true
    title: qsTr("FightScreen")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Button {
        id: fight_button
        width: 133
        height: 61
        text: qsTr("Fight")
        anchors.left: what_will_you_do_text.left
        anchors.leftMargin: 0
        anchors.top: what_will_you_do_text.bottom
        anchors.topMargin: 6
        tooltip: "Click to attack"
    }

    Button {
        id: item_button
        width: 129
        height: 61
        text: qsTr("Item")
        anchors.right: what_will_you_do_text.right
        anchors.bottom: fight_button.bottom
        anchors.top: fight_button.top
        anchors.topMargin: 0
        anchors.left: escape_button.left
        anchors.leftMargin: 0
        tooltip: "Click to use an item"
    }

    Button {
        id: escape_button
        width: 129
        height: 66
        text: qsTr("Escape")
        anchors.right: what_will_you_do_text.right
        anchors.bottom: hero_image.bottom
        anchors.left: parent.left
        anchors.leftMargin: 456
        anchors.top: magic_button.top
        anchors.topMargin: 0
        tooltip: "Click to try and escape the fight"
    }

    Button {
        id: magic_button
        width: 133
        height: 66
        text: qsTr("Magic")
        anchors.right: fight_button.right
        anchors.bottom: hero_image.bottom
        anchors.left: what_will_you_do_text.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 379
        tooltip: "Click to cast a spell"
    }

    Image {
        id: hero_image
        width: 279
        height: 202
        anchors.top: hero_health_bar.bottom
        anchors.topMargin: 6
        anchors.left: action_text_box.left
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    ProgressBar {
        id: enemy_health_bar
        width: 196
        height: 23
        clip: false
        transformOrigin: Item.Center
        indeterminate: false
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 414
        value: 100
        maximumValue: 100
    }

    ProgressBar {
        id: hero_health_bar
        width: 279
        height: 25
        anchors.right: hero_image.right
        anchors.top: parent.top
        anchors.topMargin: 212
        anchors.left: hero_image.left
        anchors.leftMargin: 0
        value: 100
        maximumValue: 100
    }

    Text {
        id: what_will_you_do_text
        width: 262
        height: 40
        text: qsTr("What will you do?")
        anchors.left: parent.left
        anchors.leftMargin: 323
        anchors.top: parent.top
        anchors.topMargin: 271
        verticalAlignment: Text.AlignVCenter
        font.family: "Arial"
        font.italic: false
        font.underline: false
        font.strikeout: false
        font.bold: true
        font.pixelSize: 29
        horizontalAlignment: Text.AlignHCenter
    }

    Text {
        id: action_text_box
        x: 29
        y: 15
        width: 285
        height: 80
        text: qsTr("Enemy Attacks!")
        style: Text.Normal
        font.bold: true
        font.pixelSize: 20
        anchors.top: enemy_health_bar.top
    }

    Image {
        id: enemy_image
        x: 414
        y: 44
        width: 154
        height: 146
        fillMode: Image.PreserveAspectFit
        anchors.top: enemy_health_bar.bottom
        anchors.topMargin: 6
        anchors.left: enemy_health_bar.left
        anchors.rightMargin: 0
        anchors.right: enemy_health_bar.right
        source: "resource/app_full_proxy.php.png"
    }
}
