#include "exception"
#include "iostream"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QLabel"
#include "QPixmap"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FindPath(){
    QString file = QFileDialog::getOpenFileName(this, "file open","/home/banhtrung/Pictures/","*.* All File;;");
    ui->il_filePath->setText(file);
//    std::cout<< "error get file" << std::endl ;

}
void MainWindow::HisSlide_gray(){
    QString file = ui->il_filePath->text();
    QImage imgin(file);
    QImage imgout(imgin.width(),imgin.height(),QImage::Format_ARGB32);
    for (int x=0;x<imgin.width();x++){
        for (int y=0;y<imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray = qGray(color);
            int grayout = gray+20 ;
            if (grayout>255) {
                grayout = 255;
            }
            if (grayout <0 ) {
                grayout=0;
            }
            QRgb colorout = qRgb(grayout,grayout,grayout);
            imgout.setPixel(x,y,colorout);
        }
    }
    DisplayImage(imgout,"liuliu");
}
void MainWindow::HisSlide_color(){
    QString file = ui->il_filePath->text();
    QImage imgin(file);
    QImage imgout(imgin.width(),imgin.height(),QImage::Format_ARGB32);
    for (int x=0;x<imgin.width();x++){
        for (int y=0;y<imgin.height();y++) {
            QRgb rgb = imgin.pixel(x,y);
            QColor color(rgb);
            int h,s,v ;
            color.getHsv(&h,&s,&v);
            int vout = v+20 ;
            if (vout > 255) {
                vout =255;
            }
            if (vout <0)     {
                vout =0 ;
            }
            QColor colorout = QColor::fromHsv(h,s,v);
            imgout.setPixel(x,y,colorout.rgb());
        }
    }
    DisplayImage(imgout,"liuliu");
}

void MainWindow::HisStretch_gray(){
    QImage imgin(ui->il_filePath->text());
    QImage imgout(imgin.width(),imgin.height(),QImage::Format_ARGB32);
    for (int x = 0 ; x < imgin.width();x++){
        for (int y =0 ; y<imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray = qGray(color);
            int grayout = int(gray*0.5) ;
            if (grayout>255) {
                grayout = 255;
            }
            if (grayout <0 ) {
                grayout=0;
            }
            QRgb colorout = qRgb(grayout,grayout,grayout);
            imgout.setPixel(x,y,colorout);
        }
    }
    DisplayImage(imgout,"liuliu");
    showGrayHistogram(imgout);
}

void MainWindow::HisStretch_color(){
    QImage imgin(ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    for (int x=0;x<imgin.width();x++){
        for (int y=0;y<imgin.height();y++) {
            QRgb rgb = imgin.pixel(x,y);
            QColor color(rgb);
            int h,s,v ;
            color.getHsv(&h,&s,&v);
            int vout = int(v*0.5);
            if (vout > 255) {
                vout =255;
            }
            if (vout <0) {
                vout =0 ;
            }
            QColor colorout = QColor::fromHsv(h,s,v);
            imgout.setPixel(x,y,colorout.rgb());
        }
    }
    DisplayImage(imgout,"liuliu");
    showColorHistogram(imgout);
    showColorHistogram(imgin);

}
void MainWindow::Segmentation(){
    QImage imgin(ui->il_filePath->text());
    QImage imgout(imgin.width(),imgin.height(),QImage::Format_ARGB32);
    for (int x = 0 ; x < imgin.width();x++){
        for (int y =0 ; y<imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray = qGray(color);
            int grayout = gray;
            if (grayout>127) {
                grayout = 255;
            } else {
                grayout=0;
            }
            QRgb colorout = qRgb(grayout,grayout,grayout);
            imgout.setPixel(x,y,colorout);
        }
    }
    DisplayImage(imgout,"liuliu");
}
void MainWindow::showGrayHistogram(QImage image){
    const int HEIGHT =128 ;
    QImage histogram (256,HEIGHT,QImage::Format_ARGB32);
    histogram.fill(Qt::white);
    int h[256];
    for (int i=0 ;i<256;i++){
        h[i]=0;
    }
    for (int x=0 ;x<image.width();x++) {
        for (int y=0;y<image.height();y++) {
            QRgb rgb = image.pixel(x,y);
            int gray =qGray(rgb);
            h[gray]++;
        }
    }
    int max=0;
    for (int i=0;i<256 ; i++) {
        if (max<h[i]){
            max = h[i];
        }
    }
    int lineheight =0;
    for (int x=0;x<256;x++) {
        lineheight =int(HEIGHT*h[x]/max);
//        std::cout << lineheight << " " ;
        for (int y=HEIGHT-1;y>HEIGHT-1-lineheight;y--){
            histogram.setPixel(x,y,qRgb(0,254,0));
        }
    }
    DisplayImage(histogram,"histogram");
}
void MainWindow::showColorHistogram(QImage image) {
    const int HEIGHT =128 ;
    QImage histogram (256,HEIGHT*3,QImage::Format_ARGB32);
    histogram.fill(Qt::white);

    int r[256];
    int g[256];
    int b[256];

    for (int i=0 ;i<256;i++){
        r[i]=0;
        g[i]=0;
        b[i]=0;

    }
    for (int x=0 ;x<image.height();x++){
        for (int y=0;y<image.width();y++) {
            QColor color = image.pixel(x,y);
            int red = color.red();
            int blue = color.blue();
            int green = color.green();
            r[red]++;
            g[green]++;
            b[blue]++;
        }
    }
    int max =0 ;
    for (int i=0;i<256;i++){
        if (max<r[i]) {
            max = r[i];
        }
        if (max<g[i]) {
            max = g[i];
        }
        if (max<b[i]) {
            max = b[i];
        }
    }
    int lineHeight;
    for (int i=0;i<256;i++){
        lineHeight = HEIGHT*r[i]/max;
        for (int j = HEIGHT-1 ;j>HEIGHT-lineHeight;j--){
            histogram.setPixel(i,j,qRgb(255,0,0));
        }
        lineHeight = HEIGHT*g[i]/max;
        for (int j = HEIGHT*2-1 ;j>HEIGHT*2-lineHeight;j--){
            histogram.setPixel(i,j,qRgb(0,255,0));
        }
        lineHeight = HEIGHT*b[i]/max;
        for (int j = HEIGHT*3-1 ;j>HEIGHT*3-lineHeight;j--){
            histogram.setPixel(i,j,qRgb(0,0,255));
        }
    }
    DisplayImage(histogram,"color");
}
void MainWindow::bienDoiTuyenTinh() {
    QImage image (ui->il_filePath->text());
    QImage result (image.width(),image.height(),QImage::Format_ARGB32);
    int max = 0 ,min = 999 ;
    for (int x=0;x<image.width();x++) {
        for (int y=0 ;y<image.height();y++) {
            QRgb col  = image.pixel(x,y);
            int gray = qGray(col);
            std::cout<< gray << " ";
            if (gray > max) {
                max = gray ;
            }
            if (gray < min) {
                min = gray ;
            }
        }
    }
    for (int x=0;x<image.width();x++) {
        for (int y=0 ;y<image.height();y++) {
            QRgb col  = image.pixel(x,y);
            int gray = qGray(col);
            int new_gray = 255*(gray - min)/(max-min);
//            std::cout << new_gray << " ";
            result.setPixel(x,y,qRgb(new_gray,new_gray,new_gray));
        }
    }
    DisplayImage(result,"bien doi");
    showGrayHistogram(result);
}

void MainWindow::canBangToChucDo(){
    QImage imgin(ui->il_filePath->text());
    QImage output (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    int h[256];
    float hn[256],c[256];

    for (int i=0 ; i<256 ; i++){
        h[i]= 0;
        hn[i]=0;
        c[i]=0;
    }
    for(int x =0 ; x<imgin.width();x++) {
        for (int y =0; y<imgin.height();y++) {
            QRgb rgb = imgin.pixel(x,y);
            int gray = qGray(rgb);
            h[gray]++;
        }
    }

    int tongPixel = imgin.width()*imgin.height();
    std::cout << "tong pixel "<< tongPixel << std::endl;
    for (int i =0 ; i<256 ; i++){
        hn[i] =(float)h[i]/tongPixel;
        std::cout<< hn[i] << " ";
    }
    std::cout << "test " << std::endl;
    for (int i =1;i<256 ; i++) {
        c[i]=c[i-1]+hn[i];
        std::cout<< c[i] << " ";
    }
    std::cout << "test " << std::endl;
    for(int x =0 ; x<imgin.width();x++) {
        for (int y =0; y<imgin.height();y++) {
            QRgb rgb = imgin.pixel(x,y);
            int gray = qGray(rgb);
            int col = 255*c[gray];
            std::cout << "test " << col << " ";
            output.setPixel(x,y,qRgb(col,col,col));
        }
    }
    DisplayImage(output,"canbang");
    showGrayHistogram(output);
}

void MainWindow::DisplayImage(QImage &image, QString titel){
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap::fromImage(image));
    label->setWindowTitle(QFileInfo(titel).fileName());
    label->show();
}

void MainWindow::on_btn_find_path_clicked()
{
    FindPath();
}


void MainWindow::on_btn_his_slide_gray_clicked()
{
    HisSlide_gray();
}

void MainWindow::on_btn_his_slide_color_clicked()
{
    HisSlide_color();
}

void MainWindow::on_btn_his_stretch_gray_clicked()
{
    HisStretch_gray();
}

void MainWindow::on_btn_his_stretch_color_clicked()
{
    HisStretch_color();
}

void MainWindow::on_btn_segmentation_gray_clicked()
{
    Segmentation();
}

void MainWindow::on_btn_linear_clicked()
{
    bienDoiTuyenTinh();
}

void MainWindow::on_btn_Qualitization_gray_clicked()
{
    canBangToChucDo();
}
