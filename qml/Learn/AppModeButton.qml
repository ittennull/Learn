import QtQuick 2.0

Rectangle
{
	signal clicked()
	property alias text: textElement.text



	width: 200
	height: 50

	border.color: "black"
	border.width: 0
	radius: 20
	gradient: Gradient {
		GradientStop {
			position: 0.00;
			color: "#ffffff";
		}
		GradientStop {
			position: 0.54;
			color: "#e0e62a";
		}
		GradientStop {
			position: 1.00;
			color: "#ffffff";
		}
	}

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
			textElement.color = 'green'
		}

		onExited:
		{
			textElement.color = 'black'
		}

		onPressed: border.width=2
		onReleased: border.width=0

	}
}
