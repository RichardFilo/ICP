#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "block_schema.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

private slots:
        void on_pushButton_toggled(bool checked);

        void on_pushButton_2_toggled(bool checked);

        void on_pushButton_3_toggled(bool checked);

        void on_pushButton_4_pressed();

        void on_pushButton_5_pressed();

        void on_pushButton_6_pressed();

        void on_pushButton_7_pressed();

private:
        Ui::MainWindow *ui;
        QGraphicsScene *obj_scene;

        Block_schema *obj_block_schema;

        QPointF var_mouse_scene_position, var_mouse_viewport_position;

        bool flag_move_button, flag_line_button, flag_LMB;
        QPointF var_line_start_position;

        void ViewZoom(QGraphicsView* param_view, double param_factor);
        bool eventFilter(QObject *param_object, QEvent *param_event);
};
#endif // MAINWINDOW_H
