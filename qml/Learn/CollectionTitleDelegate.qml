import QtQuick 2.0


Rectangle
{
	id: root
	border.width: 0
	height: 25
	color: ListView.isCurrentItem ? '#4400ee00' : "white"
	radius: 5

	anchors.left: parent.left
	anchors.right: parent.right

	signal collectionTitleClicked(string collectionName)
	signal deleteCollection(int index, string collectionName)

	MouseArea
	{
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: true

		property bool isHovered: false

		onClicked:
		{
			parent.collectionTitleClicked(model.display)
			parent.ListView.view.currentIndex = index
		}

		onEntered: {isHovered = true}
		onExited: {isHovered = false}
	}

	Row
	{
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

				Rectangle
				{
					color: 'red'
					width: parent.width
					height: 10
					anchors.verticalCenter: parent.verticalCenter
					radius: 5
				}

				MouseArea
				{
					anchors.fill: parent
					onClicked: root.deleteCollection(index, model.display)
				}
			}
		}

		Text
		{
			id: text
			height: root.height
			verticalAlignment: Text.AlignVCenter
			text: "<font color=#0000ff><i>" + model.display + "</i></font>"
		}
	}

	states: [
		State {
			name: "mouseOver"
			when: mouseArea.isHovered
			PropertyChanges {target: root; color: '#7700ff00'}
			PropertyChanges {target: text; font.weight: mouseArea.pressed ? Font.Bold : Font.Normal}
		}
	]


}

