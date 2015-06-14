import QtQuick 2.4
import QtQuick.Controls 1.3
import "../"

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

    function reset(numLast, numOther){
        checkModeCpp.reset(numLast, numOther);
        numErrors=0
    }

	Component.onCompleted: answerField.focus = true
    onVisibleChanged: if (visible) {
                          answerField.focus = true
                          taskSize.triggerReset()
                      }

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
			font.pixelSize: 20
			wrapMode: Text.WordWrap
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
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

            function giveUpAndGoToNestWord(){
                checkModeCpp.next()
                root.next(false)
            }

            Keys.onReturnPressed: giveUpAndGoToNestWord()
            Keys.onEnterPressed: giveUpAndGoToNestWord()
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
            id: statisticText

			anchors.right: parent.right
			horizontalAlignment: Text.AlignRight

			text: "Progress: " + checkModeCpp.CurrentTaskNumber + "/" + checkModeCpp.TotalTaskNumber + "<br>" +
				  "Errors: <font color=#ff0000>" + root.numErrors + "</font>";
		}

        TaskSize{
            id: taskSize
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: parent.right

            onReset: root.reset(numLast, numOther)
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

			font.pixelSize: 25

			text: "<font color=#0000ff size=15>" + checkModeCpp.LastEnglish + "</font>   " +
				  getTranscription() + "<br>" + getListOfRussians();

			wrapMode: Text.WordWrap

			function getListOfRussians()
			{
				var list = checkModeCpp.LastRussianList;
                list = list.map(function(x) { return "∙ " + x;} )
                return list.join("<br>")
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
