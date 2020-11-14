/**
 * @copyright
 * @file overlayed_widget.cpp
 * @author Andrea Gianarda
 * @date 19th of June 2020
 * @brief Overlayed widget functions
*/

// Qt libraries
#include <QtGui/QPainter>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOption>

#include "base/overlay/include/overlayed_widget.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"

// Categories
LOGGING_CONTEXT(overlayedWidgetOverall, overlayedWidget.overall, TYPE_LEVEL, INFO_VERBOSITY)

overlayed_widget::OverlayedWidget::OverlayedWidget(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags) {

	LOG_INFO(logger::info_level_e::ZERO, overlayedWidgetOverall,  "Overlayed widget constructor");

}

overlayed_widget::OverlayedWidget::~OverlayedWidget() {
	LOG_INFO(logger::info_level_e::ZERO, overlayedWidgetOverall,  "Overlayed widget destructor");
}

void overlayed_widget::OverlayedWidget::paintEvent(QPaintEvent * event) {
	QStyleOption styleOption;
	styleOption.init(this);

	QPainter painter(this);
	QStyle::PrimitiveElement primitiveElement = QStyle::PE_Widget;
	this->style()->drawPrimitive(primitiveElement, &styleOption, &painter, this);

	QWidget::paintEvent(event);
}

void overlayed_widget::OverlayedWidget::setGeometry(const QRect & rect) {

	QWidget::setGeometry(rect);

	// Widgets should occupy the fill size of the popup container, hence pass the new geometry down to them
	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			widget->setGeometry(rect);
			widget->updateGeometry();
		}
	}

}
