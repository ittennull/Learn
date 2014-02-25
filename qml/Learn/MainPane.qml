import QtQuick 2.2
import App 1.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle
{
	id: mainPane

    anchors.top: parent.top
    anchors.bottom: parent.bottom

	property var askCollectionNameDialog: undefined
	property var deleteConfirmDialog: undefined

    signal activateCheckMode
	signal activateRememberMode
	signal activateDictionaryMode


	Column
	{
		id: buttonsColumn

        spacing: 10
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.topMargin: 5

		FancyButton
		{
			text: "Check"
			anchors.horizontalCenter: parent.horizontalCenter
			onClicked: activateCheckMode();
		}

		FancyButton
		{
			text: "Remember"
			anchors.horizontalCenter: parent.horizontalCenter
			onClicked: activateRememberMode();
		}

		FancyButton
		{
			text: "Dictionary"
			anchors.horizontalCenter: parent.horizontalCenter
			onClicked: activateDictionaryMode();
        }

        ListView
        {
            id: collectionsListView
            clip:true

            anchors.left: parent.left
            anchors.right: parent.right
            height: 1000

            model: app.getCollectionsNamesModel()
            delegate: CollectionTitleDelegate
            {
                onCollectionTitleClicked: app.setCollection(collectionName);

                onDeleteCollection:
                {
                    var text = "Really delete <b><i>" + collectionName + "</i></b>?"
                    var onOK = function() {
                        app.deleteCollection(index)
                        collectionsListView.currentIndex = -1
                    }

                    deleteConfirmDialog.show(text, onOK)
                }
            }

            Connections
            {
                target: app
                onNewCollectionCreated: collectionsListView.currentIndex = collectionsListView.count - 1
            }

            header: Rectangle
            {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                height: 40

                visible: app.AppMode == App.Dictionary

                Button
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "New"
                    onClicked: {
                        askCollectionNameDialog.visible = true;
                    }
                }

                Connections
                {
                    target: askCollectionNameDialog
                    onSetCollectionName: app.createCollection(collectionName)
                }

            }
        }
	}

}
