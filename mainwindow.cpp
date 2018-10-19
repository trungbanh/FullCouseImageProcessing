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
void MainWindow::Segmentation(int c){
    QImage imgin(ui->il_filePath->text());
    QImage imgout(imgin.width(),imgin.height(),QImage::Format_ARGB32);
    for (int x = 0 ; x < imgin.width();x++){
        for (int y =0 ; y<imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray = qGray(color);
            int grayout = gray;
            if (grayout>c) {
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
//        std::cout<< hn[i] << " ";
    }
    std::cout << "test " << std::endl;
    for (int i =1;i<256 ; i++) {
        c[i]=c[i-1]+hn[i];
//        std::cout<< c[i] << " ";
    }
    std::cout << "test " << std::endl;
    for(int x =0 ; x<imgin.width();x++) {
        for (int y =0; y<imgin.height();y++) {
            QRgb rgb = imgin.pixel(x,y);
            int gray = qGray(rgb);
            int col = 255*c[gray];
//            std::cout << "test " << col << " ";
            output.setPixel(x,y,qRgb(col,col,col));
        }
    }
    DisplayImage(output,"canbang");
    showGrayHistogram(output);
}

void MainWindow::noiseMaker(){
    QImage imgin(ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    float randsalt [imgin.width()][imgin.height()];
    for (int x=0 ; x<imgin.width(); x++) {
        for (int y=0; y<imgin.height();y++) {
            randsalt[x][y] = (float)rand()/RAND_MAX;
            if (randsalt[x][y]<=0.01/2.0) {
                imgout.setPixel(x,y,qRgb(255,255,255));
            } else if (randsalt[x][y]>=1-0.01/2) {
                imgout.setPixel(x,y,qRgb(0,0,0));
            } else {
                imgout.setPixel(x,y,imgin.pixel(x,y));
            }
        }
    }

    DisplayImage(imgout,"noise");
    QString selectFilter ;
    QString file = QFileDialog::getSaveFileName(this,"save file","/home/banhtrung/Pictures/","PNG (*.png);;All File (*.*)",&selectFilter);
    imgout.save(file,"PNG");
}

void MainWindow::meanFilterColor() {
    QImage image(ui->il_filePath->text());
    QImage imgout (image.width(),image.height(),QImage::Format_ARGB32);

    int size = 3;
    int cells = size*size ;
    int magin = size/2;
    int sumR ,sumG,sumB ;
    for (int x=0;x<image.width();x++){
        for (int y=0 ;y<image.height();y++) {
            sumB=sumR=sumG = 0;
            for (int i = -magin;i<=magin ;i++) {
                for (int j = -magin;j<=magin ;j++) {
                    QColor rgb = image.pixel(x+i,y+j);
                    sumR+= rgb.red();
                    sumG+=rgb.green();
                    sumB+=rgb.blue();
                }
            }
            imgout.setPixel(x,y,qRgb(sumR/cells,sumG/cells,sumB/cells));
        }
    }
    DisplayImage(image,"goc");
    DisplayImage(imgout,"loc");
}

void MainWindow::medianFilterGray(){
    QImage image(ui->il_filePath->text());
    QImage imgout (image.width(),image.height(),QImage::Format_ARGB32);

    int size = 3;
    int cells = size*size ;
    int magin = size/2;
    int h[cells];
    for (int x=0;x<image.width();x++){
        for (int y=0 ;y<image.height();y++) {
            int k =0 ;
            for (int i = -magin;i<=magin ;i++) {
                for (int j = -magin;j<=magin ;j++) {
                    QRgb rgb = image.pixel(x+i,y+j);
                    int gray = qGray(rgb);
                    h[k]=gray;
                    k++;
                }
            }
            qSort(h,h+cells);
            imgout.setPixel(x,y,qRgb(h[cells/2],h[cells/2],h[cells/2]));
        }
    }
    DisplayImage(image,"goc");
    DisplayImage(imgout,"loc");
}

void MainWindow::meanFilterGray(){
    QImage image(ui->il_filePath->text());
    QImage imgout (image.width(),image.height(),QImage::Format_ARGB32);

    int size = 3;
    int cells = size*size ;
    int magin = size/2;
    int sumG ;
    for (int x=0;x<image.width();x++){
        for (int y=0 ;y<image.height();y++) {
            sumG = 0;
            for (int i = -magin;i<=magin ;i++) {
                for (int j = -magin;j<=magin ;j++) {
                    QRgb rgb = image.pixel(x+i,y+j);
                    int gray = qGray(rgb);
                    sumG += gray;
                }
            }
            imgout.setPixel(x,y,qRgb(sumG/cells,sumG/cells,sumG/cells));
        }
    }
    DisplayImage(image,"goc");
    DisplayImage(imgout,"loc");
}

void MainWindow::medianFilterColor() {
    QImage image(ui->il_filePath->text());
    QImage imgout (image.width(),image.height(),QImage::Format_ARGB32);

    int size = 3;
    int cells = size*size ;
    int magin = size/2;
    int sumR[cells] ,sumG[cells],sumB[cells] ;
    for (int x=0;x<image.width();x++){
        for (int y=0 ;y<image.height();y++) {
            int k = 0;
            for (int i = -magin;i<=magin ;i++) {
                for (int j = -magin;j<=magin ;j++) {
                    QColor rgb = image.pixel(x+i,y+j);
                    sumR[k]= rgb.red();
                    sumG[k]=rgb.green();
                    sumB[k]=rgb.blue();
                    k++;
                }
            }
            qSort(sumR,sumR+cells);
            qSort(sumG,sumG+cells);
            qSort(sumB,sumB+cells);

            imgout.setPixel(x,y,qRgb(sumR[cells/2],sumG[cells/2],sumB[cells/2]));
        }
    }
    DisplayImage(image,"goc");
    DisplayImage(imgout,"loc");
}

void MainWindow::GradientX(){
    QImage imgin (ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);

    imgout.fill(Qt::white);
    QRgb rgb1,rgb2;

    int gray1=0,gray2=0,grayout=0;

    for (int x=0;x<imgin.width()-1;x++) {
        for (int y=0;y<imgin.height();y++) {
            rgb1 = imgin.pixel(x,y);
            gray1 = qGray(rgb1);
            rgb2 = imgin.pixel(x+1,y);
            gray2 = qGray(rgb2);
            grayout = abs(gray2 - gray1);
            imgout.setPixel(x,y,qRgb(grayout,grayout,grayout));
        }
    }
    DisplayImage(imgout,"bien doc");
}


void MainWindow::GradientY(){
    QImage imgin (ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);

    imgout.fill(Qt::white);
    QRgb rgb1,rgb2;

    int gray1=0,gray2=0,grayout=0;

    for (int x=0;x<imgin.width();x++) {
        for (int y=0;y<imgin.height()-1;y++) {
            rgb1 = imgin.pixel(x,y);
            gray1 = qGray(rgb1);
            rgb2 = imgin.pixel(x,y+1);
            gray2 = qGray(rgb2);
            grayout = abs(gray2 - gray1);
            imgout.setPixel(x,y,qRgb(grayout,grayout,grayout));
        }
    }
    DisplayImage(imgout,"bien ngang");
}

void MainWindow::RobertX(){
    QImage imgin (ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);

    imgout.fill(Qt::white);
    QRgb rgb1,rgb2;

    int gray1=0,gray2=0,grayout=0;

    for (int x=0;x<imgin.width()-1;x++) {
        for (int y=0;y<imgin.height()-1;y++) {
            rgb1 = imgin.pixel(x,y);
            gray1 = qGray(rgb1);
            rgb2 = imgin.pixel(x+1,y+1);
            gray2 = qGray(rgb2);
            grayout = abs(gray2 - gray1);
            imgout.setPixel(x,y,qRgb(grayout,grayout,grayout));
        }
    }
    DisplayImage(imgout,"bien ngang");
}
void MainWindow::RobertY(){
    QImage imgin (ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);

    imgout.fill(Qt::white);
    QRgb rgb1,rgb2;

    int gray1=0,gray2=0,grayout=0;

    for (int x=0;x<imgin.width()-1;x++) {
        for (int y=0;y<imgin.height()-1;y++) {
            rgb1 = imgin.pixel(x+1,y);
            gray1 = qGray(rgb1);
            rgb2 = imgin.pixel(x,y+1);
            gray2 = qGray(rgb2);
            grayout = abs(gray2 - gray1);
            imgout.setPixel(x,y,qRgb(grayout,grayout,grayout));
        }
    }
    DisplayImage(imgout,"bien ngang");
}

void MainWindow::SobelX(){
    QImage imgin (ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    imgout.fill(Qt::white);

    int maskSize =3 ;
    int magin = maskSize/2 ;
    int mashSobel [maskSize][maskSize];
    mashSobel[0][0]=-1;
    mashSobel[0][1]=-2;
    mashSobel[0][2]=-1;
    mashSobel[1][0]=0;
    mashSobel[1][1]=0;
    mashSobel[1][2]=0;
    mashSobel[2][0]=1;
    mashSobel[2][1]=2;
    mashSobel[2][2]=1;
    int sumMask ;

    for (int x=magin;x<imgin.width()-1;x++) {
        for (int y=magin;y<imgin.height()-1;y++) {
            sumMask=0;
            for (int i=-magin;i<=magin;i++) {
                for (int j=-magin;j<=magin;j++) {
                    QRgb rgb = imgin.pixel(x+i,y+j);
                    int gray = qGray(rgb);
                    sumMask+= gray * mashSobel[i+magin][j+magin];
                }
            }
            imgout.setPixel(x,y,qRgb(abs(sumMask),abs(sumMask),abs(sumMask)) );
        }
    }
    DisplayImage(imgout,"bien ngang");
}

void MainWindow::SobelY(){
    QImage imgin (ui->il_filePath->text());
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    imgout.fill(Qt::white);

    int maskSize =3 ;
    int magin = maskSize/2 ;
    int mashSobel [maskSize][maskSize];
    mashSobel[0][0]=-1;
    mashSobel[0][1]=-2;
    mashSobel[0][2]=-1;
    mashSobel[1][0]=0;
    mashSobel[1][1]=0;
    mashSobel[1][2]=0;
    mashSobel[2][0]=1;
    mashSobel[2][1]=2;
    mashSobel[2][2]=1;
    int sumMask ;

    for (int x=magin;x<imgin.width()-1;x++) {
        for (int y=magin;y<imgin.height()-1;y++) {
            sumMask=0;
            for (int i=-magin;i<=magin;i++) {
                for (int j=-magin;j<=magin;j++) {
                    QRgb rgb = imgin.pixel(x+i,y+j);
                    int gray = qGray(rgb);
                    sumMask+= gray * mashSobel[i+magin][j+magin];
                }
            }
            imgout.setPixel(x,y,qRgb(abs(sumMask),abs(sumMask),abs(sumMask)) );
        }
    }
    DisplayImage(imgout,"bien ngang");
}

int MainWindow::nguongTuDong(QImage img) {
    int c =127 ;
    int newC = c ;
    do {
        int G1 =0;
        int count1 = 0;
        int G2 =0;
        int count2 =0;
        c= newC;
        for (int x=0;x<img.width();x++) {
            for (int y=0;y<img.height();y++) {
                QRgb rgb = img.pixel(x,y);
                int gray = qGray(rgb);
                QRgb color = qRgb(gray,gray,gray);
                img.setPixel(x,y,color);
                if (gray >c){
                    G1 = G1+gray;
                    count1++;
                } else if (gray <= c) {
                    G2 = G2 + gray ;
                    count2++;
                }
            }
        }
        int M1 = G1/count1;
        int M2 = G2/count2;
        newC = (M1+M2)/2;
    } while (abs(newC-c)!=0);
    std::cout << newC << std::endl;
    return newC;
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
    QImage image (ui->il_filePath->text());
    int c = nguongTuDong(image);
    Segmentation(c);
}

void MainWindow::on_btn_linear_clicked()
{
    bienDoiTuyenTinh();
}

void MainWindow::on_btn_Qualitization_gray_clicked()
{
    canBangToChucDo();
}

void MainWindow::on_btn_Noise_clicked()
{
    noiseMaker();
}

void MainWindow::on_btn_Mean_Color_clicked()
{
    meanFilterColor();
}

void MainWindow::on_btn_Media_gray_clicked()
{
    medianFilterGray();
}

void MainWindow::on_btn_Mean_gray_clicked()
{
    meanFilterGray();
}


void MainWindow::on_pushButton_4_clicked()
{
    medianFilterColor();
}

void MainWindow::on_btn_Gradien_X_clicked()
{
    GradientX();
}

void MainWindow::on_btn_Gradient_Y_clicked()
{
    GradientY();
}

void MainWindow::on_btn_Robert_X_clicked()
{
    RobertX();
}

void MainWindow::on_btn_Robert_Y_clicked()
{
    RobertY();
}

void MainWindow::on_btn_sobel_x_clicked()
{
    SobelX();
}

void MainWindow::on_btn_sobel_y_clicked()
{
    SobelY();
}
