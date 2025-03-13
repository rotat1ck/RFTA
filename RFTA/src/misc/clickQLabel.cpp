#include "../../header/misc/clickQLabel.h"

ClickQLabel::ClickQLabel(QWidget* parent, Qt::WindowFlags f) : QLabel(parent) {
    setCursor(Qt::PointingHandCursor);
    setStyleSheet(
        "font-family: 'Inter SemiBold';"
        "font-size: 16px;"
        "line-height: 15px;"
        "color: #7C98CB;"
    );
}

ClickQLabel::~ClickQLabel() {}

void ClickQLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
