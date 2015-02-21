import QtQuick 2.4
import App 1.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import "Dictionary"
import "CheckMode"
import "Remember"


ColumnLayout
{
    spacing: 10

	width: 1200
	height: 600


	function activateMode(mode)
	{
		app.AppMode = mode

		if(mode == App.Check)
		{
			checkWnd.visible = true
			dictionary.visible = false
			rememberWnd.visible = false
		}
		else if(mode == App.Dictionary)
		{
			dictionary.visible = true
			checkWnd.visible = false
			rememberWnd.visible = false
		}
		else if(mode == App.Remember)
		{
			rememberWnd.visible = true
			checkWnd.visible = false
			dictionary.visible = false
		}
	}

	Component.onCompleted: activateMode(app.AppMode)


	MainPane
	{
		id: mainPane
        Layout.alignment: Qt.AlignCenter
        anchors.top: parent.top
        anchors.topMargin: 10

		onActivateDictionaryMode:
		{
			activateMode(App.Dictionary)
		}

		onActivateCheckMode:
		{
			activateMode(App.Check)
		}

		onActivateRememberMode:
		{
			activateMode(App.Remember)
		}
	}

	Item
	{
        Layout.fillHeight: true
        Layout.fillWidth: true

		Dictionary
		{
			id: dictionary
		}

		CheckWindow
		{
			id: checkWnd
		}

		Remember
		{
			id: rememberWnd
		}
	}

}
