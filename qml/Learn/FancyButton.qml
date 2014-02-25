import QtQuick 2.2

Rectangle
{
	signal clicked()
	property alias text: textElement.text

	property color gradientStop2Color: "#5ea63d"
	property color gradientStop2HighlightedColor: '#7fc85f'

	width: 200
	height: 50

	border.color: "black"
	border.width: 1
	radius: 11
 gradient: Gradient {
	 GradientStop {
		 position: 0.060
		 color: "#00000000"
	 }

	 GradientStop {
		 id: gradientStop2
		 position: 1
		 color: gradientStop2Color
	 }
 }
 clip: false
 smooth: true

	Text
	{
		id: textElement
		font.family: "Courier 10 Pitch"
		horizontalAlignment: Text.AlignHCenter
		font.pointSize: 14
		anchors.centerIn: parent
	}

	MouseArea
	{
		hoverEnabled: true
		anchors.fill: parent

		onClicked:
		{
			parent.clicked();
		}

		onEntered:
		{
			gradientStop2.color = gradientStop2HighlightedColor
		}

		onExited:
		{
			gradientStop2.color = gradientStop2Color
		}

		onPressed: border.width=2
		onReleased: border.width=1

	}
}
