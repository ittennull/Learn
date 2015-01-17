import QtQuick 2.4
import QtQuick.Controls 1.3

Rectangle
{
	id: root
	anchors.fill: parent

	onVisibleChanged: focus=visible

	Rectangle
	{
		id: taskRectangle

		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		height: 250

		Text
		{
			anchors.centerIn: parent
            font.pointSize: 20
            text: (rememberModeCpp.NoMoreData ? "\\(-_-)/" : rememberModeCpp.English)
		}

		Button
		{
			x: 20
			y: 20
			text: "Reset"
			onClicked: rememberModeCpp.reset()
		}
	}

	Rectangle
	{
		id: statisticRectangle

		anchors.right: parent.right
		anchors.top: taskRectangle.bottom
		anchors.bottom: parent.bottom
		anchors.topMargin: 20
		anchors.rightMargin: 20
		width: 150

		Text
		{
			anchors.right: parent.right
			horizontalAlignment: Text.AlignRight

			text: "Progress: " + rememberModeCpp.CurrentTaskNumber + "/" + rememberModeCpp.TotalTaskNumber
		}
	}


	Rectangle
	{
		id: lastTaskAnswerRectangle

		anchors.left: parent.left
		anchors.right: statisticRectangle.left
		anchors.top: taskRectangle.bottom
		anchors.bottom: parent.bottom
		anchors.leftMargin: 20
		anchors.topMargin: 20

		Text
		{
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: parent.top
			anchors.bottom: parent.bottom

			text: "<font color=#0000ff size=15>" + rememberModeCpp.LastEnglish + "</font>   " +
				  getTranscription() + "<br>" + getListOfRussians();

			wrapMode: Text.WordWrap

            function getListOfRussians()
            {
                var list = rememberModeCpp.LastRussianList;
                list = list.map(function(x) { return "∙ " + x;} )
                return list.join("<br>")
            }

			function getTranscription()
			{
				if(rememberModeCpp.LastTranscription.length > 0)
				{
					return "[" + rememberModeCpp.LastTranscription + "]"
				}
				return ""
			}
		}
	}

	Keys.onPressed:
	{
		if (event.key == Qt.Key_Space || event.key == Qt.Key_Right || event.key == Qt.Key_Return || event.key == Qt.Key_Enter)
		{
			if(!rememberModeCpp.NoMoreData)
				rememberModeCpp.next()

		}
		else if(event.key == Qt.Key_Left)
		{
			rememberModeCpp.prev()
		}
	}
}
