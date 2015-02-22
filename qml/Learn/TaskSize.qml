import QtQuick 2.4
import QtQuick.Controls 1.3

Rectangle {
    signal reset(int numLast, int numOther)

    function triggerReset(){
        var numLast = numLastEntriesModel.get(numLastEntries.currentIndex).num,
            numOther = numOtherEntriesModel.get(numOtherEntries.currentIndex).num;

        reset(numLast, numOther);
    }

    width: 100
    height: 100

    ComboBox {
        id: numLastEntries
        anchors.right: parent.right
        anchors.topMargin: 10

        currentIndex: 4
        model: ListModel {
            id: numLastEntriesModel
            ListElement { text: "10"; num: 10 }
            ListElement { text: "20"; num: 20 }
            ListElement { text: "30"; num: 30 }
            ListElement { text: "40"; num: 40 }
            ListElement { text: "50"; num: 50 }
            ListElement { text: "60"; num: 60 }
            ListElement { text: "70"; num: 70 }
            ListElement { text: "80"; num: 80 }
            ListElement { text: "90"; num: 90 }
            ListElement { text: "100"; num: 100 }
            ListElement { text: "All"; num: -1 }
        }
    }

    ComboBox {
        id: numOtherEntries
        anchors.top: numLastEntries.bottom
        anchors.right: parent.right
        anchors.topMargin: 10

        currentIndex: 4
        model: ListModel {
            id: numOtherEntriesModel
            ListElement { text: "10"; num: 10 }
            ListElement { text: "20"; num: 20 }
            ListElement { text: "30"; num: 30 }
            ListElement { text: "40"; num: 40 }
            ListElement { text: "50"; num: 50 }
            ListElement { text: "60"; num: 60 }
            ListElement { text: "70"; num: 70 }
            ListElement { text: "80"; num: 80 }
            ListElement { text: "90"; num: 90 }
            ListElement { text: "100"; num: 100 }
        }
    }

    Button
    {
        id: resetButton
        anchors.top: numOtherEntries.bottom
        anchors.right: parent.right
        anchors.topMargin: 10

        text: "Reset"
        onClicked: triggerReset()
    }
}

