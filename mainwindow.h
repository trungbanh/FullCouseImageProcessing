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
    QImage Segmentation(int c);
    void showGrayHistogram(QImage image);
    void showColorHistogram(QImage image);
    void bienDoiTuyenTinh();
    void canBangToChucDo();
    void noiseMaker();
    void meanFilterColor();
    void medianFilterGray();
    void meanFilterGray();
    void medianFilterColor();
    void GradientX();
    void GradientY();
    void RobertX();
    void RobertY();
    void SobelX();
    void SobelY();
    int nguongTuDong(QImage img);
    QImage erode (QImage &image);
    QImage dilation (QImage &image);
    QImage open (QImage &img);
    QImage close (QImage &image);

    int otsu (QImage &img);





private slots:
    void on_btn_find_path_clicked();

    void on_btn_his_slide_gray_clicked();

    void on_btn_his_slide_color_clicked();

    void on_btn_his_stretch_gray_clicked();

    void on_btn_his_stretch_color_clicked();

    void on_btn_segmentation_gray_clicked();

    void on_btn_linear_clicked();

    void on_btn_Qualitization_gray_clicked();

    void on_btn_Noise_clicked();

    void on_btn_Mean_Color_clicked();

    void on_btn_Media_gray_clicked();

    void on_btn_Mean_gray_clicked();

    void on_pushButton_4_clicked();

    void on_btn_Gradien_X_clicked();

    void on_btn_Gradient_Y_clicked();

    void on_btn_Robert_X_clicked();

    void on_btn_Robert_Y_clicked();

    void on_btn_sobel_x_clicked();

    void on_btn_sobel_y_clicked();

    void on_btn_erode_clicked();

    void on_btn_dilate_clicked();

    void on_btn_open_clicked();

    void on_bnt_close_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
