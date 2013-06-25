import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import "../"

Rectangle
{
    id: dictionary

    anchors.fill: parent

    property int editedRecordIndex: -1

    property var deleteConfirmDialog: null


    function setStartState()
    {
        engTextField.text = ""
        rusTextField.text = ""
        transcriptionTextField.text = ""
        rusListModel.clear()
        engTextField.focus = true
        editingLayout.editedRusIndex = -1
        editedRecordIndex = -1
        deleteRecordButton.visible = false
    }

    function editRecord(recordIndex)
    {
        editedRecordIndex = recordIndex

        rusListModel.clear()
        var rusList = dictionaryModeCpp.CurrentCollectionModel.getRusList(recordIndex)
        for(var i=0; i<rusList.length; i++)
            rusListModel.append({rus: rusList[i]})

        engTextField.text = dictionaryModeCpp.CurrentCollectionModel.getEng(recordIndex)
        transcriptionTextField.text = dictionaryModeCpp.CurrentCollectionModel.getTranscription(recordIndex)

        deleteRecordButton.visible = true
    }

    Connections
    {
        target: dictionaryModeCpp
        onCurrentCollectionModelChanged: setStartState()
    }

    GridLayout{
        id: editingLayout
        columns: 2
        rows: 4

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        height: 200

        property int editedRusIndex: -1

        TextField
        {
            id: engTextField
            Layout.row: 0
            Layout.column: 0
            Layout.preferredWidth: 400

            placeholderText: "--eng--"

            Keys.onPressed:
            {
                if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter)
                {
                    if (text.length > 0)
                    {
                        rusTextField.focus = true;
                    }
                    event.accepted = false
                }
            }
        }

        TextField
        {
            id: rusTextField
            Layout.row: 1
            Layout.preferredWidth: 400

            placeholderText: "--rus--"

            Keys.onPressed:
            {
                if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter)
                {
                    if (text.length > 0)
                    {
                        var indexToInsert = (editingLayout.editedRusIndex == -1) ?rusListModel.count : editingLayout.editedRusIndex;
                        rusListModel.set(indexToInsert, { rus: text })
                        editingLayout.editedRusIndex = -1

                        text = ""
                    }
                    event.accepted = false
                }
            }
        }

        TextField
        {
            id: transcriptionTextField
            Layout.row: 2
            Layout.preferredWidth: 400

            placeholderText: "--transcription--"
        }

        Text
        {
            Layout.row: 3
            color: "#5ea63d"
            font.bold: true
            text: dictionaryModeCpp.CurrentCollectionModel.Count
        }

        Text
        {
            id: deleteRecordButton
            Layout.row: 3
            Layout.alignment: Qt.AlignRight
            text: "-delete-"
            color: 'blue'
            height: 30
            visible: false

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    var onOK = function() {
                        dictionaryModeCpp.CurrentCollectionModel.removeRecord(collectionRecordsTable.currentIndex);
                        dictionary.setStartState();
                    }
                    deleteConfirmDialog.show("Really delete?", onOK)
                }
            }
        }


        FancyButton
        {
            Layout.row: 3
            Layout.alignment: Qt.AlignCenter
            text: "Add"
            onClicked: parent.addRecord()
        }



        ListView
        {
            id: rusListView
            Layout.row: 0
            Layout.column: 1
            Layout.rowSpan: 4

            Layout.preferredWidth: 1
            Layout.preferredHeight: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true

            model: rusListModel
            delegate: Rectangle
            {
                id: delegateItem
                anchors.left: parent.left
                anchors.right: parent.right

                RowLayout{
                    spacing: 5

                    Rectangle //remove button
                    {
                        id: removeButton
                        width: 30
                        height: 30

                        Rectangle
                        {
                            anchors.centerIn: parent
                            anchors.verticalCenter: parent.verticalCenter
                            radius: 3
                            color: 'red'
                            width: 20
                            height: 6
                        }

                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked: rusListModel.remove(index)
                        }
                    }

                    Text // translation text
                    {
                        text:rus

                        MouseArea
                        {
                            anchors.fill: parent
                            onDoubleClicked:
                            {
                                editingLayout.editedRusIndex = index
                                rusTextField.text = rus
                                rusTextField.focus = true
                            }
                        }
                    }
                }

                ListView.onAdd: SequentialAnimation
                {
                    PropertyAction { target: delegateItem; property: "height"; value: 0 }
                    NumberAnimation { target: delegateItem; property: "height"; to: 30; duration: 250; easing.type: Easing.InOutQuad }
                }
            }
        }


ListModel
{
    id:rusListModel
}

function addRecord()
{
    if (engTextField.text.length != 0 &&
            (rusTextField.text.length != 0 || rusListModel.count != 0))
    {
        var rusList = []
        for(var i=0; i<rusListModel.count; i++)
        {
            rusList.push(rusListModel.get(i).rus)
        }

        if(rusTextField.text.length != 0 && editedRusIndex == -1)
            rusList.push(rusTextField.text)

        if(dictionary.editedRecordIndex == -1)
            dictionaryModeCpp.CurrentCollectionModel.addRecord(engTextField.text, transcriptionTextField.text, rusList)
        else
            dictionaryModeCpp.CurrentCollectionModel.setRecord(dictionary.editedRecordIndex, engTextField.text, transcriptionTextField.text, rusList)

        dictionary.setStartState()
    }
}

Keys.onPressed:
{
    if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter)
    {
        if(event.modifiers & Qt.ControlModifier)
        {
            addRecord()
        }
    }
}

}

ScrollView {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: editingLayout.bottom
    anchors.bottom: parent.bottom
    anchors.margins: 10

    ListView
    {
        id: collectionRecordsTable
        anchors.fill: parent
        anchors.rightMargin: 1

        model: dictionaryModeCpp.CurrentCollectionModel

        highlight: Rectangle {width: parent.width; color: "lightsteelblue"; radius: 5 }
        highlightMoveDuration: 50
        highlightResizeDuration: 0

        focus: true
        spacing: 10
        clip: true

        delegate: Component{
            Rectangle{
                color: 'transparent'
                border.color: "black"
                border.width: 1
                radius: 3

                width: parent.width
                height: childrens.height


                Rectangle{
                    id: childrens
                    width: parent.width
                    height: childrenRect.height
                    color: 'transparent'

                    Rectangle{
                        id: engRect
                        width: childrenRect.width
                        height: childrenRect.height
                        color: 'transparent'

                        Text{
                            x:5
                            text: "<b>" + eng + "</b>" +
                                  "<font color='#525252'>" + ((transcription == "") ? "" : " [ " + transcription + " ]") + "</font>"
                        }
                    }

                    Rectangle
                    {
                        id: translationRect
                        anchors.top: engRect.bottom
                        height: childrenRect.height

                        ListView
                        {
                            x: 10
                            height: childrenRect.height

                            model: ruslist

                            delegate: Text{
                                width: childrens.width - 10
                                text: "∙ " + modelData;
                                wrapMode: Text.WordWrap
                            }
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    onDoubleClicked: dictionary.editRecord(index)
                    onClicked: collectionRecordsTable.currentIndex = index
                }
            }
        }
    }
}

}
