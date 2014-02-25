import QtQuick 2.2
import QtQuick.Controls 1.1

Rectangle
{
	id: root

	height: 100
	visible: false

	signal setCollectionName(string collectionName)

	color: '#99000000'

	onVisibleChanged:
	{
		if(visible)
		{
			collectionNameField.text = ""
			collectionNameField.focus = true
		}
	}

	TextField
	{
		id: collectionNameField
		anchors.centerIn: parent
		width: 300
		height: 50

		Keys.onReturnPressed:
		{
			root.visible = false
			root.setCollectionName(text)
		}

		Keys.onEscapePressed:
		{
			root.visible = false
		}
	}
}
