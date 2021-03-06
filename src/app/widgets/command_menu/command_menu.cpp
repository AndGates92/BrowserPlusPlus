/**
 * @copyright
 * @file command_menu.cpp
 * @author Andrea Gianarda
 * @date 23th January 2020
 * @brief Command menu functions
 */

// Qt libraries
#include <QtGui/QPainter>
#include <QtWidgets/QScrollBar>

#include "app/shared/enums.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/widgets/command_menu/command_menu.h"
#include "app/widgets/command_menu/command_menu_model.h"

// Categories
LOGGING_CONTEXT(commandMenuOverall, commandMenu.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuSettings, commandMenu.settings, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuHashTable, commandMenu.hashTable, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuViewport, commandMenu.viewport, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuCursor, commandMenu.cursor, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuScrollBar, commandMenu.scrollBar, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuSelection, commandMenu.selection, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace command_menu {

		namespace {
			/**
			 * @brief command menu title
			 *
			 */
			static const QString commandMenuTitle("Commands");

			/**
			 * @brief Disable auto scroll - user will have to press a key to scroll down
			 *
			 */
			static constexpr bool autoScrollProp = false;

			/**
			 * @brief Disable drag and drop mode
			 *
			 */
			static constexpr QAbstractItemView::DragDropMode dragDropMode = QAbstractItemView::NoDragDrop;

			/**
			 * @brief Disable edit trigger
			 *
			 */
			static constexpr QAbstractItemView::EditTrigger editTrigger = QAbstractItemView::NoEditTriggers;

			/**
			 * @brief Disable drag and drop mode
			 *
			 */
			static constexpr QAbstractItemView::SelectionBehavior selection = QAbstractItemView::SelectItems;

			/**
			 * @brief Maximum number of items to be displayed
			 *
			 */
			static constexpr int maxVisibleItems = 10;

			/**
			 * @brief Extra width with respect to the minium required width
			 *
			 */
			static constexpr int extraRowWidth = 10;

			/**
			 * @brief Extra height with respect to the minium required height
			 *
			 */
			static constexpr int extraRowHeight = 10;

		}

	}

}

app::command_menu::CommandMenu::CommandMenu(QWidget * parent) : QAbstractItemView(parent), menuModel(new app::command_menu::CommandMenuModel(parent)), visibleHeight(0), visibleWidth(parent->width()) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuOverall, "Create command menu");
	this->setProperties();

	this->setModel(this->menuModel);

	// Hide scrollbars
	this->horizontalScrollBar()->setRange(0,0);
	this->verticalScrollBar()->setRange(0,0);
}

app::command_menu::CommandMenu::~CommandMenu() {
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuOverall, "Destoy command menu");

	if (this->menuModel != Q_NULLPTR) {
		delete this->menuModel;
	}
}

void app::command_menu::CommandMenu::setProperties() {

	// Set title
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuSettings, "Set title to command menu: " << app::command_menu::commandMenuTitle);
	this->setWindowTitle(app::command_menu::commandMenuTitle);

	// Edit trigger
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuSettings, "Edit trigger: " << app::command_menu::editTrigger);
	this->setEditTriggers(app::command_menu::editTrigger);

	// Drag and drop mode
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuSettings, "Drag and drop mode: " << app::command_menu::dragDropMode);
	this->setDragDropMode(app::command_menu::dragDropMode);

	// Autoscroll
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuSettings, "Enable autoscroll: " << app::command_menu::autoScrollProp);
	this->setAutoScroll(app::command_menu::autoScrollProp);

	// Selection behaviour
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuSettings, "Selection behaviour: " << app::command_menu::selection);
	this->setSelectionBehavior(app::command_menu::selection);
}

void app::command_menu::CommandMenu::setModel(app::command_menu::CommandMenuModel * model) {
	// Call setModel from the base class
	QAbstractItemView::setModel(model);
}

// Update hash table with elements from the model
void app::command_menu::CommandMenu::updateHashTable() const {

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuHashTable, "Update Hash Table");

	const QFontMetrics fontProperties(this->font());

	const int rowHeight = fontProperties.height() + app::command_menu::extraRowHeight;
//	const int maxWidgetWidth = this->viewport()->width();

	int xItem = 0;
	int yItem = 0;

	int numberItemsInModel = this->model()->rowCount(this->rootIndex());

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuHashTable, "Number of items in model " << numberItemsInModel);

	for (int row = 0; row < numberItemsInModel; row++) {
		const QModelIndex rowIndex(this->model()->index(row, 0, this->rootIndex()));
		const QString text = this->model()->data(rowIndex).toString();
		#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
		const int textWidth = fontProperties.horizontalAdvance(text);
		#else
		const int textWidth = fontProperties.width(text);
		#endif

		const int rowWidth = textWidth + app::command_menu::extraRowWidth;

		// Add element to hash table
		const QRect item = QRect(xItem, yItem, rowWidth, rowHeight);
		itemRect[row] = item;

		LOG_INFO(app::logger::info_level_e::ZERO, commandMenuHashTable, "Adding item " << item << " to the hash table at row " << row);

		yItem += rowHeight;
	}

	if (numberItemsInModel < app::command_menu::maxVisibleItems) {
		this->visibleHeight = yItem;
	} else {
		this->visibleHeight = app::command_menu::maxVisibleItems * rowHeight;
	}

	this->viewport()->update();
}

// Compute rectangle used by an item
QRect app::command_menu::CommandMenu::viewportRectangle(const int row) const {

	this->updateHashTable();

	QRect viewportRect = QRect();
	const QRect currentRect(this->itemRect.value(row));
	if (currentRect.isEmpty()) {
		LOG_INFO(app::logger::info_level_e::ZERO, commandMenuViewport, "Current rectangle is empty");
		viewportRect = currentRect;
	} else {
		// compute viewport coordinates (i.e. account for scrolling)
		int x = currentRect.x() - this->horizontalScrollBar()->value();
		int y = currentRect.y() - this->verticalScrollBar()->value();
		int width = currentRect.width();
		int height = currentRect.height();
		viewportRect = QRect(x, y, width, height);
		LOG_INFO(app::logger::info_level_e::ZERO, commandMenuViewport, "Viewport coordinates: x " << x << " y " << y);
		LOG_INFO(app::logger::info_level_e::ZERO, commandMenuViewport, "Viewport dimension: width " << width << " height " << height);
	}

	return viewportRect;

}

QRect app::command_menu::CommandMenu::visualRect(const QModelIndex & index) const {

	QRect rectOnViewport = QRect();

	if (index.isValid()) {
		rectOnViewport = this->viewportRectangle(index.row());
	}

	return rectOnViewport;
}

void app::command_menu::CommandMenu::scrollTo(const QModelIndex & index, const QAbstractItemView::ScrollHint hint) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuScrollBar, "Scroll hint" << hint << " is ignored");

	const QRect viewportRect(this->viewport()->rect());
	const QRect itemRectInViewportCoord(this->visualRect(index));

	// item boundary
	const int itemTopSide = itemRectInViewportCoord.top();
	const int itemBottomSide = itemRectInViewportCoord.bottom();
	const int itemLeftSide = itemRectInViewportCoord.left();
	const int itemRightSide = itemRectInViewportCoord.right();

	// viewport boundary
	const int viewportTopSide = viewportRect.top();
	const int viewportBottomSide = viewportRect.bottom();
	const int viewportLeftSide = viewportRect.left();
	const int viewportRightSide = viewportRect.right();

	int vValue = 0;
	// scrollbar position + item position - viewport position
	// Move scrollbar to ensure that the model index is visible in the widget
	if (itemTopSide < viewportTopSide) {
		vValue = this->verticalScrollBar()->value() + itemTopSide - viewportTopSide;
	} else if (itemBottomSide < viewportBottomSide) {
		vValue = this->verticalScrollBar()->value() + qMin((itemTopSide - viewportTopSide), (itemBottomSide - viewportBottomSide));
	} else {
		vValue = this->verticalScrollBar()->value();
	}
	this->verticalScrollBar()->setValue(vValue);

	int hValue = 0;
	if (itemLeftSide < viewportLeftSide) {
		hValue = this->horizontalScrollBar()->value() + itemLeftSide - viewportLeftSide;
	} else if (itemRightSide < viewportRightSide) {
		hValue = this->horizontalScrollBar()->value() + qMin((itemLeftSide - viewportLeftSide), (itemRightSide - viewportRightSide));
	} else {
		hValue = this->horizontalScrollBar()->value();
	}
	this->horizontalScrollBar()->setValue(hValue);

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuScrollBar, "Scrollbar values: vertical " << vValue << " horizontal " << hValue);

	this->viewport()->update();
}

QModelIndex app::command_menu::CommandMenu::indexAt(const QPoint &point) const {

	QPoint pointCopy(point);

	// convert coordinates to widget coordinates
	pointCopy.rx() += this->horizontalScrollBar()->value();
	pointCopy.ry() += this->verticalScrollBar()->value();

	this->updateHashTable();

	for (QHash<int, QRect>::const_iterator rectIter = this->itemRect.cbegin(); rectIter != this->itemRect.cend(); rectIter++) {
		// If item contains the requested point, return it
		if (rectIter.value().contains(pointCopy)) {
			return this->model()->index(rectIter.key(), 0, this->rootIndex());
		}
	}

	return QModelIndex();
}

QModelIndex app::command_menu::CommandMenu::moveCursor(const QAbstractItemView::CursorAction cursorAction, const Qt::KeyboardModifiers modifiers) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuCursor, "Cursor action " << cursorAction << " modifiers " << modifiers);

	QModelIndex currIndex = this->currentIndex();

	if (currIndex.isValid()) {
		if (((cursorAction == QAbstractItemView::MoveLeft) && (currIndex.row() > 0)) ||
		    ((cursorAction == QAbstractItemView::MoveRight) && (currIndex.row() < (this->model()->rowCount() - 1)))) {
			const app::shared::sign_e sign = ((cursorAction == QAbstractItemView::MoveLeft) ? app::shared::sign_e::PLUS : app::shared::sign_e::MINUS);
			// Get previous/next item on the list
			const int rowIdx = currIndex.row() + static_cast<int>(sign);
			const int colIdx = currIndex.column();
			QModelIndex parentIdx = currIndex.parent();
			currIndex = this->model()->index(rowIdx, colIdx, parentIdx);
		} else if (((cursorAction == QAbstractItemView::MoveUp)    && (currIndex.row() > 0)) ||
		           ((cursorAction == QAbstractItemView::MoveDown) && (currIndex.row() < (this->model()->rowCount() - 1)))) {

			// Get the index of the item above/below the current item
			QFontMetrics fontProperties(this->font());
			const app::shared::sign_e sign = ((cursorAction == QAbstractItemView::MoveUp) ? app::shared::sign_e::PLUS : app::shared::sign_e::MINUS);
			const int rowHeight = static_cast<int>(sign) * (fontProperties.height() + app::command_menu::extraRowHeight);

			// Get current rectangle
			QRect currentRect(this->viewportRectangle(currIndex.row()));

			// Compute point that is one row above or below the center of the current rectangle
			QPoint point(currentRect.center().x(), (currentRect.center().y() + rowHeight));

			// Move left until the point is beyond the left edge
			while (point.x() >= 0) {
				currIndex = this->indexAt(point);
				// Break if found model item is valid
				if (currIndex.isValid()) {
					break;
				}

				// Move point left by the width of one charcter

				#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
				point.rx() -= fontProperties.horizontalAdvance("n");
				#else
				point.rx() -= fontProperties.width("n");
				#endif
			}

		}

	}

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuCursor, "Current index is set at row " << currIndex.row() << " and column " << currIndex.column());

	return currIndex;
}

int app::command_menu::CommandMenu::horizontalOffset() const {
	const int offset = this->horizontalScrollBar()->value();
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuScrollBar, "Horizontal scrollbar offset " << offset);
	return offset;
}

int app::command_menu::CommandMenu::verticalOffset() const {
	const int offset = this->verticalScrollBar()->value();
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuScrollBar, "Vertical scrollbar offset " << offset);
	return offset;
}

bool app::command_menu::CommandMenu::isIndexHidden(const QModelIndex & index) const {
	const bool isHidden = false;

	const int rowIdx = index.row();
	const int colIdx = index.column();

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuCursor, "Index iat row " << rowIdx << " and column " << colIdx << " has hidden attribute set to " << isHidden);

	return isHidden;
}

void app::command_menu::CommandMenu::setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags command) {
	this->updateHashTable();

	// Transalte rectangle into the visible region
	QRect visibleRectangle(rect.translated(this->horizontalScrollBar()->value(), this->verticalScrollBar()->value()));
	// Make width and height positive
	visibleRectangle = visibleRectangle.normalized();

	// Initialize top and bottom row
	// To simplify the logic, initialize them to a value they will never take.
	const int topRowSelInitValue = this->model()->rowCount();
	const int bottomRowSelInitValue = -1;

	int topRowSel = topRowSelInitValue;
	int bottomRowSel = bottomRowSelInitValue;

	for (QHash<int, QRect>::const_iterator rectIter = this->itemRect.cbegin(); rectIter != this->itemRect.cend(); rectIter++) {
		if (rectIter.value().intersects(visibleRectangle)) {
			int keyIter = rectIter.key();
			if (topRowSel >= keyIter) {
				topRowSel = keyIter;
			}

			if (bottomRowSel <= keyIter) {
				bottomRowSel = keyIter;
			}
		}
	}

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuSelection, "Selection boundaries: top row " << topRowSel << " bottom row " << bottomRowSel);

	QModelIndex topLeftModel = QModelIndex();
	QModelIndex bottomRightModel = QModelIndex();
	if ((topRowSel != topRowSelInitValue) && (bottomRowSel != bottomRowSelInitValue)) {
		topLeftModel = this->model()->index(topRowSel, 0, this->rootIndex());
		bottomRightModel = this->model()->index(bottomRowSel, 0, this->rootIndex());
	}
	QItemSelection itemSel(topLeftModel, bottomRightModel);
	this->selectionModel()->select(itemSel, command);

}

QRegion app::command_menu::CommandMenu::visualRegionForSelection(const QItemSelection & selection) const {

	QRegion region = QRegion();

	// Iterate through all selected items and add them to region
	foreach (const QItemSelectionRange & selectionRange, selection) {
		for (int column = selectionRange.left(); column < selectionRange.right(); column++) {
			for (int row = selectionRange.top(); row < selectionRange.bottom(); row++) {
				QModelIndex currentIndex(this->model()->index(row, column, this->rootIndex()));
				region = region.united(this->visualRect(currentIndex));
			}
		}
	}

	return region;
}

void app::command_menu::CommandMenu::scrollContentsBy(const int x, const int y) {
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuScrollBar, "Set dirty region to point (" << x << ", " << y << ")");
	this->scrollDirtyRegion(x,y);
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuScrollBar, "Scroll to point (" << x << ", " << y << ")");
	this->viewport()->scroll(x,y);
}

void app::command_menu::CommandMenu::paintEvent(QPaintEvent * event) {
	event->accept();
	QPainter rectPainter(this->viewport());

	int numberModelChildren = this->model()->rowCount();

	for (int row = 0; row < numberModelChildren; row++) {
		QRect rowRect(this->viewportRectangle(row));

		// if rectangle is inside the viewport
		if ((rowRect.isValid()) && (rowRect.bottom() >= 0) && (rowRect.y() <= this->viewport()->height())) {
			QStyleOptionViewItem optionRect(this->viewOptions());
			optionRect.rect = rowRect;
			QModelIndex rowIndex(this->model()->index(row, 0, this->rootIndex()));
			if (this->selectionModel()->isSelected(rowIndex)) {
				optionRect.state |= QStyle::State_Selected;
			}

			if (this->currentIndex() == rowIndex) {
				optionRect.state |= QStyle::State_HasFocus;
			}

			this->itemDelegate()->paint(&rectPainter, optionRect, rowIndex);
			this->paintRectOutline(&rectPainter, rowRect);
		}
	}
}

void app::command_menu::CommandMenu::paintRectOutline(QPainter * painter, const QRect & rectangle) {

	painter->save();
	// Draw a line after the rectangle
	painter->drawLine(rectangle.bottomLeft(), rectangle.bottomRight());
	painter->restore();
}

void app::command_menu::CommandMenu::resizeEvent(QResizeEvent * event) {
	event->accept();

	this->updateHashTable();

	// Calculate scrollbar range
	this->updateScrollbars();
}

void app::command_menu::CommandMenu::updateScrollbars() {

	QFontMetrics fontProperties(this->font());

	const int viewportWidth = this->viewport()->width();
	#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
	this->horizontalScrollBar()->setSingleStep(fontProperties.horizontalAdvance("n"));
	#else
	this->horizontalScrollBar()->setSingleStep(fontProperties.width("n"));
	#endif
	this->horizontalScrollBar()->setPageStep(viewportWidth);
	this->horizontalScrollBar()->setRange(0, qMax(0, (this->visibleWidth - viewportWidth)));

	const int rowHeight = fontProperties.height() + app::command_menu::extraRowHeight;
	const int viewportHeight = this->viewport()->height();
	this->horizontalScrollBar()->setSingleStep(rowHeight);
	this->horizontalScrollBar()->setPageStep(viewportHeight);
	this->horizontalScrollBar()->setRange(0, qMax(0, (this->visibleHeight - viewportHeight)));
}

void app::command_menu::CommandMenu::mousePressEvent(QMouseEvent * event) {
	event->accept();
	QAbstractItemView::mousePressEvent(event);
	this->setCurrentIndex(this->indexAt(event->pos()));
}
