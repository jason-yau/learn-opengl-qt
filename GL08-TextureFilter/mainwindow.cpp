#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMetaEnum>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBoxMinification_currentTextChanged(const QString &text)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QOpenGLTexture::Filter>();
    auto filter = static_cast<QOpenGLTexture::Filter>(metaEnum.keysToValue(text.toStdString().c_str()));
    ui->openGLWidget->setMinificationFilter(filter);
}


void MainWindow::on_comboBoxMagnification_currentTextChanged(const QString &text)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QOpenGLTexture::Filter>();
    auto filter = static_cast<QOpenGLTexture::Filter>(metaEnum.keysToValue(text.toStdString().c_str()));
    ui->openGLWidget->setMagnificationFilter(filter);
}

