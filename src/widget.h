#ifndef WIDGET_H
#define WIDGET_H

#define MIN_ZOOM 0.1
#define MAX_ZOOM 10.0

#include <QWidget>
#include <QOpenGLWidget>
#include <QVector>
#include <QPainter>
#include <QTabletEvent>
#include <QUndoStack>
#include <QScrollArea>
#include <QMutex>

#include <QTime>
#include <QTimer>

#include "tabletapplication.h"
#include "mrdoc.h"
#include "document.h"

class Widget : public QWidget
// class Widget : public QOpenGLWidget
{
  Q_OBJECT
public:
  explicit Widget(QWidget *parent = 0);

  enum class tool
  {
    NONE,
    PEN,
    RULER,
    CIRCLE,
    ERASER,
    SELECT,
    HAND
  };
  enum class state
  {
    IDLE,
    DRAWING,
    RULING,
    CIRCLING,
    SELECTING,
    SELECTED,
    MOVING_SELECTION,
    RESIZING_SELECTION,
    ROTATING_SELECTION
  };

  static constexpr qreal veryFinePenWidth = 0.42;
  static constexpr qreal finePenWidth = 0.85;
  static constexpr qreal mediumPenWidth = 1.41;
  static constexpr qreal thickPenWidth = 2.26;
  static constexpr qreal veryThickPenWidth = 5.67;

  void setCurrentTool(tool toolID);
  tool getCurrentTool()
  {
    return currentTool;
  }

  void setCurrentPenWidth(qreal penWidth);

  qreal getCurrentPenWidth()
  {
    return currentPenWidth;
  }

  void mouseAndTabletEvent(QPointF mousePos, Qt::MouseButton button, Qt::MouseButtons buttons, Qt::KeyboardModifiers keyboardModifiers,
                           QTabletEvent::PointerType pointerType, QEvent::Type eventType, qreal pressure, bool tabletEvent);

  /**
   * @brief updateAllPageBuffers
   * @todo use std::unique_lock
   */
  void updateAllPageBuffers();
  void updateImageBuffer(int buffNum);
  void updateBuffer(int i);
  void updateBufferRegion(int buffNum, QRectF const &clipRect);
  void drawOnBuffer(bool last = false);
  int getPageFromMousePos(QPointF mousePos);
  QPointF getPagePosFromMousePos(QPointF mousePos, int pageNum);
  QPointF getAbsolutePagePosFromMousePos(QPointF mousePos);
  QRect getWidgetGeometry();
  int getCurrentPage();

  void setCurrentState(state newState);
  state getCurrentState();

  void setCurrentColor(QColor newColor);
  QColor getCurrentColor();

  void setDocument(const MrDoc::Document &newDocument);
  void letGoSelection();

  void newFile();
  //    void openFile();

  void zoomIn();
  void zoomOut();
  void zoomTo(qreal newZoom);
  void zoomFitWidth();
  void zoomFitHeight();

  void rotateSelection(qreal angle);

  MrDoc::Document currentDocument;
  QVector<QPixmap> pageBuffer;
  QVector<QImage> pageImageBuffer;
  QMutex pageImageBufferMutex;

  QColor currentColor;
  qreal currentPenWidth;

  qreal m_currentAngle;

  void setCurrentPattern(QVector<qreal> newPattern);
  QVector<qreal> getCurrentPattern();

  MrDoc::Selection currentSelection;
  MrDoc::Selection &clipboard = static_cast<TabletApplication *>(qApp)->clipboard;

  int selectingOnPage;

  QScrollArea *scrollArea;

  QUndoStack undoStack;

  qreal zoom;

private:
  QTime timer;

  QTimer *updateTimer;
  QTimer *updateDirtyTimer;

  qreal count;

  void scrollDocumentToPageNum(int pageNum);

  QVector<qreal> currentPattern = MrDoc::solidLinePattern;

  QCursor penCursor;
  QCursor circleCursor;
  QCursor rulerCursor;
  QCursor eraserCursor;

  MrDoc::Stroke currentStroke;
  QRect currentUpdateRect;

  state currentState;

  bool penDown = false;
  int drawingOnPage;

  tool currentTool;
  tool previousTool;
  bool realEraser;

  qreal currentDashOffset;

  qreal minWidthMultiplier = 0.0;
  qreal maxWidthMultiplier = 1.25;

  QPointF currentCOSPos;
  QPointF firstMousePos;
  QPointF previousMousePos;
  QPointF previousPagePos;
  MrDoc::Selection::GrabZone m_grabZone = MrDoc::Selection::GrabZone::None;

  void startDrawing(QPointF mousePos, qreal pressure);
  void continueDrawing(QPointF mousePos, qreal pressure);
  void stopDrawing(QPointF mousePos, qreal pressure);

  void startRuling(QPointF mousePos);
  void continueRuling(QPointF mousePos);
  void stopRuling(QPointF mousePos);

  void startCircling(QPointF mousePos);
  void continueCircling(QPointF mousePos);
  void stopCircling(QPointF mousePos);

  void startSelecting(QPointF mousePos);
  void continueSelecting(QPointF mousePos);
  void stopSelecting(QPointF mousePos);

  void startMovingSelection(QPointF mousePos);
  void continueMovingSelection(QPointF mousePos);

  void startRotatingSelection(QPointF mousePos);
  void continueRotatingSelection(QPointF mousePos);
  void stopRotatingSelection(QPointF mousePos);

  void startResizingSelection(QPointF mousePos, MrDoc::Selection::GrabZone grabZone);
  void continueResizingSelection(QPointF mousePos);
  void stopResizingSelection(QPointF mousePos);

  void setPreviousTool();

  void erase(QPointF mousePos, bool invertEraser = false);

private slots:
  void updateAllDirtyBuffers();

  void undo();
  void redo();

  void selectAll();
  void copy();
  void paste();
  void cut();

  void pageFirst();
  void pageLast();
  void pageUp();
  void pageDown();

  void pageAddBefore();
  void pageAddAfter();
  void pageAddBeginning();
  void pageAddEnd();

  void pageRemove();

  void veryFine();
  void fine();
  void medium();
  void thick();
  void veryThick();

  void solidPattern();
  void dashPattern();
  void dashDotPattern();
  void dotPattern();

  void updateWhileDrawing();

signals:
  void pen();
  void ruler();
  void circle();
  void eraser();
  void select();
  void hand();

  void updateGUI();

  void modified();

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

  void tabletEvent(QTabletEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // WIDGET_H
