#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionRepeat);
    actionGroup->addAction(ui->actionMirroredRepeat);
    actionGroup->addAction(ui->actionClampToEdge);
    actionGroup->addAction(ui->actionClampToBorder);

    connect(ui->actionRepeat, &QAction::triggered, std::bind(&OpenGLView::setTextureWrapMode, ui->openGLWidget, QOpenGLTexture::Repeat));
    connect(ui->actionMirroredRepeat, &QAction::triggered, std::bind(&OpenGLView::setTextureWrapMode, ui->openGLWidget, QOpenGLTexture::MirroredRepeat));
    connect(ui->actionClampToEdge, &QAction::triggered, std::bind(&OpenGLView::setTextureWrapMode, ui->openGLWidget, QOpenGLTexture::ClampToEdge));
    connect(ui->actionClampToBorder, &QAction::triggered, std::bind(&OpenGLView::setTextureWrapMode, ui->openGLWidget, QOpenGLTexture::ClampToBorder));
}

MainWindow::~MainWindow()
{
    delete ui;
}

