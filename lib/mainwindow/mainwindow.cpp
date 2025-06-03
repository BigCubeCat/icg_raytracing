#include "mainwindow.hpp"
#include <qmessagebox.h>
#include <qplaintextedit.h>
#include <qscrollarea.h>

#include "canvaspanel.hpp"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QObject>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_editor(&m_model, &m_parser, nullptr),
      m_canvas_panel(nullptr, &m_model),
      m_fp(&m_model),
      m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);
    m_tab2.addWidget(&m_editor);
    m_ui->tab_2->setLayout(&m_tab2);
    m_tab1.addWidget(&m_canvas_panel);
    m_ui->tab->setLayout(&m_tab1);

    m_ui->toolBar->addActions(m_ui->menuFile->actions());

    m_ui->tab_3->setLayout(m_ui->tab_3_layout);

    connectSlots();
    m_ui->sceneEditor->setPlainText(
        QString("32 32 42\n1\n10 10 10 255 255 0\n"));
    m_ui->lightsEditor->setPlainText(QString(
        "128 255 128\n0.2\n0.1\nfine\n-10 -10 -10\n0 0 0\n0 100\n600 400\n"));
}

void MainWindow::connectSlots() {
    connect(&m_editor, &Editor::new_objects, &m_canvas_panel,
            &CanvasPanel::update_objects);
    connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(m_ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(m_ui->actionSaveAs, &QAction::triggered, this,
            &MainWindow::save_as);
    connect(m_ui->actionAbout, &QAction::triggered, this,
            &MainWindow::show_about);
    connect(m_ui->actionHelp, &QAction::triggered, this,
            &MainWindow::show_help);

    connect(m_ui->lightsEditor, &QPlainTextEdit::textChanged, this,
            &MainWindow::light_changed);
    connect(m_ui->sceneEditor, &QPlainTextEdit::textChanged, this,
            &MainWindow::header_changed);
}

void MainWindow::header_changed() {
    auto text = m_ui->sceneEditor->toPlainText();
    //     m_parser.set_header(text.toStdString());
}

void MainWindow::light_changed() {
    auto text = m_ui->lightsEditor->toPlainText();
    m_parser.set_scene(text.toStdString());
}

void MainWindow::open() {
    m_fp.open();
}

void MainWindow::save() {
    m_fp.save();
}

void MainWindow::save_as() {
    m_fp.save_as();
}

MainWindow::~MainWindow() {
    delete m_ui;
}

void MainWindow::open_file() {}

void MainWindow::show_about() {
    static QString license_text =
        "<h3>End User Soul Agreement</h3>"
        "<p>By using this software, you hereby agree to:</p>"
        "<ul>"
        "<li>Surrender your soul to the Developer</li>"
        "<li>Forfeit all claims to eternal salvation</li>"
        "</ul>"
        "<p><b>This agreement is:</b><br>"
        "✓ Binding for 666 lifetimes<br>"
        "✓ Non-negotiable<br>"
        "✓ Renewable upon death</p>"
        "<p>Thank you for selling your soul!<br>"
        "<i>Team: Devil's Software Division</i></p>";
    QMessageBox::about(this, "About This App", license_text);
}

void MainWindow::show_help() {
    QDialog dialog(this);
    dialog.setWindowTitle("Usage");
    dialog.resize(1000, 600);

    QLabel content_label = QLabel(&dialog);
    static QString content =
        "<div style='{display: 'flex'; flex-direction: 'column', "
        "align-content: 'center'}'><h3>Usage</h3>"
        "<h1>Drag to move node; Left click to add node; Right click to "
        "delete "
        "node</h1>"
        "<img src='assets/screens/1.png' width='900'/>"
        "<h1>Setup figure config</h1>"
        "<img src='assets/screens/2.png' width='900'/>"
        "<h1>Pass figure in [-1, 1] range</h1>"
        "<img src='assets/screens/3.png' width='900'/>"
        "<h1></h1>"
        "<img src='assets/screens/4.png' width='900'/>"
        "<h1></h1>"
        "<img src='assets/screens/5.png' width='900'/>"
        "<h1></h1>"
        "<img src='assets/screens/6.png' width='900'/>"
        "<h1>Change Color! Color on top - nearest edge, color on bottom - "
        "farest edge</h1>"
        "<img src='assets/screens/7.png' width='900'/></div>";
    content_label.setTextFormat(Qt::RichText);
    content_label.setWordWrap(true);
    content_label.setText(content);

    auto* scroll_area = new QScrollArea(&dialog);
    scroll_area->setWidget(&content_label);
    scroll_area->setWidgetResizable(true);
    QVBoxLayout layout(&dialog);
    layout.addWidget(scroll_area);

    dialog.exec();
}
