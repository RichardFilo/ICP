#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
        ui->setupUi(this);

        obj_block_schema = new Block_schema();

        QString path = QString::fromStdString(obj_block_schema->generate_sim_code());

        flag_move_button = true;
        flag_line_button = flag_LMB = false;

        obj_scene = new QGraphicsScene(this); // vytvorenie scény (plátna)
        ui->graphicsView->setScene(obj_scene); // určenie plátna na vykreslenie
        ui->graphicsView->viewport()->installEventFilter(this); // zachytávanie udalostí
        ui->graphicsView->setMouseTracking(true); // sledovanie myši

        //obj_scene->addPixmap(QPixmap(":/block_images/images/sum_block.png"));
        obj_scene->addText(path);
    }

MainWindow::~MainWindow() {
    delete ui;
    delete obj_block_schema;
}

void MainWindow::ViewZoom(QGraphicsView* param_view, double param_factor) {
    param_view->scale(param_factor, param_factor);
    param_view->centerOn(var_mouse_scene_position);
    QPointF var_viewport_position_difference = var_mouse_viewport_position - QPointF(param_view->viewport()->width() / 2.0, param_view->viewport()->height() / 2.0);
    QPointF var_center = param_view->mapFromScene(var_mouse_scene_position) - var_viewport_position_difference;
    param_view->centerOn(param_view->mapToScene(var_center.toPoint()));
}

bool MainWindow::eventFilter(QObject *param_object, QEvent *param_event) {
    // sníma pohyb kolečkom na myši
    // ak je zároveň stisknutá kĺavesa CTRL, pohyb kolečkom môže približovať odďaľovať pohľad
    if (param_event->type() == QEvent::Wheel) {
        QWheelEvent* var_wheel_event = static_cast<QWheelEvent*>(param_event); // pretypovanie udalosti na požadovaný tvar (pre prístup k parametrom)
        if (QApplication::keyboardModifiers() == Qt::ControlModifier) { // pozrie či bol stlačený Ctrl
            double var_angle = var_wheel_event->angleDelta().y();
            double var_factor = qPow(1.001, var_angle); // 1.001 je cistlivosť zoomovania
            ViewZoom(ui->graphicsView, var_factor);
            return true;
        }
    }
    // sníma pohyb myši a priebežne si ukladá jej pozíciu
    // využitie pre zoomovanie na pozíciu myši
    else if (param_event->type() == QEvent::MouseMove) {
        QMouseEvent* var_mouse_event = static_cast<QMouseEvent*>(param_event); // pretypovanie udalosti na požadovaný tvar (pre prístup k parametrom)
        QPointF var_difference = var_mouse_viewport_position - var_mouse_event->pos();
        if (qAbs(var_difference.x()) > 10 || qAbs(var_difference.y()) > 10) { // ak sa myš vzdiali 10 pixelov od predošlej uloženej pozície...
            var_mouse_viewport_position = var_mouse_event->pos(); // uloží si obe jej pozície
            var_mouse_scene_position = ui->graphicsView->mapToScene(var_mouse_event->pos());
        }
    }
    // Sníma stlačenie myši ak je zvolený "line"
    else if (flag_line_button && param_event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* var_mouse_event = static_cast<QMouseEvent*>(param_event); // pretypovanie udalosti na požadovaný tvar (pre prístup k parametrom)
        if (var_mouse_event->button() == Qt::LeftButton) {
            flag_LMB = true;
            var_line_start_position = var_mouse_event->pos();
        }
    }
    else if (flag_LMB && flag_line_button && param_event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* var_mouse_event = static_cast<QMouseEvent*>(param_event); // pretypovanie udalosti na požadovaný tvar (pre prístup k parametrom)
        if (var_mouse_event->button() == Qt::LeftButton) {
            QLineF aux_line;
            aux_line.setP1(var_line_start_position);
            aux_line.setP2(var_mouse_event->pos());
            obj_scene->addLine(aux_line);
            flag_LMB = false;
        }
    }
    Q_UNUSED(param_object)
    return false;
}

void MainWindow::on_pushButton_toggled(bool checked) {
    if (checked) {
        flag_move_button = true;
        flag_line_button = false;
        flag_LMB = false;
        ui->pushButton_2->setChecked(false);
        ui->pushButton_3->setChecked(false);
    }
    else {
        flag_move_button = false;
    }
}

void MainWindow::on_pushButton_2_toggled(bool checked) {
    if (checked) {
        flag_move_button = false;
        flag_line_button = true;
        flag_LMB = false;
        ui->pushButton->setChecked(false);
        ui->pushButton_3->setChecked(false);
    }
    else {
        flag_line_button = false;
    }

}

void MainWindow::on_pushButton_3_toggled(bool checked) {
    if (checked) {
        flag_move_button = false;
        flag_line_button = false;
        flag_LMB = false;
        ui->pushButton->setChecked(false);
        ui->pushButton_2->setChecked(false);
    }
}

void MainWindow::on_pushButton_4_pressed() {
    QGraphicsPixmapItem *new_item = new QGraphicsPixmapItem;
    new_item->setPixmap(QPixmap(":/block_images/images/sum_block.png"));
    new_item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    obj_scene->addItem(new_item);
}

void MainWindow::on_pushButton_5_pressed() {
    QGraphicsPixmapItem *new_item = new QGraphicsPixmapItem;
    new_item->setPixmap(QPixmap(":/block_images/images/sub_block.png"));
    new_item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    obj_scene->addItem(new_item);
}

void MainWindow::on_pushButton_6_pressed() {
    QGraphicsPixmapItem *new_item = new QGraphicsPixmapItem;
    new_item->setPixmap(QPixmap(":/block_images/images/inc_block.png"));
    new_item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    obj_scene->addItem(new_item);
}

void MainWindow::on_pushButton_7_pressed() {
    QGraphicsPixmapItem *new_item = new QGraphicsPixmapItem;
    new_item->setPixmap(QPixmap(":/block_images/images/dec_block.png"));
    new_item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    obj_scene->addItem(new_item);
}
