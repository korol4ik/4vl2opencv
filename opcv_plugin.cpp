//g++ file.cpp -o file -lopencv_highgui -lopencv_core
#include "opencv.h"

void komiks(IplImage *img_in,IplImage *img_out)
{
IplImage *sw,*gr,*gr_kol;
gr_kol= cvCreateImage(cvGetSize(img_in),img_in->depth,img_in->nChannels);
sw=cvCreateImage(cvGetSize(img_in),IPL_DEPTH_8U,1);  //<Inizializazija Kartinok
gr=cvCreateImage(cvGetSize(sw),IPL_DEPTH_8U,1);  //Objazatel'no!!!

//Polu4enie kadra

 //i ego vida4a iz bufera

   cvConvertImage(img_in,sw,CV_BGR2GRAY);//Delaem 4erno beli kadr (sw)
   cvCanny( sw, gr,10,250, 3);//Videljaem granii (gr) iz sw
    cvConvertImage(gr,gr_kol,0);//preobrazovivaem rezultat Canny v BGR24 format..
   cvSub(img_in,gr_kol,img_out,sw);//nakladivaem rezul'tat Canny na pervona4al'ni kadr


   cvReleaseImage(&gr);
   cvReleaseImage(&gr_kol);
   cvReleaseImage(&sw);



}

