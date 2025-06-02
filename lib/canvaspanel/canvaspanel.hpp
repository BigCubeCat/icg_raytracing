#pragma once
#include <QWidget>
#include "canvas.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class CanvasPanel;
}
QT_END_NAMESPACE

class CanvasPanel : public QWidget {
    Q_OBJECT
   private:
    Canvas m_canvas;
    DataModel* m_data;
    Ui::CanvasPanel* m_ui;
    bool m_render_mode = false;

   public:
    explicit CanvasPanel(QWidget* parent, DataModel* model);
    ~CanvasPanel() override;

   private slots:
    void toggle();
};
