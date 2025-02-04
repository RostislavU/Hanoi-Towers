//#
//# Copyright (C) 2018 - 2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import NotifyModule 1.0
import "./base" as Base
import "./menu" as Menu

import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    id: gameWindow
    width: 1240
    height: 720
    title: qsTr("Hanoi Towers")

    Base.Theme{
        id: theme;
    }

    header: Menu.ToolBarPage {
        id: toolBar
        state: stackview.state

        onReturnToMenu: {
            stackview.state = "MainMenu"
        }

        onRestart: {
            gamePage.start(level);
        }
    }


    background:  Background {
        source: "qrc:/textures/res/fogBack.png"
        anchors.fill: parent
        opacity: 0.2
    }

    contentData: SwipeView {
        id: stackview
        state: "MainMenu"
        anchors.fill: parent
        interactive: false

        background: Item {}

        Menu.MainMenu {
            id: mainmenu
            onlineStatus : toolBar.onlineStatus
            onStart: {
                stackview.state = "Game"
                gamePage.launch();

            }

            onLoad: {
                stackview.state = "Game"
                gamePage.load();

            }

            onNewState: {
                stackview.state = state;
            }

            gameState: gamePage.stateData
        }

        Menu.LocalUsersTable {
            id: usersTable
        }

        Menu.World {
            id: worldTable
        }

        Menu.Config {
            id: configPage
        }

        About {
            id: aboutPage
        }

        Game {
            id: gamePage
            stateWidget: gameWindow.header.gameState
        }

        states: [
            State {
                name: "MainMenu"
                PropertyChanges {
                    target: stackview
                    currentIndex: 0
                }
            },
            State {
                name: "UsersTable"
                PropertyChanges {
                    target: stackview
                    currentIndex: 1
                }
            },

            State {
                name: "WorldTable"
                PropertyChanges {
                    target: stackview
                    currentIndex: 2
                }
            },

            State {
                name: "Settings"
                PropertyChanges {
                    target: stackview
                    currentIndex: 3
                }
            },

            State {
                name: "About"
                PropertyChanges {
                    target: stackview
                    currentIndex: 4
                }
            },

            State {
                name: "Game"
                PropertyChanges {
                    target: stackview
                    currentIndex: 5
                }
            }
        ]
    }

    NotificationServiceView {
        anchors.fill: parent;
    }
}
