import QtQuick 2.4
import App 1.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

RowLayout
{
	id: mainPane
    spacing: 20

    signal activateCheckMode
	signal activateRememberMode
	signal activateDictionaryMode

    FancyButton
    {
        text: "Check"
        onClicked: activateCheckMode();
        isActive: checkWnd.visible;
    }

    FancyButton
    {
        text: "Remember"
        onClicked: activateRememberMode();
        isActive: rememberWnd.visible;
    }

    FancyButton
    {
        text: "Dictionary"
        onClicked: activateDictionaryMode();
        isActive: dictionary.visible;
    }
}

