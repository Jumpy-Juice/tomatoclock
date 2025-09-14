#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include "displayclockbase.h"
#include <cstdint>

namespace lon {
namespace clock_window {
class ProgressWidget : public DisplayClockBase {
    Q_OBJECT
private:
    QGraphicsItem* current_progress_;

    QGraphicsScene* scene_;
    QGraphicsView* view_;

    QLabel* time_label_;

    QPen* pen_;

    ClockTime const* total_time_;

    QHBoxLayout* layout_;
    QHBoxLayout* view_layout_;

    uint16_t height_;
    uint16_t width_;

public:
    explicit ProgressWidget(QWidget* parent = nullptr);

    explicit ProgressWidget(uint16_t height, uint16_t width, QWidget* parent = nullptr);

    ~ProgressWidget();

    void updateTimeDisplay(TimerStatus const* timer_status) override;
signals:

public slots:

    void progressChanged(uint16_t current, uint16_t total) {}
};
}  // namespace clock_window
}  // namespace lon

#endif  // PROGRESSWIDGET_H
