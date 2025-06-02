#include "canvaspanel.hpp"

#include <qobject.h>
#include <qwidget.h>
#include "canvas.hpp"

#include <QColorDialog>

#include "ui_canvaspanel.h"

CanvasPanel::CanvasPanel(QWidget* parent, DataModel* model)
    : QWidget(parent),
      m_canvas(this, model),
      m_data(model),
      m_ui(new Ui::CanvasPanel) {
    m_ui->setupUi(this);
    m_ui->layout->addWidget(&m_canvas);

    connect(m_ui->toggleModeButton, &QPushButton::clicked, this,
            &CanvasPanel::toggle);
}

CanvasPanel::~CanvasPanel() {
    delete m_ui;
}

void CanvasPanel::toggle() {
    m_render_mode = !m_render_mode;
    if (m_render_mode) {
        m_ui->toggleModeButton->setText(tr("edit"));
    } else {
        m_ui->toggleModeButton->setText(tr("render"));
    }
}
