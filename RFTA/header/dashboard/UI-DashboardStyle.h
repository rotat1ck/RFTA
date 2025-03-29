#pragma once
#ifndef DASHBOARDSTYLE_H
#define DASHBOARDSTYLE_H

QString activeStartButtonStyle =
    "background: rgba(204, 218, 185, 1);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(50, 50, 50, 1);"
;

QString activeStopButtonStyle =
    "background: rgba(255, 217, 217, 1);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(50, 50, 50, 1);"
;

QString activeEditButtonStyle =
    "background: rgba(217, 217, 217, 1);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(50, 50, 50, 1);"
;

QString inactiveStartButtonStyle =
    "background: rgba(204, 218, 185, 128);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(50, 50, 50, 128);"
;

QString inactiveStopButtonStyle =
    "background: rgba(255, 217, 217, 128);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(50, 50, 50, 128);"
;

QString consoleTextStyle =
    "font-family: 'Inter SemiBold';"
    "font-size: 15px;"
    "line-height: 17px;"
    "color: #CDCDCD;"
;

QString scrollAreaStyle =
    "QScrollArea { border: none; }"
    "QScrollBar:vertical { border: none; background: #D9D9D9; width: 10px; }"
    "QScrollBar::handle:vertical { background: #707070; min-height: 20px; }"
;

#endif // DASHBOARDSTYLE_H
