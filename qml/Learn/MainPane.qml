import QtQuick 2.4
import App 1.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle
{
	id: mainPane

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    signal activateCheckMode
	signal activateRememberMode
	signal activateDictionaryMode


	Column
	{
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
	}
}
