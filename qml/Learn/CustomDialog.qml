import QtQuick 2.1
import QtQuick.Controls 1.0

Rectangle
{
	id: dialog

	anchors.fill: parent
	color: "#88555555"
	visible: false

	property alias text: dialogText.text
	signal okPressed
	signal cancelPressed


	Rectangle
	{
		anchors.centerIn: parent
		width: 300
		height: 130
		border.width: 2
		radius: 5

		Text
		{
			id: dialogText
			anchors.top: parent.top
			anchors.topMargin: 10
			anchors.horizontalCenter: parent.horizontalCenter
			height: 100
			text: ""
		}

		Row
		{
			anchors.bottom: parent.bottom
			anchors.horizontalCenter: parent.horizontalCenter
			height: 50

			spacing: 30

			Button
			{
				text: "Ok"
				onClicked:
				{
					dialog.okPressed()
					dialog.visible = false
				}
			}

			Button
			{
				text: "Cancel"
				onClicked:
				{
					dialog.cancelPressed()
					dialog.visible = false
				}
			}
		}
	}


}
