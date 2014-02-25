import QtQuick 2.2


Rectangle
{
	id: root
	border.width: 1
	height: 25
	color: ListView.isCurrentItem ? "#5ea63d" : "white"
	radius: 6
	smooth: true

	anchors.left: parent.left
	anchors.right: parent.right

	signal collectionTitleClicked(string collectionName)
	signal deleteCollection(int index, string collectionName)

    property string collectionName: model.display

	MouseArea
	{
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		property bool isHovered: false

		onClicked:
		{
            parent.collectionTitleClicked(collectionName)
			parent.ListView.view.currentIndex = index
		}

		onEntered: {isHovered = true}
		onExited: {isHovered = false}
	}

	Row
	{
		x:5

		Rectangle
		{
			width: 30
			height: root.height
			color: 'transparent'

			Text
			{
				visible: !mouseArea.isHovered
				text: index + ") "
				height: root.height
				verticalAlignment: Text.AlignVCenter
			}

			Rectangle
			{
				width: 20
				height: parent.height
				visible: mouseArea.isHovered
				color: 'transparent'

				Rectangle
				{
					color: 'red'
					width: parent.width
					height: 10
					anchors.verticalCenter: parent.verticalCenter
					radius: 3
				}

				MouseArea
				{
					anchors.fill: parent
                    onClicked: root.deleteCollection(index, collectionName)
				}
			}
		}

		Text
		{
			id: text
			height: root.height
			verticalAlignment: Text.AlignVCenter
            text: "<font color=#0000ff><i>" + collectionName + "</i></font>"
		}
	}

	states: [
		State {
			name: "mouseOver"
			when: mouseArea.isHovered
			PropertyChanges {target: root; color: "#775ea63d"}
			PropertyChanges {target: text; font.weight: mouseArea.pressed ? Font.Bold : Font.Normal}
		}
	]


}

