import QtQuick 2.1
import App 1.0
import QtQuick.Controls 1.0
import "Dictionary"
import "CheckMode"
import "Remember"


Rectangle
{
	width: 1200
	height: 600
	gradient: Gradient {
		GradientStop {
			position: 0.00;
			color: "#ffffff";
		}
		GradientStop {
			position: 0.49;
			color: "#a6a6a2";
		}
		GradientStop {
			position: 1.00;
			color: "#ffffff";
		}
	}

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
		anchors.left: parent.left
		width: parent.width * 0.25
		askCollectionNameDialog: askCollectionNameDialog
		deleteConfirmDialog: deleteConfirmDialog

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
		anchors.left: mainPane.right
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom


		Dictionary
		{
			id: dictionary
			deleteConfirmDialog: deleteConfirmDialog
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

	AskCollectionNameDialog
	{
		id: askCollectionNameDialog

		anchors.left: parent.left
		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter
	}

	CustomDialog
	{
		id: deleteConfirmDialog
		anchors.centerIn: parent

		property var onOk: null

		function show(text, onOk)
		{
			this.text = text
			this.onOk = onOk
			visible = true
		}

		onOkPressed: { onOk(); onOk=null;}
	}

//	MouseArea {
//		anchors.fill: parent
//		onClicked: {
//			var a = app.RusListModel
//			console.log(a.length)
//		}
//	}


}
