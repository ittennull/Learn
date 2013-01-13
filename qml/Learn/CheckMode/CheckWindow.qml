import QtQuick 2.0
import QtDesktop 1.0

Rectangle
{
	id: root
	anchors.fill: parent


	property int numErrors: 0

	function next(correctAnswer)
	{
		if(!correctAnswer)
		{
			numErrors++
		}

		answerField.text = ""
	}

	Component.onCompleted: answerField.focus = true
	onVisibleChanged: if(visible) answerField.focus = true

	Rectangle
	{
		id: taskRectangle

		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		height: 250

		Text
		{
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			anchors.bottom: parent.bottom

			text: checkModeCpp.NoMoreData ? "" : checkModeCpp.Russian
			font.family: "Cousine"
			font.pixelSize: 20
			wrapMode: Text.WordWrap
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
		}

		Button
		{
			x: 20
			y: 20
			text: "Reset"
			onClicked: checkModeCpp.reset()
		}
	}


	Rectangle
	{
		id: answerRectangle

		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: taskRectangle.bottom
		height: 50


		TextField
		{
			id: answerField
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			width: 300
			enabled: !checkModeCpp.NoMoreData

			onTextChanged:
			{
				if(checkModeCpp.checkAndGoFurtherIfCorrect(text))
				{
					root.next(true)
				}
			}

			Keys.onPressed:
			{
				if (event.key == Qt.Key_Return || event.key == Qt.Key_Enter)
				{
					checkModeCpp.next()
					root.next(false)
				}
			}
		}
	}


	Rectangle
	{
		id: statisticRectangle

		anchors.right: parent.right
		anchors.top: answerRectangle.bottom
		anchors.bottom: parent.bottom
		anchors.topMargin: 20
		anchors.rightMargin: 20
		width: 150

		Text
		{
			anchors.right: parent.right
			horizontalAlignment: Text.AlignRight

			text: "Progress: " + checkModeCpp.CurrentTaskNumber + "/" + checkModeCpp.TotalTaskNumber + "<br>" +
				  "Errors: <font color=#ff0000>" + root.numErrors + "</font>";
		}
	}


	Rectangle
	{
		id: lastTaskAnswerRectangle

		anchors.left: parent.left
		anchors.right: statisticRectangle.left
		anchors.top: answerRectangle.bottom
		anchors.bottom: parent.bottom
		anchors.leftMargin: 20
		anchors.topMargin: 20

		Text
		{
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			anchors.bottom: parent.bottom

			font.family: "Lato Light"
			font.pixelSize: 25

			text: "<font color=#0000ff size=15>" + checkModeCpp.LastEnglish + "</font>   " +
				  getTranscription() + "<br>" + getListOfRussians();

			wrapMode: Text.WordWrap

			function getListOfRussians()
			{
				var str = "";
				var list = checkModeCpp.LastRussianList;
				for(var i=0; i<list.length; i++)
				{
					str += "∙ " + list[i];
					if(i !== list.legth - 1)
						str += "<br>";
				}
				return str;
			}

			function getTranscription()
			{
				if(checkModeCpp.LastTranscription.length > 0)
				{
					return "[" + checkModeCpp.LastTranscription + "]"
				}
				return ""
			}
		}
	}
}
