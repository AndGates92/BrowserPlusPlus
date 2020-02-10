#ifndef COMMAND_MENU_H
#define COMMAND_MENU_H

/**
 * @copyright
 * @file command_menu.h
 * @author Andrea Gianarda
 * @date 23th of January 2020
 * @brief Command Menu file
*/

#include <qt5/QtWidgets/QAbstractItemView>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QRect>
#include <qt5/QtCore/QModelIndex>
#include <qt5/QtGui/QRegion>
#include <qt5/QtGui/QResizeEvent>
#include <qt5/QtGui/QMouseEvent>

#include "command_menu_model.h"

/** @defgroup CommandMenuGroup Command Menu Doxygen Group
 *  Command Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(commandMenuOverall)
Q_DECLARE_LOGGING_CATEGORY(commandMenuSettings)
Q_DECLARE_LOGGING_CATEGORY(commandMenuHashTable)
Q_DECLARE_LOGGING_CATEGORY(commandMenuViewport)
Q_DECLARE_LOGGING_CATEGORY(commandMenuCursor)
Q_DECLARE_LOGGING_CATEGORY(commandMenuScrollBar)
Q_DECLARE_LOGGING_CATEGORY(commandMenuSelection)

namespace command_menu {

	namespace {
		/**
		 * @brief command menu title
		 *
		 */
		const QString commandMenuTitle("Commands");

		/**
		 * @brief Disable auto scroll - user will have to press a key to scroll down
		 *
		 */
		const bool autoScrollProp = false;

		/**
		 * @brief Disable drag and drop mode
		 *
		 */
		const QAbstractItemView::DragDropMode dragDropMode = QAbstractItemView::NoDragDrop;

		/**
		 * @brief Disable edit trigger
		 *
		 */
		const QAbstractItemView::EditTrigger editTrigger = QAbstractItemView::NoEditTriggers;

		/**
		 * @brief Disable drag and drop mode
		 *
		 */
		const QAbstractItemView::SelectionBehavior selection = QAbstractItemView::SelectItems;

		/**
		 * @brief Maximum number of items to be displayed
		 *
		 */
		const int maxVisibleItems = 10;

		/**
		 * @brief Extra width with respect to the minium required width
		 *
		 */
		const int extraRowWidth = 10;

		/**
		 * @brief Extra height with respect to the minium required height
		 *
		 */
		const int extraRowHeight = 10;

	}

	/**
	 * @brief CommandMenu class
	 *
	 */
	class CommandMenu : public QAbstractItemView {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit CommandMenu(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent window
			 *
			 * Command menu constructor
			 */
			explicit CommandMenu(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~CommandMenu()
			 *
			 * Command menu destructor
			 */
			~CommandMenu();

		protected:

		private:
			/**
			 * @brief command menu model
			 *
			 */
			command_menu_model::CommandMenuModel * menuModel;

			/**
			 * @brief Height to be displayed without the need of a scrollbar
			 *
			 */
			mutable int visibleHeight;

			/**
			 * @brief Width to be displayed without the need of a scrollbar
			 *
			 */
			mutable int visibleWidth;

			/**
			 * @brief Hash of rectangles of every single row
			 *
			 */
			mutable QHash<int, QRect> itemRect;

			/**
			 * @brief Function: void setProperties()
			 *
			 * Set properties of the command menu
			 */
			void setProperties();

			/**
			 * @brief Function: void setModel(command_menu_model::CommandMenuModel * model)
			 *
			 * \param model: model to set for the command menu
			 *
			 * Set command menu model
			 */
			void setModel(command_menu_model::CommandMenuModel * model);

			/**
			 * @brief Function: QRect visualRect(const QModelIndex & index) const
			 *
			 * \return rectangle where item at index is
			 *
			 * This function returns the rectangle occupied by item at inde 
			 */
			QRect visualRect(const QModelIndex & index) const;

			/**
:			 * @brief Function: void scrollTo(const QModelIndex & index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible)
			 *
			 * \param index: is the index of the model
			 * \param hint: view will position an item accoridng to the value of hint

			 * Scroll the view if required to ensure that element at item index is visible
			 */
			void scrollTo(const QModelIndex & index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible);

			/**
			 * @brief Function: QModelIndex indexAt(const QPoint & point) const
			 *
			 * \param point: points to search model index for. Its coordinates are in viewport coordinate system

			 * \return model index at point point
			 *
			 * This function returns the model index of item at point point
			 */
			QModelIndex indexAt(const QPoint & point) const;

			/**
			 * @brief Function: QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
			 *
			 * \param cursorAction: action execute by the cursor
			 * \param modifiers: enumeration with the keyboard modifier supported by Qt
			 *
			 * \return model index pointing to the next object in the view based on the input arguments
			 *
			 * This function returns the model index pointing to the next object in the view based on the input arguments
			 */
			QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

			/**
			 * @brief Function: int horizontalOffset() const
			 *
			 * \return the horizontal offset of the view
			 *
			 * This function returns the horizontal offset of the view
			 */
			int horizontalOffset() const;

			/**
			 * @brief Function: int verticalOffset() const
			 *
			 * \return the vertical offset of the view
			 *
			 * This function returns the vertical offset of the view
			 */
			int verticalOffset() const;

			/**
			 * @brief Function: bool isIndexHidden(const QModelIndex & index) const
			 *
			 * \param index: model index to check whether is idle while the code is running
			 *
			 * \return if an item is hidden
			 *
			 * This function returns whether an item is hidden (true) or visible (false)
			 */
			bool isIndexHidden(const QModelIndex & index) const;

			/**
			 * @brief Function: void setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags command)
			 *
			 * \param rect: rectangle limiting th earea where flags are applied
			 * \param command: flags to be used 
			 *
			 * apply flags to item inside of touched by rectangle rect
			 */
			void setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags command);

			/**
			 * @brief Function: QRegion visualRegionForSelection(const QItemSelection & selection) const
			 *
			 * \param selection: items to search for
			 *
			 * \return region that encapsulates all items in selection selection
			 *
			 * This function returns from the viewport of the items
			 */
			QRegion visualRegionForSelection(const QItemSelection & selection) const;

			/**
			 * @brief Function: void updateHashTable() const
			 *
			 * This function updates the hash table where all rows are stored
			 */
			void updateHashTable() const;

			/**
			 * @brief Function: QRect viewportRectangle(int row) const
			 *
			 * \param row: items to search for
			 *
			 * \return the rectangle at row row whose coordinates account for the scrolling
			 *
			 * This function returns the rectangle at row row whose coordinates account for the scrolling
			 */
			QRect viewportRectangle(int row) const;

			/**
			 * @brief Function: void scrollContentsBy(int x, int y) const
			 *
			 * \param x: scrollbar movement along x axis
			 * \param y: scrollbar movement along y axis
			 *
			 * This function updates the viewport content as a consequence of scrolling
			 */
			void scrollContentsBy(int x, int y);

			/**
			 * @brief Function: void paintEvent(QPaintEvent * event)
			 *
			 * \param event: paint event
			 *
			 * This function paints all the rectangles
			 */
			void paintEvent(QPaintEvent * event);

			/**
			 * @brief Function: void resizeEvent(QResizeEvent * event)
			 *
			 * \param event: resize event
			 *
			 * This function is called when the widget is resized
			 */
			void resizeEvent(QResizeEvent * event);

			/**
			 * @brief Function: void mousePressEvent(QMouseEvent * event)
			 *
			 * \param event: mouse event
			 *
			 * This function is called when a mouse button is pressed
			 */
			void mousePressEvent(QMouseEvent * event);

			/**
			 * @brief Function: void paintRectOutline(QPainter * painter, const QRect & rectangle)
			 *
			 * \param painter: pointer to QPainter object
			 * \param rectangle: rectangle to paint outline
			 *
			 * This function paints the rectangle outline
			 */
			void paintRectOutline(QPainter * painter, const QRect & rectangle);

			/**
			 * @brief Function: void updateScrollbars()
			 *
			 * This function updates the properties and its steps
			 */
			void updateScrollbars();

	};

}
/** @} */ // End of CommandMenuGroup group

#endif // COMMAND_MENU_H
