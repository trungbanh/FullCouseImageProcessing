#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DisplayImage (QImage &image, QString title);
    void FindPath();
    void HisSlide_gray();
    void HisSlide_color();
    void HisStretch_gray();
    void HisStretch_color();
    void Segmentation();
    void showGrayHistogram(QImage image);
    void showColorHistogram(QImage image);
    void bienDoiTuyenTinh();
    void canBangToChucDo();

private slots:
    void on_btn_find_path_clicked();

    void on_btn_his_slide_gray_clicked();

    void on_btn_his_slide_color_clicked();

    void on_btn_his_stretch_gray_clicked();

    void on_btn_his_stretch_color_clicked();

    void on_btn_segmentation_gray_clicked();

    void on_btn_linear_clicked();

    void on_btn_Qualitization_gray_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
